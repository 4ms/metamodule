#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "gui/elements/state_names.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "params_state.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

struct ManualControlPopUp {

	ManualControlPopUp(OpenPatchManager &patches, PatchModQueue &patch_mod_queue, PatchPlayLoader &playloader)
		: patch_mod_queue{patch_mod_queue}
		, patches{patches}
		, playloader{playloader}
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

		patch = patches.get_view_patch();
		prepare_control_arc();

		lv_show(ui_ControlAlert);
		visible = true;

		lv_indev_set_group(lv_indev_get_next(nullptr), controlarc_group);
		lv_group_focus_obj(ui_ControlArc);
		lv_group_set_editing(controlarc_group, true);

		auto param_id = drawn_el->gui_element.idx.param_idx;
		auto module_id = drawn_el->gui_element.module_idx;

		auto value = playloader.param_value(module_id, param_id);
		float range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
		lv_arc_set_value(ui_ControlArc, std::round(value * range) + lv_arc_get_min_value(ui_ControlArc));
		update_control_arc_text();
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
	void increment_value() {
		auto new_value = lv_arc_get_value(ui_ControlArc) + 1;
		if (new_value > lv_arc_get_max_value(ui_ControlArc))
			new_value = lv_arc_get_min_value(ui_ControlArc);
		lv_arc_set_value(ui_ControlArc, new_value);
		arc_change_value();
	}

	void press() {
		if (!drawn_el)
			return;

		std::visit(overloaded{
					   // default: do nothing
					   [](const BaseElement &) {},

					   [this](const ParamElement &) {
						   // Generic Param: clicking toggles value 0/100
						   lv_arc_set_value(ui_ControlArc, lv_arc_get_value(ui_ControlArc) > 50 ? 0 : 100);
						   arc_change_value();
					   },

					   [this](const Slider &pot) {
						   float cur_value = lv_arc_get_value(ui_ControlArc);
						   auto cur_arc_range = lv_arc_get_max_value(ui_ControlArc);
						   arc_range_idx = (arc_range_idx + 1) % arc_range_value.size();

						   set_continuous_range(pot);

						   auto new_arc_range = lv_arc_get_max_value(ui_ControlArc);
						   lv_arc_set_value(ui_ControlArc,
											std::round(cur_value / (float)cur_arc_range * (float)new_arc_range));
					   },

					   [this](const Knob &pot) {
						   float cur_value = lv_arc_get_value(ui_ControlArc);
						   auto cur_arc_range = lv_arc_get_max_value(ui_ControlArc);
						   arc_range_idx = (arc_range_idx + 1) % arc_range_value.size();

						   set_continuous_range(pot);

						   auto new_arc_range = lv_arc_get_max_value(ui_ControlArc);
						   lv_arc_set_value(ui_ControlArc,
											std::round(cur_value / (float)cur_arc_range * (float)new_arc_range));
					   },

					   [this](const KnobSnapped &pot) {
						   if (pot.num_pos > 0)
							   increment_value();
					   },

					   // switches: increment value, wrapping
					   [this](const Switch &) { increment_value(); },

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

					   [this](const AltParamChoice &el) { increment_value(); },
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
		arc_range_idx = 0; //default

		if (!drawn_el)
			return;

		hide_resolution_text();

		std::visit(overloaded{
					   [](const BaseElement &) {},
					   [](const ParamElement &) { lv_arc_set_range(ui_ControlArc, 0, 100); },
					   [this](const Knob &knob) { set_continuous_range(knob); },
					   [this](const Slider &slider) { set_continuous_range(slider); },
					   [this](const KnobSnapped &knob) { set_snapped_range(knob); },
					   [](const Button &el) { lv_arc_set_range(ui_ControlArc, 0, 1); },
					   [](const FlipSwitch &el) { lv_arc_set_range(ui_ControlArc, 0, el.num_pos - 1); },
					   [](const SlideSwitch &el) { lv_arc_set_range(ui_ControlArc, 1, el.num_pos); },
					   [](const AltParamChoice &el) { lv_arc_set_range(ui_ControlArc, 1, el.num_pos); },
					   [](const AltParamContinuous &) { lv_arc_set_range(ui_ControlArc, 0, 100); },
				   },
				   drawn_el->element);

		auto name = base_element(drawn_el->element).short_name;
		if (name.size() == 0)
			name = "the control";
		lv_label_set_text_fmt(ui_ControlAlertLabel, "Turn rotary to adjust %.*s", (int)name.size(), name.data());
		lv_label_set_text(ui_ControlAlertAmount, "");
	}

	void set_continuous_range(Pot const &pot) {
		// Use coarse/fine/ultrafine unless value is displayed what we are guessing is an integer with no units
		if (pot.display_mult > 1 && pot.display_mult != 100 && pot.display_base == 0 && pot.units == "") {
			lv_arc_set_range(ui_ControlArc, 0, pot.display_mult);
			hide_resolution_text();
		} else {
			lv_arc_set_range(ui_ControlArc, 0, arc_range_value[arc_range_idx]);
			show_resolution_text();
		}
	}

	void set_snapped_range(KnobSnapped const &knob) {
		if (knob.num_pos > 0) {
			lv_arc_set_range(ui_ControlArc, knob.min_value, knob.max_value);
			hide_resolution_text();
		} else {
			set_continuous_range(knob);
		}
	}

	void arc_change_value() {
		float range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
		auto value = lv_arc_get_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);

		StaticParam sp{
			.module_id = drawn_el->gui_element.module_idx,
			.param_id = drawn_el->gui_element.idx.param_idx,
			.value = (float)value / range, //0/6 1/6 ... 6/6 => 1 2 ... 7
		};
		patch_mod_queue.put(SetStaticParam{.param = sp});

		patch->set_or_add_static_knob_value(sp.module_id, sp.param_id, sp.value);

		update_control_arc_text();
	}

	void update_control_arc_text() {
		auto range = lv_arc_get_max_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);
		auto value = lv_arc_get_value(ui_ControlArc) - lv_arc_get_min_value(ui_ControlArc);

		float val = (float)value / (float)range;

		auto strval = get_element_value_string(drawn_el->element, val, arc_range_value[arc_range_idx]);
		lv_label_set_text(ui_ControlAlertAmount, strval.c_str());
	}

	void hide_resolution_text() {
		lv_hide(ui_ControlAlertResolutionCont);
		lv_label_set_text(ui_ControlAlertClickLabel, "");
		lv_label_set_text(ui_ControlAlertResolution, "");
	}

	void show_resolution_text() {
		lv_show(ui_ControlAlertResolutionCont);
		lv_label_set_text(ui_ControlAlertClickLabel, "Click to change:");
		lv_label_set_text(ui_ControlAlertResolution, arc_range_text[arc_range_idx].data());
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

	const DrawnElement *drawn_el{};
	PatchData *patch{};
	PatchModQueue &patch_mod_queue;
	OpenPatchManager &patches;
	PatchPlayLoader &playloader;

	lv_group_t *controlarc_group = nullptr;
	lv_group_t *prev_group = nullptr;

	unsigned arc_range_idx = 0;
	std::array<unsigned, 3> arc_range_value{100, 1000, 10000};
	std::array<std::string_view, 3> arc_range_text{"Coarse", "Fine", "Ultra-fine"};

public:
	bool visible = true;
};

} // namespace MetaModule
