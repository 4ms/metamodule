#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobSetViewPage : PageBase {

	KnobSetViewPage(PatchInfo info)
		: PageBase{info}
		, base{ui_KnobSetViewPage}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::KnobSetView);
		init_bg(base);
		lv_group_set_editing(group, false);
	}

	void prepare_focus() override {
		for (auto cont : containers) {
			lv_obj_set_style_radius(cont, 8, LV_STATE_FOCUSED);
			lv_obj_set_style_border_color(cont, lv_color_hex(0xFF9D41), LV_STATE_FOCUSED);
			lv_obj_set_style_border_opa(cont, LV_OPA_50, LV_STATE_FOCUSED);
			lv_obj_set_style_border_width(cont, 2, LV_STATE_FOCUSED);
			lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		}
		for (auto label : labels)
			lv_label_set_text(label, "");
		for (auto knob : knobs) {
			lv_arc_set_mode(knob, LV_ARC_MODE_NORMAL);
			lv_arc_set_bg_angles(knob, 120, 60);
			lv_arc_set_value(knob, 0);
			lv_obj_add_state(knob, LV_STATE_DISABLED);
		}

		lv_group_remove_all_objs(group);

		knobset = nullptr;
		patch = patch_storage.get_view_patch();

		auto ks_idx = PageList::get_viewing_knobset();
		if (ks_idx >= patch.knob_sets.size())
			return;

		knobset = &patch.knob_sets[ks_idx];
		if (knobset->name.length())
			lv_label_set_text(ui_KnobSetNameText1, knobset->name.c_str());
		else
			lv_label_set_text_fmt(ui_KnobSetNameText1, "Knob Set %d", (int)ks_idx);

		if (patch.patch_name.length())
			lv_label_set_text(ui_KnobSetDescript1, patch.patch_name.c_str());
		else
			lv_label_set_text(ui_KnobSetDescript1, "");

		for (auto map : knobset->set) {
			auto label = get_label(map.panel_knob_id);
			if (label) {
				std::string_view name = map.alias_name;
				if (name.length()) {
					lv_label_set_text(label, name.data());
				} else {
					auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, patch);
					lv_label_set_text_fmt(label, "%s\n%s", fullname.module_name.data(), fullname.element_name.data());
				}
			}

			auto knob = get_knob(map.panel_knob_id);
			if (knob) {
				// Set min/max of arc
				lv_obj_clear_state(knob, LV_STATE_DISABLED);
				lv_arc_set_mode(knob, (map.min < map.max) ? LV_ARC_MODE_NORMAL : LV_ARC_MODE_REVERSE);
				float left = std::min<float>(map.min, map.max);
				float right = std::max<float>(map.min, map.max);
				lv_arc_set_bg_angles(knob, lvgl_knob_angle(left), lvgl_knob_angle(right));

				// Set initial value
				if (map.panel_knob_id < params.knobs.size()) {
					float val = params.knobs[map.panel_knob_id];
					lv_arc_set_value(knob, (uint16_t)(val * 120));
				}
			}
		}

		for (auto [container, label] : zip(containers, labels)) {
			if (lv_label_get_text(label)[0] != '\0')
				lv_group_add_obj(group, container);
			if (container == ui_KnobContainerU)
				lv_group_add_obj(group, ui_KnobContainerU1);
		}
		lv_group_set_editing(group, false);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}

		bool is_patch_playing = true;
		if (is_patch_playing) {
			for (unsigned i = 0; i < params.knobs.size(); i++) {
				if (auto val = ElementUpdate::get_mapped_param_value(params, i); val.has_value()) {
					unsigned lv_pos = val.value() * 120.f;
					lv_arc_set_value(get_knob(i), lv_pos);
					printf_("Updated %d\n", i);
				}
			}
		}
	}

	void blur() final {
	}

private:
	lv_obj_t *base = nullptr;
	MappedKnobSet *knobset = nullptr;
	PatchData &patch;

	std::array<lv_obj_t *, 12> labels{ui_LabelA,
									  ui_LabelB,
									  ui_LabelC,
									  ui_LabelD,
									  ui_LabelE,
									  ui_LabelF,
									  ui_LabelU,
									  ui_LabelV,
									  ui_LabelW,
									  ui_LabelX,
									  ui_LabelY,
									  ui_LabelZ};
	lv_obj_t *get_label(unsigned panel_knob_id) {
		if (panel_knob_id >= 12)
			return nullptr;
		return labels[panel_knob_id];
	}

	std::array<lv_obj_t *, 12> knobs{ui_KnobA,
									 ui_KnobB,
									 ui_KnobC,
									 ui_KnobD,
									 ui_KnobE,
									 ui_KnobF,
									 ui_KnobU,
									 ui_KnobV,
									 ui_KnobW,
									 ui_KnobX,
									 ui_KnobY,
									 ui_KnobZ};
	auto get_knob(unsigned panel_knob_id) -> lv_obj_t * {
		if (panel_knob_id >= 12)
			return nullptr;
		return knobs[panel_knob_id];
	}

	std::array<lv_obj_t *, 12> containers{ui_KnobContainerA,
										  ui_KnobContainerB,
										  ui_KnobContainerC,
										  ui_KnobContainerD,
										  ui_KnobContainerE,
										  ui_KnobContainerF,
										  ui_KnobContainerU,
										  ui_KnobContainerV,
										  ui_KnobContainerW,
										  ui_KnobContainerX,
										  ui_KnobContainerY,
										  ui_KnobContainerZ};
	auto get_container(unsigned panel_knob_id) -> lv_obj_t * {
		if (panel_knob_id >= 12)
			return nullptr;
		return containers[panel_knob_id];
	}

	uint16_t lvgl_knob_angle(float knob_pos) {
		knob_pos = std::clamp<float>(knob_pos, 0.f, 1.f);
		uint16_t angle = knob_pos * 300.f + 120.f; //120 .. 359, 0 .. 60
		if (angle > 360)
			angle -= 360;
		return angle;
	}
};

} // namespace MetaModule
