#pragma once
#include "dynload/plugin_manager.hh"
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/plugin_popup.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/plugin_preload_settings.hh"
#include <algorithm>
#include <deque>

namespace MetaModule
{

struct PluginTab : SystemMenuTab {

	PluginTab(PluginManager &plugin_manager,
			  PluginPreloadSettings &settings,
			  NotificationQueue &notify_queue,
			  GuiState &gui_state,
			  PatchPlayLoader &play_loader)
		: plugin_manager{plugin_manager}
		, notify_queue{notify_queue}
		, settings{settings}
		, gui_state{gui_state}
		, play_loader{play_loader} {

		clear_autoloads_button = create_button(ui_PluginsRightColumn, "Pre-load None");
		current_autoloads_button = create_button(ui_PluginsRightColumn, "Pre-load Current");
		load_all_found_button = create_button(ui_PluginsLeftColumn, "Load all");

		{ // Load All popup
			load_all_popup = lv_obj_create(lv_layer_top());
			lv_obj_set_width(load_all_popup, 320);
			lv_obj_set_height(load_all_popup, LV_SIZE_CONTENT);
			lv_obj_set_style_radius(load_all_popup, 0, LV_PART_MAIN);
			lv_obj_set_style_pad_hor(load_all_popup, 8, LV_PART_MAIN);
			lv_obj_set_style_pad_ver(load_all_popup, 6, LV_PART_MAIN);
			lv_obj_set_style_bg_color(load_all_popup, lv_color_hex(0xE1E878), LV_PART_MAIN);
			lv_obj_add_flag(load_all_popup, LV_OBJ_FLAG_SNAPABLE);

			load_in_progress_label = lv_label_create(load_all_popup);
			lv_label_set_text(load_in_progress_label, "Loading All Plugins: Please Wait");
			lv_obj_set_style_text_color(load_all_popup, lv_color_black(), LV_PART_MAIN);
			lv_label_set_long_mode(load_in_progress_label, LV_LABEL_LONG_DOT);
			lv_obj_set_width(load_in_progress_label, LV_PCT(100));
			lv_obj_set_height(load_in_progress_label, LV_SIZE_CONTENT);
			lv_hide(load_all_popup);

			loading_group = lv_group_create();
			lv_group_add_obj(loading_group, load_all_popup);
		}

		clear_loaded_list();
		clear_found_list();
		lv_show(ui_PluginScanButton);
		lv_obj_add_event_cb(ui_PluginScanButton, scan_plugins_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PluginScanButton, scroll_up_cb, LV_EVENT_FOCUSED, this);
		lv_hide(ui_PluginsFoundCont);

		lv_obj_add_event_cb(clear_autoloads_button, clear_autoloads, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(current_autoloads_button, current_autoloads, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(load_all_found_button, load_all, LV_EVENT_CLICKED, this);

		lv_show(load_all_found_button);

		ram_label = lv_label_create(ui_PluginsRightColumn);
		lv_obj_move_to_index(ram_label, 1);
		lv_obj_set_style_text_font(ram_label, &ui_font_MuseoSansRounded50012, 0);
		lv_label_set_text(ram_label, "");
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;
		lv_show(ui_PluginScanButton);
		lv_hide(ui_PluginsFoundCont);
		lv_hide(ui_PluginTabSpinner);

		const auto &loaded_plugins = plugin_manager.loaded_plugins();
		if (!lv_obj_get_child_cnt(ui_PluginsLoadedCont) && loaded_plugins.size()) {
			// plugins were autoloaded on startup, they need to be added to the loaded plugin list.
			for (auto const &p : loaded_plugins) {
				auto pluginname = std::string{p.fileinfo.plugin_name};
				if (p.fileinfo.version_in_filename.length() > 0)
					pluginname += "\n" + Gui::grey_text(std::string{p.fileinfo.version_in_filename});

				lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, pluginname.c_str());
				lv_obj_add_event_cb(plugin_obj, query_loaded_plugin_cb, LV_EVENT_CLICKED, this);
				lv_obj_add_event_cb(plugin_obj, scroll_up_cb, LV_EVENT_FOCUSED, this);
			}
		}

		clear_found_list();
		reset_group();
		lv_hide(load_all_popup);
		lv_hide(load_all_found_button);

		lv_group_focus_obj(ui_PluginScanButton);
		lv_obj_scroll_to_y(ui_SystemMenuPluginsTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_PluginScanButton, LV_ANIM_OFF);

		plugin_state_popup.init(ui_SystemMenu, group);
		confirm_popup.init(ui_SystemMenu, group);

		show_ramdisk_free();

		pr_dbg("Pre-loaded list:\n");
		for (auto const &slug : settings.slug) {
			pr_dbg("'%s'\n", slug.c_str());
		}

		is_loading_all = false;
	}

	bool consume_back_event() override {
		if (plugin_state_popup.is_visible()) {
			plugin_state_popup.hide();
			return true;
		}
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;
		}
		if (is_loading_all) {
			is_loading_all = false;
			lv_hide(load_all_popup);
			return false;
		}

		if (should_write_settings)
			gui_state.do_write_settings = true;
		return false;
	}

