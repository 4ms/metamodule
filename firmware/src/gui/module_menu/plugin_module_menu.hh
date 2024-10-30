#pragma once
#include "console/pr_dbg.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/roller_hover_text.hh"
#include "gui/module_menu/base_plugin_menu.hh"
#include "gui/module_menu/native_plugin_menu.hh"
#include "gui/module_menu/vcv_plugin_menu.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "patch_play/patch_playloader.hh"
#include "util/overloaded.hh"
#include <functional>

namespace MetaModule
{

struct PluginModuleMenu {
	PluginModuleMenu(PatchPlayLoader &patch_playloader)
		: roller_hover(ui_ElementRollerPanel, ui_ModuleViewExtraMenuRoller)
		, patch_playloader{patch_playloader} {
		lv_hide(roller);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(roller, roller_scrolled_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(roller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(roller, nullptr, LV_STATE_FOCUS_KEY);

		auto roller_label = lv_obj_get_child(roller, 0);
		lv_label_set_recolor(roller_label, true);

		lv_obj_set_style_text_font(roller, &ui_font_MuseoSansRounded70014, LV_PART_MAIN);
		lv_obj_set_style_text_font(roller, &ui_font_MuseoSansRounded70014, LV_PART_SELECTED);

		auto hover_label = lv_obj_get_child(roller_hover.get_cont(), 0);
		lv_obj_set_style_text_font(hover_label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN);
	}

	bool create_options_menu(unsigned this_module_id) {
		if (auto rack_module = patch_playloader.get_plugin_module<rack::engine::Module>(this_module_id)) {
			plugin_menu = std::make_unique<RackModuleMenu>(rack_module->module_widget);
			return populate_menu_items() > 0;

		} else if (auto native_module = patch_playloader.get_plugin_module<CoreProcessor>(this_module_id)) {
			plugin_menu = std::make_unique<NativeModuleMenu>();
			return populate_menu_items() > 0;
		}

		return false;
	}

	void show() {
		populate_menu_items();

		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		lv_show(roller);
		lv_group_focus_obj(roller);
		if (auto *group = static_cast<lv_group_t *>(lv_obj_get_group(roller)))
			lv_group_set_editing(group, true);
		lv_event_send(roller, LV_EVENT_PRESSED, nullptr);

		roller_hover.hide();

		visible = true;
		should_close = false;
	}

	void hide() {
		if (visible) {
			lv_hide(roller);
			roller_hover.hide();
			visible = false;
			should_close = false;
		}
	}

	void back_event() {
		if (visible) {
			plugin_menu->back_event();

			if (plugin_menu->is_done())
				should_close = true;
			else
				populate_menu_items();
		}
	}

	void update() {
		roller_hover.update();
	}

	bool wants_to_close() {
		return should_close;
	}

	void click(unsigned idx) {
		// First item is "< Back"
		if (idx == 0) {
			back_event();
		} else {
			plugin_menu->click_item(idx - 1);
			refresh_menu_items();
		}
	}

private:
	unsigned populate_menu_items() {
		std::string opts = LV_SYMBOL_LEFT + std::string(" Back\n");

		std::vector<std::string> item_strings;

		if (plugin_menu) {
			item_strings = plugin_menu->get_items();
			for (auto const &item : item_strings) {
				opts += item + "\n";
			}
		} else {
			pr_err("plugin_menu not created\n");
		}

		// Remove final /n
		if (opts.length() > 0)
			opts.pop_back();

		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

		return item_strings.size();
	}

	// Same as populate_menu_items() but keeps current selection
	void refresh_menu_items() {
		auto cur_idx = lv_roller_get_selected(roller);
		auto num_items = populate_menu_items() + 1; // +1 for "< Back" item
		if (cur_idx < num_items)
			lv_roller_set_selected(roller, cur_idx, LV_ANIM_OFF);
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<PluginModuleMenu *>(event->user_data);
		auto idx = lv_roller_get_selected(page->roller);

		page->click(idx);

		// keep editing focus on roller after clicking it
		lv_group_focus_obj(page->roller);
		if (auto *group = static_cast<lv_group_t *>(lv_obj_get_group(page->roller)))
			lv_group_set_editing(group, true);
		lv_event_send(page->roller, LV_EVENT_PRESSED, nullptr);

		// index might be the same, but content probably changed
		page->roller_hover.force_redraw();
	}

	static void roller_scrolled_cb(lv_event_t *event) {
		auto page = static_cast<PluginModuleMenu *>(event->user_data);
		page->roller_hover.hide();
	}

	std::unique_ptr<BasePluginModuleMenu> plugin_menu;

	lv_obj_t *roller = ui_ModuleViewExtraMenuRoller;

	RollerHoverText roller_hover;
	PatchPlayLoader &patch_playloader;

	bool visible = false;
	bool should_close = false;
};

} // namespace MetaModule
