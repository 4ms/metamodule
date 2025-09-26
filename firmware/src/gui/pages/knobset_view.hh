#pragma once
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/keyboard_entry.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/knobset_view_buttonexp.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "src/core/lv_event.h"

namespace MetaModule
{
struct KnobSetViewPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobSetViewPage(PatchContext info)
		: PageBase{info, PageId::KnobSetView}
		, base{ui_KnobSetViewPage}
		, patch{patches.get_view_patch()}
		, button_exp{info.metaparams} {
		init_bg(base);
		lv_group_set_editing(group, false);

		lv_hide(ui_PreviousKnobSet);

		jacks_button = create_button(ui_KnobSetPageHeader, "Jacks");
		lv_obj_set_height(jacks_button, 18);
		lv_obj_add_event_cb(jacks_button, goto_jackmap_cb, LV_EVENT_CLICKED, this);
		lv_obj_move_to_index(jacks_button, 1);

		// Add MIDI Maps button next to Jacks
		midi_map_button = create_button(ui_KnobSetPageHeader, "MIDI");
		lv_obj_set_height(midi_map_button, 18);
		lv_obj_add_event_cb(midi_map_button, goto_midimap_cb, LV_EVENT_CLICKED, this);
		// Place immediately after the Jacks button in header
		lv_obj_move_to_index(midi_map_button, 2);

		lv_obj_add_event_cb(ui_KnobSetNameText, rename_knobset_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_NextKnobSet, next_knobset_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ActivateKnobSet, activate_knobset_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_PreviousKnobSet, scroll_to_knobs, LV_EVENT_FOCUSED, this);

		lv_hide(ui_KnobSetDescript);
	}

	void prepare_focus() override {
		lv_obj_set_y(ui_Keyboard, 40);
		keyboard_entry.prepare_focus(ui_KnobSetViewPage, group);

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
		lv_group_add_obj(group, jacks_button);
		lv_group_add_obj(group, midi_map_button);
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

			lv_obj_t *cont{};

			if (map.is_panel_knob()) {
				cont = create_knob_item(idx, map);
			} else if (map.is_button()) {
				cont = button_exp.create_button_item(idx, map, patch);
			}

			if (!cont)
				continue;

			lv_obj_remove_event_cb(cont, mapping_cb);
			lv_obj_add_event_cb(cont, mapping_cb, LV_EVENT_CLICKED, this);

			// Use user_data to connect the mapping to the lvgl object (via index in the knobset->set)
			lv_obj_set_user_data(cont, reinterpret_cast<void *>(idx + 1));

			// Focus on the previously focussed object (if any), or the Next>> button if it's visible
			if (!args.mappedknob_id) {
				if (idx == 0) { //only need to do this once
					focus = (lv_obj_has_flag(ui_NextKnobSet, LV_OBJ_FLAG_HIDDEN)) ? cont : ui_NextKnobSet;
				}
			} else {
				if (idx == args.mappedknob_id)
					focus = cont;
			}
		}

		// Show midi button only if there are midi maps
		lv_hide(midi_map_button);
		if (patch->midi_maps.set.size() > 0)
			lv_show(midi_map_button);
		else {
			for (auto const &map : patch->mapped_ins) {
				if (Midi::is_midi_panel_id(map.panel_jack_id)) {
					lv_show(midi_map_button);
					break;
				}
			}
		}

		// Add all items to the group
		for (auto [idx, pane] : enumerate(panes)) {
			if (num_maps[idx])
				lv_foreach_child(pane, [this](lv_obj_t *cont, int idx) { lv_group_add_obj(group, cont); });
		}
		button_exp.add_to_group(group);

		// Hide button expander columns for expanders that aren't physically connected,
		// unless there are mappings
		button_exp.hide_unused_columns();

		lv_group_focus_obj(focus);

		lv_group_set_editing(group, false);

		display_active_status();
	}

	lv_obj_t *create_knob_item(unsigned idx, MappedKnob const &map) {
		lv_obj_t *cont;

		if (num_maps[map.panel_knob_id] == 0) {
			cont = get_container(map.panel_knob_id);
		} else {
			cont = (map.panel_knob_id < 6) ? ui_KnobContainerBig_create(panes[map.panel_knob_id]) :
											 ui_KnobContainer_create(panes[map.panel_knob_id]);
		}
		num_maps[map.panel_knob_id]++;

		std::string s;
		param_item_name(s, map, patch);
		lv_label_set_text(get_label(cont), s.c_str());

		lv_obj_add_event_cb(cont, scroll_to_knobs, LV_EVENT_FOCUSED, this);

		set_knob_arc<min_arc, max_arc>(map, get_knob(cont), 0);
		set_for_knob(cont, map.panel_knob_id);
		arcs[idx] = get_knob(cont);
		indicators[idx] = get_indicator(cont);

		return cont;
	}

	void update() override {
		// if (!kb_visible)
		// 	lv_group_set_editing(group, false);
		// save_knobset_name(false);

		if (gui_state.back_button.is_just_released()) {
			if (keyboard_entry.is_visible()) {
				keyboard_entry.back();
			} else if (page_list.request_last_page()) {
				blur();
			}
		}

		handle_changed_active_status();

		if (knobset) {
			for (auto idx = 0u; auto const &map : knobset->set) {
				auto value = patch_playloader.param_value(map.module_id, map.param_id);

				auto arc_val = map.unmap_val(value) * 120.f;
				if (arcs[idx])
					lv_arc_set_value(arcs[idx], arc_val);

				if (map.is_panel_knob()) {
					auto phys_val = params.knobs[map.panel_knob_id].val;
					auto mapped_phys_val = map.get_mapped_val(phys_val);

					auto is_tracking = patch_playloader.is_param_tracking(map.module_id, map.param_id);
					if (indicators[idx])
						update_indicator(indicators[idx], is_tracking, mapped_phys_val);
					if (arcs[idx])
						update_knob(arcs[idx], is_tracking, arc_val);

				} else if (map.is_button()) {
					button_exp.update_button(idx, value);
				}

				idx++;
			}
		}

		poll_patch_file_changed();

		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;
			if (keyboard_entry.is_visible())
				keyboard_entry.hide();
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

		button_exp.blur();
	}

