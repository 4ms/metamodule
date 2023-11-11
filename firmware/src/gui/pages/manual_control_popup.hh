#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "gui/elements/state_names.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "patch.hh"
#include "patch_data.hh"
#include "patch_play/patch_mod_queue.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

struct ManualControlPopUp {

	ManualControlPopUp(PatchData &patch, PatchModQueue &patch_mod_queue)
		: patch{patch}
		, patch_mod_queue{patch_mod_queue}
		, controlarc_group(lv_group_create()) {

		lv_group_add_obj(controlarc_group, ui_ControlArc);
		lv_group_set_editing(controlarc_group, true);

		lv_obj_add_event_cb(ui_ControlArc, arc_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ControlArc, click_arc_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlArc, click_arc_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_ControlArc, click_arc_cb, LV_EVENT_LONG_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlArc, click_arc_cb, LV_EVENT_LONG_PRESSED_REPEAT, this);
	}

	void prepare_focus(lv_group_t *cur_group) {
		prev_group = cur_group;
	}

	void show(const DrawnElement *el) {
		if (!el)
			return;
		drawn_el = el;

		prepare_control_arc();

		lv_show(ui_ControlAlert);
		visible = true;

		lv_indev_set_group(lv_indev_get_next(nullptr), controlarc_group);
		lv_group_focus_obj(ui_ControlArc);
		lv_group_set_editing(controlarc_group, true);

		auto param_id = drawn_el->gui_element.idx.param_idx;
		auto module_id = PageList::get_selected_module_id();
		auto cur_val = patch.get_static_knob_value(module_id, param_id);
		if (cur_val) {
			float range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
			lv_arc_set_value(ui_ControlArc, cur_val.value() * range);
			update_control_arc_text();
		}
	}

	void hide() {
		if (visible) {
			visible = false;

			if (prev_group)
				lv_indev_set_group(lv_indev_get_next(nullptr), prev_group);

			lv_hide(ui_ControlAlert);
			lv_group_focus_obj(ui_ControlButton);
		}
	}

private:
	void press() {
		if (!drawn_el)
			return;

		std::visit(overloaded{
					   // default: do nothing
					   [](const BaseElement &) {},

					   // switches: increment value, wrapping
					   [this](const Switch &) {
						   auto new_value = lv_arc_get_value(ui_ControlArc) + 1;
						   if (new_value > lv_arc_get_max_value(ui_ControlArc))
							   new_value = lv_arc_get_min_value(ui_ControlArc);
						   lv_arc_set_value(ui_ControlArc, new_value);
						   arc_change_value();
					   },

					   // latching button: toggle state
					   [this](const LatchingButton &) {
						   lv_arc_set_value(ui_ControlArc, lv_arc_get_value(ui_ControlArc) ? 0 : 1);
						   arc_change_value();
					   },

					   // MomentaryButton: encoder press/release translated to button press/release
					   [this](const MomentaryButton &el) {
						   lv_arc_set_value(ui_ControlArc, 1);
						   arc_change_value();
					   },
				   },
				   drawn_el->element);
		lv_group_focus_obj(ui_ControlArc);
		lv_group_set_editing(controlarc_group, true);
	}

	void release() {
		if (!drawn_el)
			return;

		std::visit(overloaded{
					   [](const BaseElement &) {},
					   [this](const MomentaryButton &el) {
						   lv_arc_set_value(ui_ControlArc, 0);
						   arc_change_value();
					   },
				   },
				   drawn_el->element);
		lv_group_focus_obj(ui_ControlArc);
		lv_group_set_editing(controlarc_group, true);
	}

	void prepare_control_arc() {
		printf("prepare\n");
		if (!drawn_el)
			return;

		printf("visit\n");
		std::visit(overloaded{
					   [](const BaseElement &) {},
					   [](const Button &el) { lv_arc_set_range(ui_ControlArc, 0, 1); },
					   [](const FlipSwitch &el) { lv_arc_set_range(ui_ControlArc, 0, el.num_pos - 1); },
					   [](const SlideSwitch &el) { lv_arc_set_range(ui_ControlArc, 1, el.num_pos); },
					   [](const Pot &) { lv_arc_set_range(ui_ControlArc, 0, 100); },
				   },
				   drawn_el->element);

		auto name = base_element(drawn_el->element).short_name;
		if (name.size() == 0)
			name = "the control";
		lv_label_set_text_fmt(ui_ControlAlertLabel, "Turn rotary to adjust %.*s", (int)name.size(), name.data());
		lv_label_set_text(ui_ControlAlertAmount, "");
		printf("set text done\n");
	}

	void arc_change_value() {
		float range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
		auto value = lv_arc_get_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);

		StaticParam sp{
			.module_id = (uint16_t)PageList::get_selected_module_id(),
			.param_id = drawn_el->gui_element.idx.param_idx,
			.value = (float)value / range, //0/6 1/6 ... 6/6 => 1 2 ... 7
		};
		patch_mod_queue.put(SetStaticParam{.param = sp});
		patch.set_static_knob_value(sp.module_id, sp.param_id, sp.value);

		update_control_arc_text();
	}

	void update_control_arc_text() {
		auto range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
		auto value = lv_arc_get_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);

		float val = (float)value / (float)range;

		auto strval = get_element_value_string(drawn_el->element, val);
		lv_label_set_text(ui_ControlAlertAmount, strval.c_str());
	}

	static void click_arc_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ManualControlPopUp *>(event->user_data);

		if (event->code == LV_EVENT_PRESSED)
			page->press();

		else if (event->code == LV_EVENT_RELEASED)
			page->release();
	}

	static void arc_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ManualControlPopUp *>(event->user_data);
		page->arc_change_value();
	}

	const DrawnElement *drawn_el;
	PatchData &patch;
	PatchModQueue &patch_mod_queue;
	lv_group_t *controlarc_group = nullptr;
	lv_group_t *prev_group = nullptr;

public:
	bool visible = true;
};

} // namespace MetaModule