	void update() override {
		auto result = plugin_manager.process_loading();
		bool loading_done = false;

		if (result.state == PluginFileLoader::State::GotList) {
			lv_hide(ui_PluginTabSpinner);
			lv_hide(ui_PluginScanButton);
			lv_show(ui_PluginsFoundCont);

			display_found_plugins();

			reset_group();
			lv_group_focus_obj(lv_obj_get_child(ui_PluginsFoundCont, 0));
		}

		else if (result.state == PluginFileLoader::State::Success)
		{
			lv_hide(ui_PluginTabSpinner);
			move_found_plugin_to_loaded();

			loading_done = true;
		}

		if (result.error_message.length()) {
			lv_hide(ui_PluginTabSpinner);

			std::string err = "Error loading plugin: " + result.error_message;
			notify_queue.put({err, Notification::Priority::Error, 2500});

			last_loaded_name = "";
			loading_done = true;
		}

		if (is_loading_all && loading_done) {
			show_ramdisk_free();

			lv_show(ui_PluginTabSpinner);
			load_next();
		}
	}

	bool is_idle() override {
		return plugin_manager.is_idle();
	}

private:
	void reset_group() {
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, lv_tabview_get_tab_btns(ui_SystemMenuTabView));
		lv_group_add_obj(group, ui_PluginScanButton);

		lv_foreach_child(ui_PluginsFoundCont, [this](auto *obj, unsigned) { lv_group_add_obj(this->group, obj); });
		lv_group_add_obj(group, load_all_found_button);

		lv_foreach_child(ui_PluginsLoadedCont, [this](auto *obj, unsigned) { lv_group_add_obj(this->group, obj); });
		lv_group_add_obj(group, clear_autoloads_button);
		lv_group_add_obj(group, current_autoloads_button);

		// Show "autoload none" only if there are plugins to be autoloaded
		lv_show(clear_autoloads_button, settings.slug.size() > 0);

		// Show "autoload current" only if there are plugins currently loaded
		lv_show(current_autoloads_button, (lv_obj_get_child_cnt(ui_PluginsLoadedCont) > 0));

		// Show "load all" only if there are plugins found
		lv_show(load_all_found_button, lv_obj_get_child_cnt(ui_PluginsFoundCont) > 0);
	}

	void clear_loaded_list() {
		lv_foreach_child(ui_PluginsLoadedCont, [](auto *obj, unsigned) { lv_obj_del_async(obj); });
	}

	void clear_found_list() {
		lv_foreach_child(ui_PluginsFoundCont, [](auto *obj, unsigned) { lv_obj_del_async(obj); });
		lv_hide(load_all_found_button);
	}

