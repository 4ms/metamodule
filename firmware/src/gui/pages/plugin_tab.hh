#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct PluginTab : SystemMenuTab {

	PluginTab(PluginManager &plugin_manager, NotificationQueue &notify_queue)
		: plugin_manager{plugin_manager}
		, notify_queue{notify_queue} {

		clear_loaded_list();
		clear_found_list();
		lv_show(ui_PluginScanButton);
		lv_obj_add_event_cb(ui_PluginScanButton, scan_plugins_cb, LV_EVENT_CLICKED, this);
		lv_hide(ui_PluginsFoundCont);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;
		lv_show(ui_PluginScanButton);
		lv_hide(ui_PluginsFoundCont);
		lv_hide(ui_PluginTabSpinner);
		lv_group_add_obj(this->group, ui_PluginScanButton);

		lv_foreach_child(ui_PluginsLoadedCont, [this](auto *obj, unsigned) {
			lv_group_add_obj(this->group, obj);
			return true;
		});
		lv_group_focus_obj(ui_PluginScanButton);
	}

	void update() override {
		auto result = plugin_manager.process_loading();

		if (result.state == PluginFileLoader::State::GotList) {
			lv_hide(ui_PluginTabSpinner);
			lv_hide(ui_PluginScanButton);
			lv_show(ui_PluginsFoundCont);

			clear_found_list();

			bool first_item = true;
			auto *found_plugins = plugin_manager.found_plugin_list();

			for (unsigned idx = 0; auto plugin : *found_plugins) {
				// Strip .so
				auto pluginname = std::string{std::string_view{plugin.plugin_name}};
				if (pluginname.ends_with(".so")) {
					pluginname = pluginname.substr(0, pluginname.length() - 3);
				}

				if (!plugin_already_loaded(pluginname)) {

					lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsFoundCont, pluginname.c_str());
					lv_group_add_obj(group, plugin_obj);

					if (first_item) {
						lv_group_focus_obj(plugin_obj);
						first_item = false;
					}

					lv_obj_set_user_data(plugin_obj, (void *)((uintptr_t)idx + 1));
					lv_obj_add_event_cb(plugin_obj, load_plugin_cb, LV_EVENT_CLICKED, this);
					lv_obj_add_event_cb(plugin_obj, scroll_on_focus_cb, LV_EVENT_FOCUSED, this);
					lv_obj_add_event_cb(plugin_obj, noscroll_on_defocus_cb, LV_EVENT_DEFOCUSED, this);
				}

				idx++;
			}
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
				lv_obj_add_event_cb(plugin_obj, scroll_on_focus_cb, LV_EVENT_FOCUSED, this);
				lv_obj_add_event_cb(plugin_obj, noscroll_on_defocus_cb, LV_EVENT_DEFOCUSED, this);

				lv_obj_del_async(load_in_progress_obj);

				load_in_progress_obj = nullptr;
			}
		}

		if (result.error_message.length()) {
			lv_hide(ui_PluginTabSpinner);
			pr_err("Error: %s\n", result.error_message.c_str());
			std::string err = "Error loading plugin: " + result.error_message;
			notify_queue.put({err, Notification::Priority::Error, 1500});
		}
	}

private:
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
			lv_obj_add_event_cb(plugin_obj, scroll_on_focus_cb, LV_EVENT_FOCUSED, this);
			lv_obj_add_event_cb(plugin_obj, noscroll_on_defocus_cb, LV_EVENT_DEFOCUSED, this);
		}
	}

	bool plugin_already_loaded(std::string_view name) {
		// TODO: get this working
		auto const &loaded_plugin_list = plugin_manager.loaded_plugins();
		for (auto &plugin : loaded_plugin_list) {
			pr_dbg("Comparing %s (new) and %s (loaded)\n", name.data(), plugin.fileinfo.plugin_name.c_str());
			if (plugin.fileinfo.plugin_name == name) {
				return true;
			}
		}
		return false;
	}

	static void scan_plugins_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;
		lv_show(ui_PluginTabSpinner);
		page->plugin_manager.start_loading_plugin_list();
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

	static void scroll_on_focus_cb(lv_event_t *event) {
		if (event->target)
			label_scrolls(event->target);
	}

	static void noscroll_on_defocus_cb(lv_event_t *event) {
		if (event->target)
			label_overflow_dot(event->target);
	}

	PluginManager &plugin_manager;
	NotificationQueue &notify_queue;

	lv_obj_t *load_in_progress_obj = nullptr;

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
