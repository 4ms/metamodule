#pragma once
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "patch-serial/patch/midi_def.hh"
#include <optional>

namespace MetaModule
{

struct MidiMapViewPage : PageBase {

	MidiMapViewPage(PatchContext info)
		: PageBase{info, PageId::MidiMapView}
		, base{ui_MidiMapViewPage}
		, patch{patches.get_view_patch()}
		, group{lv_group_create()} {

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_label_set_text(ui_MidiMapInputsTitle, "MIDI Jacks");
		lv_label_set_text(ui_MidiMapOutputsTitle, "MIDI Params");
	}

	void prepare_focus() override {
		redraw();
		lv_group_activate(group);
		lv_obj_scroll_to_y(ui_MidiMapLeftColumn, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_y(ui_MidiMapRightColumn, 0, LV_ANIM_OFF);
	}

	void redraw() {
		patch = patches.get_view_patch();

		// Clear existing items
		lv_obj_clean(ui_MidiMapLeftColumn);
		lv_obj_clean(ui_MidiMapRightColumn);

		left_items.clear();
		right_items.clear();

		lv_group_remove_all_objs(group);

		// MIDI jack maps (inputs): any mapped_in whose panel_jack_id is a MIDI mapping
		for (auto [i, map] : enumerate(patch->mapped_ins)) {
			if (!Midi::is_midi_panel_id(map.panel_jack_id))
				continue;

			const char *label_text = "";
			std::string label_storage;
			if (map.alias_name.size()) {
				label_text = map.alias_name.c_str();
			} else if (!map.ins.empty()) {
				auto name = get_full_element_name(map.ins[0].module_id, map.ins[0].jack_id, ElementType::Input, *patch);
				label_storage = std::string(name.module_name) + " " + std::string(name.element_name);
				label_text = label_storage.c_str();
			}

			auto cont = create_jack_map_item(ui_MidiMapLeftColumn, JackMapType::MIDI, map.panel_jack_id, label_text);
			lv_obj_set_user_data(cont, (void *)((uintptr_t)i));
			lv_obj_add_event_cb(cont, on_midi_jack_click, LV_EVENT_CLICKED, this);
			lv_group_add_obj(group, cont);
			left_items.push_back(cont);
		}

		// MIDI param maps (right): entries from pd.midi_maps.set
		for (auto [i, mk] : enumerate(patch->midi_maps.set)) {
			auto fullname = get_full_element_name(mk.module_id, mk.param_id, ElementType::Param, *patch);
			std::string label = std::string(fullname.module_name) + " " + std::string(fullname.element_name);
			auto cont = create_jack_map_item(ui_MidiMapRightColumn, JackMapType::MIDI, mk.panel_knob_id, label.c_str());
			lv_obj_set_user_data(cont, (void *)((uintptr_t)i));
			lv_obj_add_event_cb(cont, on_param_map_click, LV_EVENT_CLICKED, this);
			lv_group_add_obj(group, cont);
			right_items.push_back(cont);
		}
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {
			if (page_list.request_last_page()) {
				blur();
			}
		}

		poll_patch_file_changed();
		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;
			redraw();
		}
	}

private:
	static void on_midi_jack_click(lv_event_t *event) {
		if (const auto page = static_cast<MidiMapViewPage *>(event->user_data); page) {
			const auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
			if (idx < page->patch->mapped_ins.size() && !page->patch->mapped_ins[idx].ins.empty()) {
				const auto &jack = page->patch->mapped_ins[idx].ins[0];
				page->args.module_id = jack.module_id;
				page->args.element_indices = ElementCount::mark_unused_indices(
					{.input_idx = static_cast<uint8_t>(jack.jack_id)}, {.num_inputs = 1});
				page->args.detail_mode = true;
				page->page_list.request_new_page(PageId::ModuleView, page->args);
			}
		}
	}

	static void on_param_map_click(lv_event_t *event) {
		if (const auto page = static_cast<MidiMapViewPage *>(event->user_data); page) {
			const auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
			if (idx < page->patch->midi_maps.set.size()) {
				page->args.mappedknob_id = static_cast<uint32_t>(idx);
				page->args.view_knobset_id = PatchData::MIDIKnobSet;
				page->page_list.request_new_page(PageId::KnobMap, page->args);
			}
		}
	}

private:
	lv_obj_t *base = nullptr;
	PatchData *patch;
	lv_group_t *group;
	std::vector<lv_obj_t *> left_items;
	std::vector<lv_obj_t *> right_items;
};

} // namespace MetaModule
