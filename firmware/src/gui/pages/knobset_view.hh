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

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobSetViewPage(PatchInfo info)
		: PageBase{info}
		, base{ui_KnobSetViewPage}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::KnobSetView);
		init_bg(base);
		lv_group_set_editing(group, false);
	}

	void set_for_knob(lv_obj_t *cont, unsigned knob_i) {
		auto knob = get_knob(cont);
		lv_obj_set_style_arc_color(knob, Gui::knob_palette[knob_i % 6], LV_PART_INDICATOR);

		auto circle = get_circle(cont);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[knob_i % 6], LV_STATE_DEFAULT);

		auto circle_letter = get_circle_letter(cont);
		lv_label_set_text(circle_letter, PanelDef::get_map_param_name(knob_i).data());
	}

	void prepare_focus() override {

		for (unsigned i = 0; auto cont : containers) {
			set_for_knob(cont, i);

			auto knob = get_knob(cont);
			lv_arc_set_mode(knob, LV_ARC_MODE_NORMAL);
			lv_arc_set_bg_angles(knob, min_arc, max_arc);
			lv_arc_set_value(knob, 0);

			auto label = get_label(cont);
			lv_label_set_text(label, "");

			disable(cont);

			i++;
		}

		lv_group_remove_all_objs(group);

		knobset = nullptr;
		patch = patch_storage.get_view_patch();

		auto ks_idx = PageList::get_viewing_knobset();
		if (ks_idx >= patch.knob_sets.size())
			return;

		knobset = &patch.knob_sets[ks_idx];
		if (knobset->name.length())
			lv_label_set_text(ui_KnobSetNameText, knobset->name.c_str());
		else
			lv_label_set_text_fmt(ui_KnobSetNameText, "Knob Set %d", (int)ks_idx);

		if (patch.patch_name.length())
			lv_label_set_text(ui_KnobSetDescript, patch.patch_name.c_str());
		else
			lv_label_set_text(ui_KnobSetDescript, "");

		unsigned num_maps[PanelDef::NumKnobs]{};

		for (auto map : knobset->set) {
			if (map.panel_knob_id >= PanelDef::NumKnobs)
				continue;

			lv_obj_t *cont;
			if (num_maps[map.panel_knob_id] == 0) {
				cont = get_container(map.panel_knob_id);
			} else {
				cont = (map.panel_knob_id < 6) ? ui_KnobContainerBig_create(panes[map.panel_knob_id]) :
												 ui_KnobContainer_create(panes[map.panel_knob_id]);
			}
			num_maps[map.panel_knob_id]++;

			auto label = get_label(cont);
			if (label) {
				std::string_view name = map.alias_name;
				if (name.length()) {
					lv_label_set_text(label, name.data());
				} else {
					auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, patch);
					lv_label_set_text_fmt(label, "%s\n%s", fullname.module_name.data(), fullname.element_name.data());
				}
			}

			auto knob = get_knob(cont);
			if (knob) {
				// Set min/max of arc
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

			set_for_knob(cont, map.panel_knob_id);

			enable(cont);
			lv_group_add_obj(group, cont);
		}

		lv_group_set_editing(group, false);
	}

	void update() override {
		lv_group_set_editing(group, false);
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}

		bool is_patch_playing = PageList::get_selected_patch_location() == patch_playloader.cur_patch_location();
		if (is_patch_playing) {
			for (unsigned i = 0; i < params.knobs.size(); i++) {
				if (auto val = ElementUpdate::get_mapped_param_value(params, i); val.has_value()) {
					unsigned lv_pos = val.value() * 120.f;
					lv_arc_set_value(get_knob(i), lv_pos);
				}
			}
		}
	}

	void blur() final {
		// Clear all containers except for the original ones
		for (auto [pane, cont] : zip(panes, containers)) {
			auto num_children = lv_obj_get_child_cnt(pane);
			for (auto i = 0u; i < num_children; i++) {
				auto child = lv_obj_get_child(pane, i);
				if (child != cont)
					lv_obj_del_async(child);
			}
		}
	}

private:
	lv_obj_t *base = nullptr;
	MappedKnobSet *knobset = nullptr;
	PatchData &patch;

	std::array<lv_obj_t *, 12> panes{ui_KnobPanelA,
									 ui_KnobPanelB,
									 ui_KnobPanelC,
									 ui_KnobPanelD,
									 ui_KnobPanelE,
									 ui_KnobPanelF,
									 ui_KnobPanelU,
									 ui_KnobPanelV,
									 ui_KnobPanelW,
									 ui_KnobPanelX,
									 ui_KnobPanelY,
									 ui_KnobPanelZ};

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
	lv_obj_t *get_container(unsigned panel_knob_id) {
		return containers[panel_knob_id];
	}

	lv_obj_t *get_knob(unsigned panel_knob_id) {
		if (panel_knob_id >= 12)
			return nullptr;
		if (panel_knob_id >= 6)
			return ui_comp_get_child(get_container(panel_knob_id), UI_COMP_KNOBCONTAINER_KNOB);
		else
			return ui_comp_get_child(get_container(panel_knob_id), UI_COMP_KNOBCONTAINERBIG_KNOB);
	}

	lv_obj_t *get_knob(lv_obj_t *container) {
		return ui_comp_get_child(container, UI_COMP_KNOBCONTAINER_KNOB);
	}

	lv_obj_t *get_label(lv_obj_t *container) {
		return ui_comp_get_child(container, UI_COMP_KNOBCONTAINER_LABEL);
	}

	lv_obj_t *get_circle(lv_obj_t *container) {
		return ui_comp_get_child(container, UI_COMP_KNOBCONTAINER_CIRCLE);
	}

	lv_obj_t *get_circle_letter(lv_obj_t *container) {
		return ui_comp_get_child(container, UI_COMP_KNOBCONTAINERBIG_CIRCLE_KNOBLETTER);
	}

	void disable(lv_obj_t *container) {
		auto knob = get_knob(container);
		auto circle = get_circle(container);
		auto label = get_label(container);
		if (!knob || !circle || !label)
			return;
		lv_obj_add_state(knob, LV_STATE_DISABLED);
		lv_obj_add_state(circle, LV_STATE_DISABLED);
		lv_obj_add_state(label, LV_STATE_DISABLED);
	}

	void enable(lv_obj_t *container) {
		auto knob = get_knob(container);
		auto circle = get_circle(container);
		auto label = get_label(container);
		if (!knob || !circle || !label)
			return;
		lv_obj_clear_state(knob, LV_STATE_DISABLED);
		lv_obj_clear_state(circle, LV_STATE_DISABLED);
		lv_obj_clear_state(label, LV_STATE_DISABLED);
	}

	uint16_t lvgl_knob_angle(float knob_pos) {
		knob_pos = std::clamp<float>(knob_pos, 0.f, 1.f);
		uint16_t angle = knob_pos * (360 + max_arc - min_arc) + min_arc;
		if (angle > 360)
			angle -= 360;
		return angle;
	}
};

} // namespace MetaModule
