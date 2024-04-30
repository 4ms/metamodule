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
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;
		plugin_manager.start_loading_plugin_list();
	}

	void update() {
		auto result = plugin_manager.process_loading();

		if (result.state == PluginFileLoader::State::GotList) {
			lv_foreach_child(ui_PluginsFoundCont, [](auto *obj) { lv_obj_delete_async(obj); });

			auto *found_plugins = plugin_manager.found_plugin_list();
			for (auto &plugin : *found_plugins) {
				printf("Found: %s\n", plugin.plugin_name.c_str());

				lv_obj_t *plugin_obj = create_plugin_list_item(ui_PluginsFoundCont, plugin.plugin_name.c_str());
				lv_group_add_obj(group, plugin_obj);
				lv_obj_add_event_cb(plugin_obj, load_plugin_cb, LV_EVENT_CLICKED, this);
			}
		}

		if (result.error_message.length()) {
			pr_err("Error: %s\n", result.error_message.c_str());
			std::string err = "Error loading plugin: " + result.error_message;
			notify_queue.put({err, Notification::Priority::Error});
		}
	}

private:
	static void load_plugin_cb(lv_event_t *event) {
	}

	PluginManager &plugin_manager;
	NotificationQueue &notify_queue;

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