	void populate_loaded_list() {
		auto const &loaded_plugin_list = plugin_manager.loaded_plugins();
		for (auto &plugin : loaded_plugin_list) {
			auto plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, plugin.fileinfo.plugin_name.c_str());
			lv_group_add_obj(group, plugin_obj);
		}
	}

	bool plugin_already_loaded(PluginFile const &plugin) {
		auto const &loaded_plugin_list = plugin_manager.loaded_plugins();
		for (auto &loaded_plugin_file : loaded_plugin_list) {
			auto const &loaded_plugin = loaded_plugin_file.fileinfo;
			pr_trace(
				"Comparing %s (new) and %s (loaded)\n", plugin.plugin_name.c_str(), loaded_plugin.plugin_name.c_str());
			if (loaded_plugin.plugin_name == plugin.plugin_name) {
				return true;
			}
		}
		return false;
	}

	void unload_plugin(std::string_view plugin_name) {
		play_loader.prepare_patch_for_plugin_change(plugin_name);
		plugin_manager.unload_plugin(plugin_name);
		gui_state.force_redraw_patch = true;
		if (lv_obj_has_flag(ui_PluginScanButton, LV_OBJ_FLAG_HIDDEN)) {
			clear_found_list();
			scan_plugins();
			lv_show(ui_PluginScanButton);
			lv_hide(load_all_found_button);
		}
		show_ramdisk_free();
	}

	void display_found_plugins() {
		auto *found_plugins = plugin_manager.found_plugin_list();
		std::string last_pluginname = "";

		for (unsigned idx = 0; auto const &plugin : *found_plugins) {
			idx++;

			if (!plugin_already_loaded(plugin)) {

				std::string pluginname;
				lv_obj_t *plugin_obj;

				if (last_pluginname == std::string_view(plugin.plugin_name)) {
					pluginname = (plugin.version_in_filename.length() > 0) ?
									 Gui::grey_text(plugin.version_in_filename) :
									 "(no version)";

					plugin_obj = create_plugin_list_version_item(ui_PluginsFoundCont, pluginname.c_str());

				} else {
					pluginname = std::string{plugin.plugin_name};

					if (plugin.version_in_filename.length() > 0) {
						pluginname += "\n" + Gui::grey_text(plugin.version_in_filename);
					}

					plugin_obj = create_plugin_list_item(ui_PluginsFoundCont, pluginname.c_str());
				}

				lv_obj_set_user_data(plugin_obj, (void *)((uintptr_t)idx));
				lv_obj_add_event_cb(plugin_obj, load_plugin_cb, LV_EVENT_CLICKED, this);
				lv_obj_add_event_cb(plugin_obj, scroll_up_cb, LV_EVENT_FOCUSED, this);

				last_pluginname = std::string(plugin.plugin_name);
			}
		}
	}

	void delete_found_items_with_name(std::string_view plugin_name) {
		auto *found_plugins = plugin_manager.found_plugin_list();

		lv_foreach_child(ui_PluginsFoundCont, [=](lv_obj_t *obj, unsigned) {
			auto idx = (uintptr_t)lv_obj_get_user_data(obj);

			if (idx > 0 && idx <= (*found_plugins).size()) {
				auto &plugin = (*found_plugins)[idx - 1];

				if (plugin.plugin_name == plugin_name) {
					lv_obj_del_async(obj);
				}
			}
		});
	}

	void move_found_plugin_to_loaded() {
		if (load_in_progress_obj) {
			auto label = lv_obj_get_child(load_in_progress_obj, 0);

			std::string pluginname;

			if (auto idx = (uintptr_t)lv_obj_get_user_data(load_in_progress_obj); idx > 0) {
				auto *found_plugins = plugin_manager.found_plugin_list();
				auto &plugin = (*found_plugins)[idx - 1];
				pluginname = std::string{plugin.plugin_name};

				delete_found_items_with_name(plugin.plugin_name);

				if (plugin.version_in_filename.length() > 0)
					pluginname += "\n" + Gui::grey_text(plugin.version_in_filename);

			} else {
				pluginname = label ? lv_label_get_text(label) : "(new plugin)";
				lv_obj_del(load_in_progress_obj);
			}

			lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, pluginname.c_str());

			lv_obj_add_event_cb(plugin_obj, query_loaded_plugin_cb, LV_EVENT_CLICKED, this);

			reset_group();

			if (!is_loading_all)
				lv_group_focus_obj(plugin_obj);

			load_in_progress_obj = nullptr;
			gui_state.playing_patch_needs_manual_reload = true;
			gui_state.force_redraw_patch = true;
		}
	}

	void show_ramdisk_free() {
		auto [avail, total] = plugin_manager.get_free_total_space_kb();
		if (avail >= 0 && total >= 0) {
			lv_label_set_text_fmt(
				ram_label, "%dMB of %dMB used", (int)std::round((total - avail) / 1024), (int)std::round(total / 1024));
		} else {
			lv_label_set_text(ram_label, "");
		}
	}

	static void query_loaded_plugin_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		const auto target = lv_event_get_target(event);
		if (lv_obj_get_child_cnt(target) != 1)
			return;

		std::string plugin_name = lv_label_get_text(lv_obj_get_child(target, 0));
		if (auto newline = plugin_name.find_first_of("\n"); newline != std::string::npos) {
			plugin_name = plugin_name.substr(0, newline);
		}
		//trim
		while (plugin_name.back() == ' ')
			plugin_name.pop_back();

		const auto is_autoloaded = std::ranges::find(page->settings.slug, plugin_name) != page->settings.slug.end();
		pr_dbg("%s found %s in slugs\n", is_autoloaded ? "Did" : "Did not", plugin_name.c_str());

		page->plugin_state_popup.show(
			[page, plugin_name, target](std::optional<uint8_t> button, std::optional<bool> toggle) {
				if (button) {
					// Cancel
					if (*button == 0)
						return;

					// Unload
					if (*button == 1) {
						pr_info("Unload Plugin: %s\n", plugin_name.data());
						page->unload_plugin(plugin_name);
						lv_obj_del_async(target);
					}
				}

				// Preload toggle
				if (toggle) {
					if (*toggle) {
						pr_info("Pre-load Enabled: %s\n", plugin_name.data());
						page->settings.slug.push_back(plugin_name);
					} else {
						const auto autoload_slot = std::ranges::find(page->settings.slug, plugin_name);
						if (autoload_slot != page->settings.slug.end()) {
							pr_info("Pre-load Disabled: %s\n", plugin_name.data());
							page->settings.slug.erase(autoload_slot);
						} else {
							pr_err("Error: can't disable pre-load for %s: not found in settings pre-load list\n",
								   plugin_name.data());
						}
					}
					page->should_write_settings = true;
				}
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

			auto *plugins = page->plugin_manager.found_plugin_list();
			page->play_loader.prepare_patch_for_plugin_change((*plugins)[idx - 1].plugin_name);

			page->plugin_manager.load_plugin(idx - 1);
			page->load_in_progress_obj = event->target;
		}
	}

	static void clear_autoloads(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		page->confirm_popup.show(
			[page](unsigned ok) {
				if (ok) {
					page->settings.slug.clear();
					page->gui_state.do_write_settings = true;
				}
			},
			"Are you sure you want to disable pre-loading plugins?",
			"OK");
	}

	static void current_autoloads(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		page->confirm_popup.show(
			[page](unsigned ok) {
				if (ok) {
					page->settings.slug.clear();
					auto const &current = page->plugin_manager.loaded_plugins();
					for (auto const &plugin : current) {
						std::string name = plugin.fileinfo.plugin_name;
						page->settings.slug.push_back(name);
					}

					page->gui_state.do_write_settings = true;
				}
			},
			"This will pre-load the current set of loaded plugins the next time you power on",
			"OK");
	}

	static void load_all(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		page->start_loading_all();
	}

	void end_loading_all() {
		lv_hide(ui_PluginTabSpinner);
		lv_hide(load_all_popup);
		lv_show(ui_PluginScanButton);

		is_loading_all = false;

		lv_group_activate(group);
		reset_group();
		lv_hide(load_all_found_button);
		notify_queue.put({"Done loading all plugins"});
	}

	void start_loading_all() {
		lv_show(load_all_popup);
		lv_show(ui_PluginTabSpinner);
		lv_hide(load_all_found_button);

		lv_obj_scroll_to_y(ui_SystemMenuPluginsTab, 0, LV_ANIM_ON);
		lv_group_activate(loading_group);

		plugins_to_load.clear();

		lv_foreach_child(ui_PluginsFoundCont, [&](lv_obj_t *child, unsigned id) {
			auto idx = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(lv_obj_get_user_data(child)));
			if (idx > 0) {
				plugins_to_load.emplace_back(child, idx - 1);
			}
		});
		last_loaded_name = "";
		load_next();
		is_loading_all = true;
	}

	void load_next() {
		if (plugins_to_load.size()) {
			auto [obj, idx] = plugins_to_load.front();
			plugins_to_load.pop_front();

			auto const *found_plugins = plugin_manager.found_plugin_list();
			auto const &plugin = (*found_plugins)[idx];

			// Skip loading different versions of same plugin
			auto this_loaded_name = std::string(plugin.plugin_name);
			if (this_loaded_name == last_loaded_name) {
				load_next();
				return;
			}

			last_loaded_name = std::string(plugin.plugin_name);

			lv_label_set_text_fmt(load_in_progress_label, "Loading All Plugins: %s", plugin.plugin_name.c_str());

			load_in_progress_obj = obj;

			plugin_manager.load_plugin(idx);
		} else {
			end_loading_all();
		}
	}

	PluginManager &plugin_manager;
	NotificationQueue &notify_queue;
	PluginPreloadSettings &settings;
	GuiState &gui_state;
	bool should_write_settings = false;
	PatchPlayLoader &play_loader;
	PluginPopup plugin_state_popup;
	ConfirmPopup confirm_popup;

	lv_obj_t *load_in_progress_obj = nullptr;
	lv_obj_t *load_in_progress_label = nullptr;

	lv_group_t *group = nullptr;

	struct DisplayedPlugins {
		std::optional<unsigned> found_idx;
	};

	lv_obj_t *clear_autoloads_button;
	lv_obj_t *current_autoloads_button;

	lv_obj_t *ram_label;

	// Load all:
	lv_obj_t *load_all_found_button;

	bool is_loading_all = false;
	// bool loading_done = false;
	std::deque<std::pair<lv_obj_t *, uint32_t>> plugins_to_load;

	lv_obj_t *load_all_popup = nullptr;
	lv_group_t *loading_group = nullptr;
	std::string last_loaded_name;
};
} // namespace MetaModule
