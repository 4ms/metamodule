#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/plugin_popup.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "user_settings/plugin_autoload_settings.hh"
#include <algorithm>

namespace MetaModule
{

struct PluginTab : SystemMenuTab {

	PluginTab(PluginManager &plugin_manager,
			  PluginAutoloadSettings &settings,
			  NotificationQueue &notify_queue,
			  GuiState &gui_state,
			  PatchPlayLoader &play_loader)
		: plugin_manager{plugin_manager}
		, notify_queue{notify_queue}
		, settings{settings}
		, gui_state{gui_state}
		, play_loader{play_loader} {

		clear_loaded_list();
		clear_found_list();
		lv_show(ui_PluginScanButton);
		lv_obj_add_event_cb(ui_PluginScanButton, scan_plugins_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PluginScanButton, scroll_up_cb, LV_EVENT_FOCUSED, this);
		lv_hide(ui_PluginsFoundCont);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;
		lv_show(ui_PluginScanButton);
		lv_hide(ui_PluginsFoundCont);
		lv_hide(ui_PluginTabSpinner);

		const auto &loaded_plugins = plugin_manager.loaded_plugins();
		if (!lv_obj_get_child_cnt(ui_PluginsLoadedCont) && loaded_plugins.size()) {
			// plugins were autoloaded on startup, they need to be added to the loaded plugin list.
			for (auto &p : loaded_plugins) {
				auto pluginname = std::string{p.fileinfo.plugin_name};
				if (p.fileinfo.version.length() > 0)
					pluginname += Gui::grey_text(" " + std::string{p.fileinfo.version});

				lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, pluginname.c_str());
				lv_obj_add_event_cb(plugin_obj, query_loaded_plugin_cb, LV_EVENT_CLICKED, this);
				lv_obj_add_event_cb(plugin_obj, scroll_up_cb, LV_EVENT_FOCUSED, this);
			}
		}

		clear_found_list();
		reset_group();
		lv_group_focus_obj(ui_PluginScanButton);
		confirm_popup.init(ui_SystemMenu, group);
	}

	bool consume_back_event() override {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;
		}

		if (should_write_settings)
			gui_state.do_write_settings = true;
		return false;
	}

	void update() override {
		auto result = plugin_manager.process_loading();

		if (result.state == PluginFileLoader::State::GotList) {
			lv_hide(ui_PluginTabSpinner);
			lv_hide(ui_PluginScanButton);
			lv_show(ui_PluginsFoundCont);

			auto *found_plugins = plugin_manager.found_plugin_list();

			for (unsigned idx = 0; auto plugin : *found_plugins) {
				auto pluginname = std::string{plugin.plugin_name};
				if (plugin.version.length() > 0)
					pluginname += Gui::grey_text(" " + std::string{plugin.version});

				if (!plugin_already_loaded(plugin)) {

					lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsFoundCont, pluginname.c_str());

					lv_obj_set_user_data(plugin_obj, (void *)((uintptr_t)idx + 1));
					lv_obj_add_event_cb(plugin_obj, load_plugin_cb, LV_EVENT_CLICKED, this);
					lv_obj_add_event_cb(plugin_obj, scroll_up_cb, LV_EVENT_FOCUSED, this);
				}

				idx++;
			}
			reset_group();
			lv_group_focus_obj(lv_obj_get_child(ui_PluginsFoundCont, 0));
		}

		else if (result.state == PluginFileLoader::State::Success)
		{
			lv_hide(ui_PluginTabSpinner);
			if (load_in_progress_obj) {
				auto label = lv_obj_get_child(load_in_progress_obj, 0);
				std::string pluginname = label ? lv_label_get_text(label) : "(new plugin)";
				lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, pluginname.c_str());
				lv_group_add_obj(group, plugin_obj);
				lv_group_focus_obj(plugin_obj);
				lv_obj_add_event_cb(plugin_obj, query_loaded_plugin_cb, LV_EVENT_CLICKED, this);

				lv_obj_del_async(load_in_progress_obj);

				load_in_progress_obj = nullptr;
			}
		}

		if (result.error_message.length()) {
			lv_hide(ui_PluginTabSpinner);
			std::string err = "Error loading plugin: " + result.error_message;
			notify_queue.put({err, Notification::Priority::Error, 2500});
		}
	}

