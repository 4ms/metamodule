#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct PluginTab {

	PluginTab(PluginManager &plugin_manager, NotificationQueue &notify_queue)
		: plugin_manager{plugin_manager}
		, notify_queue{notify_queue} {

		clear_loaded_list();
		clear_found_list();
		lv_show(ui_PluginScanButton);
		lv_obj_add_event_cb(ui_PluginScanButton, scan_plugins_cb, LV_EVENT_CLICKED, this);
		lv_hide(ui_PluginsFoundCont);
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
			lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsLoadedCont, plugin.fileinfo.plugin_name.c_str());
			lv_group_add_obj(group, plugin_obj);
		}
	}

	bool plugin_already_loaded(StaticString<255> const &name) {
		// This next line makes it crash? Why?
		// auto const &loaded_plugin_list = plugin_manager.loaded_plugins();
		// for (auto &plugin : loaded_plugin_list) {
		// if (plugin.fileinfo.plugin_name == name) {
		// 	return true;
		// }
		// }
		return false;
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;
		lv_show(ui_PluginScanButton);
		lv_hide(ui_PluginsFoundCont);
		lv_group_remove_obj(ui_PluginScanButton);
		lv_group_remove_obj(ui_PluginsBuiltinListText);
		lv_group_add_obj(group, ui_PluginScanButton);
		lv_group_add_obj(group, ui_PluginsBuiltinListText);
		lv_group_focus_obj(ui_PluginScanButton);

		clear_found_list();
		clear_loaded_list();
		populate_loaded_list();
	}

	void update() {
		auto result = plugin_manager.process_loading();

		if (result.state == PluginFileLoader::State::GotList) {
			lv_hide(ui_PluginScanButton);
			lv_show(ui_PluginsFoundCont);

			clear_found_list();

			bool first_item = true;
			auto *found_plugins = plugin_manager.found_plugin_list();

			for (unsigned idx = 0; auto plugin : *found_plugins) {

				if (!plugin_already_loaded(plugin.plugin_name)) {
					// Strip .so
					auto pluginname = std::string{std::string_view{plugin.plugin_name}};
					if (pluginname.ends_with(".so")) {
						pluginname = pluginname.substr(0, pluginname.length() - 3);
					}

					lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsFoundCont, pluginname.c_str());
					lv_group_add_obj(group, plugin_obj);

					if (first_item) {
						lv_group_focus_obj(plugin_obj);
						first_item = false;
					}

					lv_obj_set_user_data(plugin_obj, (void *)(idx + 1));
					lv_obj_add_event_cb(plugin_obj, load_plugin_cb, LV_EVENT_CLICKED, this);
				}

				idx++;
			}
		}

		else if (result.state == PluginFileLoader::State::Success)
		{
			if (load_in_progress_idx.has_value()) {
				auto plugin_obj = lv_obj_get_child(ui_PluginsFoundCont, *load_in_progress_idx);
				lv_obj_set_user_data(plugin_obj, nullptr);
				lv_obj_remove_event_cb(plugin_obj, load_plugin_cb);
				lv_obj_set_parent(plugin_obj, ui_PluginsLoadedCont);
				lv_group_remove_obj(plugin_obj);
				load_in_progress_idx = std::nullopt;
			}
		}

		if (result.error_message.length()) {
			pr_err("Error: %s\n", result.error_message.c_str());
			std::string err = "Error loading plugin: " + result.error_message;
			notify_queue.put({err, Notification::Priority::Error});
		}
	}

private:
	static void scan_plugins_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;
		page->plugin_manager.start_loading_plugin_list();
	}

	static void load_plugin_cb(lv_event_t *event) {
		auto page = static_cast<PluginTab *>(event->user_data);
		if (!page)
			return;

		auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
		if (idx > 0) {
			page->plugin_manager.load_plugin(idx - 1);
			page->load_in_progress_idx = idx - 1;
		}
	}

	PluginManager &plugin_manager;
	NotificationQueue &notify_queue;

	std::optional<unsigned> load_in_progress_idx{};

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
