#pragma once
#include "gui/styles.hh"
#include "lvgl.h"
#include "page_list.hh"
#include "patch/patch_data.hh"
#include "printf.h"
#include <vector>

extern "C" {
#include "gui/slsexport/meta5/ui.h"
}

namespace MetaModule
{

struct PatchViewKnobsetMenu {

	struct Settings {
		uint32_t active_knobset = 0;
		bool changed = false;
	};

	PatchViewKnobsetMenu(Settings &settings)
		: settings{settings} {
	}

	void init() {
		static bool already_init = false;
		if (!already_init) {
			lv_obj_set_parent(ui_KnobsetMenu, lv_layer_top());
			lv_obj_add_event_cb(ui_KnobButton, knob_button_cb, LV_EVENT_PRESSED, this);
			lv_obj_add_event_cb(ui_KnobsetCloseButton, knob_button_cb, LV_EVENT_PRESSED, this);

			visible = false;
			lv_obj_set_x(ui_KnobsetMenu, 220);

			knobset_list.reserve(MaxKnobSets);

			already_init = true;
		}
	}

	void focus(lv_group_t *group, std::vector<MappedKnobSet> &knobsets) {

		base_group = group;
		knobset_menu_group = lv_group_create();
		lv_group_remove_all_objs(knobset_menu_group);
		lv_group_set_editing(knobset_menu_group, false);
		lv_group_add_obj(knobset_menu_group, ui_KnobsetCloseButton);

		for (const auto &knobset : knobsets) {
			if (knobset.set.size()) {
				auto panel = ui_KnobSetGroup_create(ui_KnobsetMenu);
				auto check = ui_comp_get_child(panel, UI_COMP_KNOBSETGROUP_KNOBSETBUTTON);
				auto label = ui_comp_get_child(panel, UI_COMP_KNOBSETGROUP_KNOBSETNAME);
				if (knobset.name.length())
					lv_label_set_text(label, knobset.name.c_str());
				else {
					char text[32];
					snprintf_(text, 32, "KnobSet: %d", (int)knobset_list.size() + 1);
					lv_label_set_text(label, text);
				}

				// Switch checkbox
				if (settings.active_knobset == knobset_list.size())
					lv_obj_add_state(check, LV_STATE_CHECKED);
				else
					lv_obj_clear_state(check, LV_STATE_CHECKED);
				lv_obj_add_event_cb(check, knobset_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
				lv_group_add_obj(knobset_menu_group, check);

				knobset_list.push_back(panel);
			}
		}

		if (knobset_list.size() == 0) {
			auto panel = ui_KnobSetGroup_create(ui_KnobsetMenu);
			auto check = ui_comp_get_child(panel, UI_COMP_KNOBSETGROUP_KNOBSETBUTTON);
			auto label = ui_comp_get_child(panel, UI_COMP_KNOBSETGROUP_KNOBSETNAME);
			lv_label_set_text(label, "Default");
			lv_obj_add_state(check, LV_STATE_CHECKED);
			lv_group_add_obj(knobset_menu_group, check);
			knobset_list.push_back(panel);
		}
	}

	void blur() {
		if (knobset_menu_group) {
			lv_group_del(knobset_menu_group);
			knobset_menu_group = nullptr;
		}
		for (auto *c : knobset_list) {
			lv_obj_del(c);
		}
		knobset_list.clear();
	}

	void show() {
		if (!visible) {
			Dropdown_Animation(ui_KnobsetMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			lv_indev_set_group(indev, knobset_menu_group);
			lv_group_focus_obj(ui_KnobsetCloseButton);
			lv_obj_clear_state(ui_KnobsetCloseButton, LV_STATE_PRESSED);
			lv_obj_scroll_to_y(ui_KnobsetMenu, 0, LV_ANIM_OFF);
			visible = true;
		}
	}

	void hide() {
		if (visible) {
			Dropup_Animation(ui_KnobsetMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			if (base_group)
				lv_indev_set_group(indev, base_group);
			lv_obj_clear_state(ui_KnobButton, LV_STATE_PRESSED);
			visible = false;
		}
	}

	static void knob_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewKnobsetMenu *>(event->user_data);

		if (page->visible) {
			page->hide();
		} else {
			page->show();
		}
	}

	static void knobset_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_event_code_t event_code = lv_event_get_code(event);
		auto obj = lv_event_get_target(event);

		if (event_code == LV_EVENT_VALUE_CHANGED) {
			// Can't uncheck
			if (!lv_obj_has_state(obj, LV_STATE_CHECKED)) {
				lv_obj_add_state(obj, LV_STATE_CHECKED);
				return;
			}

			auto page = static_cast<PatchViewKnobsetMenu *>(event->user_data);

			for (unsigned i = 0; auto *panel : page->knobset_list) {
				auto check = ui_comp_get_child(panel, UI_COMP_KNOBSETGROUP_KNOBSETBUTTON);

				if (check == obj) {
					if (i != page->settings.active_knobset) {
						page->settings.active_knobset = i;
						page->settings.changed = true;
					}
					continue;
				}

				if (lv_obj_has_state(check, LV_STATE_CHECKED)) {
					lv_obj_clear_state(check, LV_STATE_CHECKED);
				}

				i++;
			}
		}
	}

	lv_group_t *base_group;
	lv_group_t *knobset_menu_group = nullptr;
	bool visible = false;
	Settings &settings;
	std::vector<lv_obj_t *> knobset_list;
};

} // namespace MetaModule