private:
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

			page_list.update_state(PageId::KnobSetView, args);
			page_list.request_new_page_no_history(PageId::KnobSetView,
												  {.patch_loc_hash = args.patch_loc_hash,
												   .mappedknob_id = args.mappedknob_id,
												   .view_knobset_id = page_list.get_active_knobset()});

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
		keyboard_entry.show_keyboard(ui_KnobSetNameText, [this](std::string_view text) {
			save_knobset_name();
			patches.mark_view_patch_modified();
		});
	}

	void save_knobset_name() {
		knobset->name = lv_textarea_get_text(ui_KnobSetNameText);
		patches.mark_view_patch_modified();
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

	static void rename_knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobSetViewPage *>(event->user_data);

		if (lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN))
			page->show_keyboard();
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

		unsigned map_idx = reinterpret_cast<uintptr_t>(obj->user_data) - 1;
		if (map_idx >= page->patch->knob_sets[view_set_idx].set.size())
			return;

		page->args.mappedknob_id = map_idx;
		page->load_page(PageId::KnobMap, page->args);
	}

	static void scroll_to_knobs(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_KnobSetContainer, 0, LV_ANIM_ON);
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

	static void goto_midimap_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobSetViewPage *>(event->user_data);
		page->page_list.request_new_page_no_history(PageId::MidiMapView, page->args);
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
		lv_obj_set_style_arc_color(knob, Gui::get_knob_color(knob_i), LV_PART_INDICATOR);

		auto circle = get_circle(cont);
		lv_obj_set_style_bg_color(circle, Gui::get_knob_color(knob_i), LV_STATE_DEFAULT);

		auto circle_letter = get_circle_letter(cont);
		lv_label_set_text(circle_letter, PanelDef::get_map_param_name(knob_i).data());

		auto indicator = get_indicator(cont);
		lv_obj_set_style_bg_color(indicator, Gui::get_knob_indicator_color(knob_i), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(indicator, LV_OPA_100, LV_STATE_DEFAULT);
	}

	lv_obj_t *base = nullptr;
	lv_obj_t *jacks_button = nullptr;
	lv_obj_t *midi_map_button = nullptr;
	MappedKnobSet *knobset = nullptr;
	PatchData *patch;
	ButtonExpanderMapsView button_exp;
	bool is_actively_playing = false;

	bool is_patch_playing = false;
	unsigned last_known_active_knobset = 0;

	std::vector<lv_obj_t *> arcs;
	std::vector<lv_obj_t *> indicators;
	std::array<unsigned, PanelDef::NumKnobs> num_maps{};

	KeyboardEntry keyboard_entry;

	// The panes are the areas where mapping containers go
	// If one knob maps to multiple things, then there will be multiple containers in that knob's pane
	std::array<lv_obj_t *, 12> panes{
		ui_KnobPanelA,
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
		ui_KnobPanelZ,
	};

	// These are the first container in each pane. We always keep one here
	// so that a disabled knob shows up as grey-ed out
	std::array<lv_obj_t *, 12> containers{
		ui_KnobContainerA,
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
		ui_KnobContainerZ,
	};

	//////////// Helpers

	lv_obj_t *get_container(unsigned panel_knob_id) {
		return containers[panel_knob_id];
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

	lv_obj_t *get_button_label(lv_obj_t *container) {
		return lv_obj_get_child(container, 1);
	}

	lv_obj_t *get_button_circle(lv_obj_t *container) {
		return lv_obj_get_child(container, 0);
	}

	lv_obj_t *get_button_circle_number(lv_obj_t *container) {
		return lv_obj_get_child(get_button_circle(container), 0);
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

		lv_obj_set_style_arc_color(knob, Gui::get_knob_color(knob_i), LV_PART_INDICATOR);
		lv_obj_set_style_opa(knob, LV_OPA_100, LV_PART_KNOB);

		auto indicator = get_indicator(container);
		lv_obj_clear_flag(indicator, LV_OBJ_FLAG_HIDDEN);
	}
};

} // namespace MetaModule
