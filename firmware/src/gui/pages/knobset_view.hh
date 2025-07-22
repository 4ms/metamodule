#pragma once
#include <algorithm>

#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/pages/base.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/module_view/mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "src/core/lv_event.h"
#include "src/widgets/lv_textarea.h"

namespace MetaModule
{
struct KnobSetViewPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobSetViewPage(PatchContext info)
		: PageBase{info, PageId::KnobSetView}
		, base{ui_KnobSetViewPage}
		, patch{patches.get_view_patch()} {
		init_bg(base);
		lv_group_set_editing(group, false);

		// Use Prev button for Jack Map
		lv_show(ui_PreviousKnobSet);
		lv_obj_add_event_cb(ui_PreviousKnobSet, goto_jackmap_cb, LV_EVENT_CLICKED, this);
		// lv_obj_add_event_cb(ui_PreviousKnobSet, prev_knobset_cb, LV_EVENT_CLICKED, this);
		lv_label_set_text(ui_PreviousKnobSetLabel, "Jacks");

		lv_obj_add_event_cb(ui_KnobSetNameText, rename_knobset_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_NextKnobSet, next_knobset_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ActivateKnobSet, activate_knobset_cb, LV_EVENT_CLICKED, this);

		lv_hide(ui_KnobSetDescript);

		kb_popup.init(base, group);
	}

	void prepare_focus() override {
		reset_keyboard();

		clear_containers();

		knobset = nullptr;
		arcs.clear();
		indicators.clear();

		for (auto &m : num_maps)
			m = 0;

		update_active_status();

		patch = patches.get_view_patch();

		if (patch->knob_sets.size() > 1) {
			lv_show(ui_NextKnobSet);
		} else {
			lv_hide(ui_NextKnobSet);
		}
		lv_group_add_obj(group, ui_PreviousKnobSet);
		lv_group_add_obj(group, ui_KnobSetNameText);
		lv_group_add_obj(group, ui_ActivateKnobSet);
		lv_group_add_obj(group, ui_NextKnobSet);

		// Set Knobset
		if (!args.view_knobset_id)
			return;
		auto ks_idx = args.view_knobset_id.value();
		if (ks_idx >= patch->knob_sets.size())
			return;
		knobset = &patch->knob_sets[ks_idx];

		update_knobset_text_area();

		// Set mappings in knobset
		for (auto &m : num_maps)
			m = 0;
		arcs.resize(knobset->set.size());
		indicators.resize(knobset->set.size());

		lv_obj_t *focus{};

		for (auto [idx, map] : enumerate(knobset->set)) {
			if (!map.is_panel_knob())
				continue;

			lv_obj_t *cont{};
			if (num_maps[map.panel_knob_id] == 0) {
				cont = get_container(map.panel_knob_id);
			} else {
				cont = (map.panel_knob_id < 6) ? ui_KnobContainerBig_create(panes[map.panel_knob_id]) :
												 ui_KnobContainer_create(panes[map.panel_knob_id]);
			}
			num_maps[map.panel_knob_id]++;

			if (auto label = get_label(cont)) {
				std::string_view name = map.alias_name;
				if (name.length()) {
					lv_label_set_text(label, name.data());
				} else {
					auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, *patch);
					lv_label_set_text_fmt(label, "%s - %s", fullname.element_name.data(), fullname.module_name.data());
				}
			}

			set_knob_arc<min_arc, max_arc>(map, get_knob(cont), 0);

			set_for_knob(cont, map.panel_knob_id);

			lv_obj_remove_event_cb(cont, mapping_cb);
			lv_obj_add_event_cb(cont, mapping_cb, LV_EVENT_CLICKED, this);

			arcs[idx] = get_knob(cont);
			indicators[idx] = get_indicator(cont);

			lv_obj_set_user_data(cont, reinterpret_cast<void *>(idx));

			if (idx == args.mappedknob_id)
				focus = cont;
			else if (idx == 0 && !args.mappedknob_id) {
				if (lv_obj_has_flag(ui_NextKnobSet, LV_OBJ_FLAG_HIDDEN))
					focus = cont;
				else
					focus = ui_NextKnobSet;
			}
		}

