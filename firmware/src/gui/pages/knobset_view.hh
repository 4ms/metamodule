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
	}

	void prepare_focus() override {
		for (auto label : labels)
			lv_label_set_text(label, "");
		for (auto knob : knobs) {
			lv_arc_set_bg_angles(knob, 120, 60);
			lv_arc_set_mode(knob, LV_ARC_MODE_NORMAL);
		}

		knobset = nullptr;
		patch = patch_storage.get_view_patch();

		if (auto ks_idx = PageList::get_viewing_knobset(); ks_idx < patch.knob_sets.size()) {
			knobset = &patch.knob_sets[ks_idx];
			if (knobset->name.length())
				lv_label_set_text(ui_KnobSetNameText1, knobset->name.c_str());
			else
				lv_label_set_text_fmt(ui_KnobSetNameText1, "Knob Set %ul", ks_idx);

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
						lv_label_set_text_fmt(
							// label, "%s", fullname.element_name.data());
							label,
							"%s\n%s",
							fullname.module_name.data(),
							fullname.element_name.data());
					}
				}

				auto knob = get_knob(map.param_id);
				if (knob) {
					float left = std::min(map.min, map.max);
					float right = std::max(map.min, map.max);
					lv_arc_set_bg_angles(knob, lvgl_knob_angle(left), lvgl_knob_angle(right));
					lv_arc_set_mode(knob, (map.min < map.max) ? LV_ARC_MODE_NORMAL : LV_ARC_MODE_REVERSE);
				}
			}
		}
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				printf_("Back from knobset view\n");
				blur();
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

	unsigned lvgl_knob_angle(float knob_pos) {
		unsigned angle = knob_pos * 300.f + 120.f; //120 .. 359, 0 .. 60
		if (angle > 360)
			angle -= 360;
		return angle;
	}
};

} // namespace MetaModule