private:
	void reset_group() {
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, lv_tabview_get_tab_btns(ui_SystemMenuTabView));
		lv_group_add_obj(group, ui_PluginScanButton);
		lv_foreach_child(ui_PluginsFoundCont, [this](auto *obj, unsigned) {
			lv_group_add_obj(this->group, obj);
			return true;
		});
		lv_foreach_child(ui_PluginsLoadedCont, [this](auto *obj, unsigned) {
			lv_group_add_obj(this->group, obj);
			return true;
		});
	}

	void clear_loaded_list() {
		lv_foreach_child(ui_PluginsLoadedCont, [](auto *obj, unsigned) {
			lv_obj_del_async(obj);
			return true;
		});
	}

	void clear_found_list() {
		lv_foreach_child(ui_PluginsFoundCont, [](auto *obj, unsigned) {
			lv_obj_del_async(obj);
			return true;
		});
	}

	void populate_loaded_list() {
		auto loaded_plugin_list = plugin_manager.loaded_plugins();
		for (auto &plugin : loaded_plugin_list) {
			auto plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, plugin.fileinfo.plugin_name.c_str());
			lv_group_add_obj(group, plugin_obj);
		}
	}

	bool plugin_already_loaded(PluginFile const &plugin) {
		auto const &loaded_plugin_list = plugin_manager.loaded_plugins();
		for (auto &loaded_plugin_file : loaded_plugin_list) {
			auto const &loaded_plugin = loaded_plugin_file.fileinfo;
			pr_dbg(
				"Comparing %s (new) and %s (loaded)\n", plugin.plugin_name.c_str(), loaded_plugin.plugin_name.c_str());
			if (loaded_plugin.plugin_name == plugin.plugin_name) {
				return true;
			}
		}
		return false;
	}

	void unload_plugin(std::string_view plugin_name) {
		play_loader.prepare_remove_plugin(plugin_name);
		plugin_manager.unload_plugin(plugin_name);
		gui_state.force_redraw_patch = true;
		if (lv_obj_has_flag(ui_PluginScanButton, LV_OBJ_FLAG_HIDDEN)) {
			clear_found_list();
			scan_plugins();
			lv_show(ui_PluginScanButton);
		}
	}

	static void query_loaded_plugin_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		const auto target = lv_event_get_target(event);
		const std::string plugin_name = lv_list_get_btn_text(lv_event_get_current_target(event), target);

		const auto is_autoloaded =
			std::find(page->settings.slug.begin(), page->settings.slug.end(), plugin_name) != page->settings.slug.end();

		page->confirm_popup.show(
			[page, plugin_name, target](uint8_t opt) {
				if (!opt)
					return;

				if (opt == 1) {
					pr_info("Unload Plugin: %s\n", plugin_name.data());
					page->unload_plugin(plugin_name);
					lv_obj_del_async(target);
				}
			},
			[page, plugin_name](bool opt) {
				const auto autoload_slot =
					std::find(page->settings.slug.begin(), page->settings.slug.end(), plugin_name);
				if (opt) {
					pr_info("Set Autoload Enabled: %s\n", plugin_name.data());
					page->settings.slug.push_back(plugin_name);
				} else {
					pr_info("Set Autoload Disabled: %s\n", plugin_name.data());
					page->settings.slug.erase(autoload_slot);
				}
				page->should_write_settings = true;
			},
			plugin_name.c_str(),
			"Unload",
			is_autoloaded);
	}

	static void scan_plugins_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;
		page->scan_plugins();
	}

	void scan_plugins() {
		lv_show(ui_PluginTabSpinner);
		plugin_manager.start_loading_plugin_list();
	}

	static void scroll_up_cb(lv_event_t *event) {
		const auto list = lv_obj_get_parent(event->target);
		const auto is_found_list = list == ui_PluginsFoundCont;
		const auto found_list_empty = lv_obj_get_child_cnt(ui_PluginsFoundCont) == 0;
		const auto is_first_in_list = event->target == lv_obj_get_child(list, 0);
		if (event->target == ui_PluginScanButton || (is_first_in_list && (is_found_list || found_list_empty))) {
			lv_obj_scroll_to_y(ui_SystemMenuPluginsTab, 0, LV_ANIM_ON);
		}
	}

	static void load_plugin_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
		if (idx > 0) {
			lv_show(ui_PluginTabSpinner);
			page->plugin_manager.load_plugin(idx - 1);
			page->load_in_progress_obj = event->target;
		}
	}

	PluginManager &plugin_manager;
	NotificationQueue &notify_queue;
	PluginAutoloadSettings &settings;
	GuiState &gui_state;
	bool should_write_settings = false;
	PatchPlayLoader &play_loader;
	PluginPopup confirm_popup;

	lv_obj_t *load_in_progress_obj = nullptr;

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