		for (auto [idx, pane] : enumerate(panes)) {
			if (!num_maps[idx])
				continue;

			lv_foreach_child(pane, [this](lv_obj_t *cont, int idx) { lv_group_add_obj(group, cont); });
		}

		lv_group_focus_obj(focus);

		lv_group_set_editing(group, false);

		display_active_status();
	}

	void update() override {
		if (!kb_visible)
			lv_group_set_editing(group, false);

		if (gui_state.back_button.is_just_released()) {
			if (kb_visible) {
				if (knobset->name.is_equal(lv_textarea_get_text(ui_KnobSetNameText))) {
					save_knobset_name(false);
				} else {
					kb_popup.show(
						[this](bool ok) { save_knobset_name(ok); }, "Do you want to keep your edits?", "Keep");
				}
			} else if (page_list.request_last_page()) {
				blur();
			} else if (kb_popup.is_visible()) {
				kb_popup.hide();
			}
		}

		handle_changed_active_status();

		if (knobset) {
			for (auto idx = 0u; auto const &map : knobset->set) {
				auto value = patch_playloader.param_value(map.module_id, map.param_id);

				auto arc_val = map.unmap_val(value) * 120.f;
				lv_arc_set_value(arcs[idx], arc_val);

				if (map.is_panel_knob()) {
					auto phys_val = params.knobs[map.panel_knob_id].val;
					auto mapped_phys_val = map.get_mapped_val(phys_val);

					auto is_tracking = patch_playloader.is_param_tracking(map.module_id, map.param_id);
					update_indicator(indicators[idx], is_tracking, mapped_phys_val);
					update_knob(arcs[idx], is_tracking, arc_val);
				}

				idx++;
			}
		}

		poll_patch_file_changed();

		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;
			if (kb_popup.is_visible())
				kb_popup.hide();
			prepare_focus();
		}
	}

	void update_indicator(lv_obj_t *indicator, bool is_tracking, float val) {
		if (is_tracking) {
			lv_hide(indicator);
		} else {
			lv_obj_set_style_transform_angle(indicator, val * 2500.f - 1250.f, LV_PART_MAIN);
			lv_show(indicator);
		}
	}

	void update_knob(lv_obj_t *arc, bool is_tracking, float arc_val) {
		if (arc_val > lv_arc_get_max_value(arc) || arc_val < lv_arc_get_min_value(arc)) {
			lv_obj_set_style_radius(arc, 0, LV_PART_KNOB);
			lv_obj_set_style_bg_color(arc, lv_color_hex(0x000000), LV_PART_KNOB);
		} else {
			lv_obj_set_style_radius(arc, 20, LV_PART_KNOB);

			if (is_tracking) {
				lv_obj_set_style_bg_color(arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
			} else {
				lv_obj_set_style_bg_color(arc, lv_color_hex(0xAAAAAA), LV_PART_KNOB);
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
	void reset_keyboard() {
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_obj_set_parent(ui_Keyboard, ui_KnobSetViewPage);
		lv_obj_set_y(ui_Keyboard, 40);

		lv_hide(ui_Keyboard);
	}

	void clear_containers() {
		for (unsigned i = 0; auto cont : containers) {
			set_for_knob(cont, i);

			auto knob = get_knob(cont);
			lv_arc_set_mode(knob, LV_ARC_MODE_NORMAL);
			lv_arc_set_bg_angles(knob, min_arc, max_arc);
			lv_arc_set_value(knob, 0);

			auto label = get_label(cont);
			lv_label_set_text(label, "");

			i++;
		}
		lv_group_remove_all_objs(group);
	}

	void jump_to_active_knobset() {
		// When changing knobsets with button+knob, then
		// jump to the new active knobset
		if (last_known_active_knobset != page_list.get_active_knobset()) {

			page_list.request_new_page_no_history(
				PageId::KnobSetView,
				{.patch_loc_hash = args.patch_loc_hash, .view_knobset_id = page_list.get_active_knobset()});

			last_known_active_knobset = page_list.get_active_knobset();
		}
	}

	void update_active_status() {
		is_patch_playing = patch_is_playing(args.patch_loc_hash);

		if (is_patch_playing && args.view_knobset_id.value_or(999) == page_list.get_active_knobset())
			is_actively_playing = true;
		else
			is_actively_playing = false;
	}

	void handle_changed_active_status() {
		jump_to_active_knobset();

		auto was_actively_playing = is_actively_playing;

		update_active_status();

		if (was_actively_playing != is_actively_playing) {
			display_active_status();
		}
	}

	void display_active_status() {
		lv_show(ui_ActivateKnobSet, !is_actively_playing && is_patch_playing);

		for (auto [knob_i, pane] : enumerate(panes)) {
			auto num_children = lv_obj_get_child_cnt(pane);
			for (auto i = 0u; i < num_children; i++) {
				auto child = lv_obj_get_child(pane, i);
				update_enabled_status(child, knob_i, is_actively_playing);
			}
		}
	}

	void show_keyboard() {
		lv_show(ui_Keyboard);
		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);
		lv_keyboard_set_textarea(ui_Keyboard, ui_KnobSetNameText);
		kb_visible = true;
		lv_obj_add_state(ui_KnobSetNameText, LV_STATE_USER_1);
	}

	void save_knobset_name(bool save) {
		lv_obj_clear_state(ui_KnobSetNameText, LV_STATE_USER_1);
		lv_group_focus_obj(ui_KnobSetNameText);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);
		kb_visible = false;

		if (save) {
			knobset->name = lv_textarea_get_text(ui_KnobSetNameText);
			patches.mark_view_patch_modified();
		}

		update_knobset_text_area();
	}

	void update_knobset_text_area() {
		if (!args.view_knobset_id)
			return;
		auto ks_idx = args.view_knobset_id.value();
		if (ks_idx >= patch->knob_sets.size())
			return;
		knobset = &patch->knob_sets[ks_idx];
		knobset->name = patch->valid_knob_set_name(ks_idx);
		lv_textarea_set_text(ui_KnobSetNameText, knobset->name.c_str());
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->save_knobset_name(true);
		}
	}

	static void rename_knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobSetViewPage *>(event->user_data);
		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			page->show_keyboard();
		}
	}

	static void mapping_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		auto obj = event->current_target;
		if (!obj)
			return;

		auto view_set_idx = page->args.view_knobset_id.value_or(0xFFFF);
		if (view_set_idx >= page->patch->knob_sets.size())
			return;

		auto map_idx = reinterpret_cast<uintptr_t>(obj->user_data);
		if (map_idx >= page->patch->knob_sets[view_set_idx].set.size())
			return;

		page->args.mappedknob_id = map_idx;
		page->page_list.request_new_page(PageId::KnobMap, page->args);
	}

	static void next_knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		if (auto cur_id = page->args.view_knobset_id) {
			if (page->args.view_knobset_id >= page->patch->knob_sets.size() - 1)
				page->args.view_knobset_id = 0;
			else
				page->args.view_knobset_id = cur_id.value() + 1;

			page->page_list.request_new_page_no_history(
				PageId::KnobSetView,
				{.patch_loc_hash = page->args.patch_loc_hash, .view_knobset_id = page->args.view_knobset_id});
		}
	}

	static void prev_knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		if (auto cur_id = page->args.view_knobset_id) {
			if (page->args.view_knobset_id == 0)
				page->args.view_knobset_id = page->patch->knob_sets.size() - 1;
			else
				page->args.view_knobset_id = cur_id.value() - 1;

			page->page_list.request_new_page_no_history(
				PageId::KnobSetView,
				{.patch_loc_hash = page->args.patch_loc_hash, .view_knobset_id = page->args.view_knobset_id});
		}
	}

	static void goto_jackmap_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobSetViewPage *>(event->user_data);
		page->page_list.request_new_page_no_history(PageId::JackMapView, page->args);
	}

	static void activate_knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		if (page->args.view_knobset_id.has_value())
			page->activate_knobset(page->args.view_knobset_id.value());
	}

	void activate_knobset(unsigned knobset_idx) {
		args.view_knobset_id = knobset_idx;
		page_list.set_active_knobset(knobset_idx);
		patch_mod_queue.put(ChangeKnobSet{knobset_idx});
		handle_changed_active_status();
	}

	void set_for_knob(lv_obj_t *cont, unsigned knob_i) {
		auto knob = get_knob(cont);
		lv_obj_set_style_arc_color(knob, Gui::knob_palette[knob_i % 6], LV_PART_INDICATOR);

		auto circle = get_circle(cont);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[knob_i % 6], LV_STATE_DEFAULT);

		auto circle_letter = get_circle_letter(cont);
		lv_label_set_text(circle_letter, PanelDef::get_map_param_name(knob_i).data());

		auto indicator = get_indicator(cont);
		lv_obj_set_style_bg_color(indicator, Gui::knob_palette[(knob_i + 1) % 6], LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(indicator, LV_OPA_100, LV_STATE_DEFAULT);
	}

	lv_obj_t *base = nullptr;
	MappedKnobSet *knobset = nullptr;
	PatchData *patch;
	ConfirmPopup kb_popup;
	bool is_actively_playing = false;

	bool is_patch_playing = false;
	unsigned last_known_active_knobset = 0;

	std::vector<lv_obj_t *> arcs;
	std::vector<lv_obj_t *> indicators;
	std::array<unsigned, PanelDef::NumKnobs> num_maps{};

	bool kb_visible = false;

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

	lv_obj_t *get_indicator(lv_obj_t *container) {
		return ui_comp_get_child(container, UI_COMP_KNOBCONTAINER_INDICATOR);
	}

	void update_enabled_status(lv_obj_t *container, unsigned knob_i, bool actively_playing) {
		if (actively_playing && num_maps[knob_i] > 0)
			enable(container, knob_i);
		else
			disable(container, knob_i);
	}

	void disable(lv_obj_t *container, unsigned knob_i) {
		auto knob = get_knob(container);
		auto circle = get_circle(container);
		auto label = get_label(container);
		if (!knob || !circle || !label)
			return;
		lv_obj_add_state(circle, LV_STATE_DISABLED);

		lv_obj_set_style_arc_color(knob, Gui::knob_disabled_palette[knob_i % 6], LV_PART_INDICATOR);
		lv_obj_set_style_opa(knob, LV_OPA_0, LV_PART_KNOB);

		auto indicator = get_indicator(container);
		lv_obj_add_flag(indicator, LV_OBJ_FLAG_HIDDEN);
	}

	void enable(lv_obj_t *container, unsigned knob_i) {
		auto knob = get_knob(container);
		auto circle = get_circle(container);
		auto label = get_label(container);
		if (!knob || !circle || !label)
			return;
		lv_obj_clear_state(circle, LV_STATE_DISABLED);

		lv_obj_set_style_arc_color(knob, Gui::knob_palette[knob_i % 6], LV_PART_INDICATOR);
		lv_obj_set_style_opa(knob, LV_OPA_100, LV_PART_KNOB);

		auto indicator = get_indicator(container);
		lv_obj_clear_flag(indicator, LV_OBJ_FLAG_HIDDEN);
	}
};

} // namespace MetaModule
