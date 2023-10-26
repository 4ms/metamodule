#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/knob_arc.hh"
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
		lv_label_set_text(ui_KnobSetNameText, patch.valid_knob_set_name(ks_idx));

		if (patch.patch_name.length())
			lv_label_set_text(ui_KnobSetDescript, patch.patch_name.c_str());
		else
			lv_label_set_text(ui_KnobSetDescript, "");

		unsigned num_maps[PanelDef::NumKnobs]{};

		for (auto [idx, map] : enumerate(knobset->set)) {
			if (!map.is_panel_knob())
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

			auto s_param = patch.find_static_knob(map.module_id, map.param_id);
			float val = s_param ? s_param->value : 0;
			set_knob_arc<min_arc, max_arc>(map, get_knob(cont), val);

			set_for_knob(cont, map.panel_knob_id);

			enable(cont);
			lv_group_add_obj(group, cont);

			lv_obj_remove_event_cb(cont, mapping_cb);
			lv_obj_add_event_cb(cont, mapping_cb, LV_EVENT_RELEASED, this);

			lv_obj_set_user_data(cont, reinterpret_cast<void *>(idx)); //Dangerous? "ptr" is actually an integer

			if (idx == PageList::get_selected_mappedknob_id())
				lv_group_focus_obj(cont);
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
			// Iterate all knobs
			for (auto knob_i = 0u; knob_i < params.knobs.size(); knob_i++) {
				// Find the knobs that have moved
				if (auto knobpos = ElementUpdate::get_mapped_param_value(params, knob_i); knobpos.has_value()) {
					// Iterate all containers in the pane for this knob
					auto pane = panes[knob_i];
					auto num_children = lv_obj_get_child_cnt(pane);
					for (unsigned i = 0; i < num_children; i++) {
						auto cont = lv_obj_get_child(pane, i);
						if (!cont)
							continue;
						auto map_idx = reinterpret_cast<uintptr_t>(lv_obj_get_user_data(cont));
						if (map_idx < knobset->set.size()) {
							unsigned lv_pos = knobpos.value() * 120.f;
							lv_arc_set_value(get_knob(cont), lv_pos);
						}
					}
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

	static void mapping_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		auto obj = event->current_target;
		if (!obj)
			return;

		auto view_set_idx = PageList::get_viewing_knobset();
		if (view_set_idx >= page->patch.knob_sets.size())
			return;

		auto map_idx = reinterpret_cast<uintptr_t>(obj->user_data);
		if (map_idx >= page->patch.knob_sets[view_set_idx].set.size())
			return;

		PageList::set_selected_mappedknob_id(map_idx);

		// auto &mk = page->patch.knob_sets[view_set_idx].set[map_idx];
		// printf_("set[] MappedKnob idx: %d\n", (unsigned)map_idx);
		// printf_("panel: %d -> m:%d p:%d\n", mk.panel_knob_id, mk.module_id, mk.param_id);

		PageList::request_new_page(PageId::KnobMap);
	}

private:
	void set_for_knob(lv_obj_t *cont, unsigned knob_i) {
		auto knob = get_knob(cont);
		lv_obj_set_style_arc_color(knob, Gui::knob_palette[knob_i % 6], LV_PART_INDICATOR);

		auto circle = get_circle(cont);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[knob_i % 6], LV_STATE_DEFAULT);

		auto circle_letter = get_circle_letter(cont);
		lv_label_set_text(circle_letter, PanelDef::get_map_param_name(knob_i).data());
	}

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
};

} // namespace MetaModule
