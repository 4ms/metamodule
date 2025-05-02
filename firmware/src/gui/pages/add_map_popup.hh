#pragma once
#include "console/pr_dbg.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/panel_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "metaparams.hh"
#include "midi/midi_message.hh"
#include "params_state.hh"
#include "patch_play/patch_mod_queue.hh"

namespace MetaModule
{

struct AddMapPopUp {

	AddMapPopUp(PatchModQueue &patch_mod_queue)
		: patch_mod_queue{patch_mod_queue}
		, popup_group(lv_group_create()) {

		midi_channel_dropdown = create_midi_map_dropdown(
			ui_AddMapPopUp,
			"All Chan.\nChan. 1\nChan. 2\nChan. 3\nChan. 4\nChan. 5\nChan. 6\nChan. 7\nChan. 8\nChan. 9\nChan. "
			"10\nChan. 11\nChan. 12\nChan. 13\nChan. 14\nChan. 15\nChan. 16");
		lv_obj_set_height(midi_channel_dropdown, 28);
		lv_obj_move_to_index(midi_channel_dropdown, -2);

		lv_obj_set_width(midi_channel_dropdown, LV_PCT(100));

		lv_group_add_obj(popup_group, midi_channel_dropdown);
		lv_group_add_obj(popup_group, ui_CancelAdd);
		lv_group_add_obj(popup_group, ui_OkAdd);

		lv_obj_add_event_cb(ui_CancelAdd, button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_OkAdd, button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(midi_channel_dropdown, drop_callback, LV_EVENT_VALUE_CHANGED, this);

		lv_hide(midi_channel_dropdown);
	}

	void prepare_focus(lv_group_t *group, lv_obj_t *base) {
		base_group = group;
		lv_obj_set_parent(ui_AddMapPopUp, base);
		midi_learn_channel = true;
		lv_dropdown_set_selected(midi_channel_dropdown, 0);
	}

	void show(uint32_t knobset_id, uint16_t param_id, uint16_t module_id, PatchData *patchdata) {
		selected_knob = std::nullopt;
		patch = patchdata;

		lv_show(ui_AddMapPopUp);
		lv_obj_scroll_to_y(ui_AddMapPopUp, 0, LV_ANIM_OFF);

		if (knobset_id == PatchData::MIDIKnobSet) {
			lv_label_set_text(ui_AddMappingTitle, "Add a map: Send MIDI Note or CC");
			lv_show(midi_channel_dropdown);
		} else {
			lv_label_set_text(ui_AddMappingTitle, "Add a map: Wiggle a knob");
			lv_hide(midi_channel_dropdown);
		}
		lv_label_set_text(ui_MapDetected, "");
		lv_label_set_text(ui_MapExistsLabel, "");

		param_idx = param_id;
		module_idx = module_id;

		set_id = knobset_id;
		visible = true;

		lv_group_activate(popup_group);
		lv_group_focus_obj(ui_OkAdd);
		lv_group_set_editing(popup_group, false);
		lv_group_set_wrap(popup_group, false);
	}

	void hide() {
		if (lv_dropdown_is_open(midi_channel_dropdown)) {
			lv_dropdown_close(midi_channel_dropdown);
			lv_group_set_editing(popup_group, false);
		} else {
			visible = false;
			lv_obj_clear_state(ui_CancelAdd, LV_STATE_PRESSED);
			lv_obj_clear_state(ui_OkAdd, LV_STATE_PRESSED);

			lv_hide(ui_AddMapPopUp);

			lv_group_activate(base_group);
			lv_group_set_editing(base_group, false);
		}
	}

	void update(ParamsMidiState &params, MetaParams &metaparams) {
		if (visible) {
			auto last_selected_knob = selected_knob;

			if (set_id == PatchData::MIDIKnobSet) {
				// Detect MIDI CC
				for (unsigned ccnum = 0; auto &cc : params.midi_ccs) {
					if (cc.changed) {
						cc.changed = 0;
						if (midi_learn_channel && cc.val < 16)
							lv_dropdown_set_selected(midi_channel_dropdown, cc.val + 1);

						selected_knob = MidiCC0 + ccnum;
						selected_midi_chan = lv_dropdown_get_selected(midi_channel_dropdown);

						set_midi_detected_name();
					}
					ccnum++;
				}

				// Detect MIDI Note On/Off
				auto &note = params.last_midi_note;
				if (note.changed) {
					note.changed = 0;
					if (midi_learn_channel && params.last_midi_note_channel < 16)
						lv_dropdown_set_selected(midi_channel_dropdown, params.last_midi_note_channel + 1);

					selected_knob = MidiGateNote0 + note.val;
					selected_midi_chan = lv_dropdown_get_selected(midi_channel_dropdown);

					set_midi_detected_name();
				}

			} else {
				for (unsigned i = 0; auto &knob : params.knobs) {
					if (knob.did_change()) {
						selected_knob = i;
						std::string_view name = PanelDef::get_map_param_name(i);

						lv_label_set_text_fmt(ui_MapDetected, "Knob: %.4s", name.data());
					}
					i++;
				}

				if (auto firstbit = std::countr_zero(metaparams.ext_buttons_high_events); firstbit < 32) {
					selected_knob = firstbit + FirstButton;
					lv_label_set_text_fmt(ui_MapDetected, "Button: %u", firstbit + 1);
				}
			}

			// Print "Already Mapped To..."
			if (patch && last_selected_knob != selected_knob && selected_knob.has_value()) {
				if (auto existingmap = patch->find_mapped_knob(set_id, selected_knob.value())) {
					auto full_name = get_full_element_name(
						existingmap->module_id, existingmap->param_id, ElementType::Param, *patch);

					std::string combined =
						(module_idx == existingmap->module_id) ?
							std::string(full_name.element_name) :
							std::string(full_name.module_name) + "\n" + std::string(full_name.element_name);

					lv_label_set_text_fmt(ui_MapExistsLabel, "Already Mapped To:\n%s", combined.c_str());
				} else
					lv_label_set_text(ui_MapExistsLabel, "");
			}
		}
	}

	void set_midi_detected_name() {
		if (!selected_knob)
			return;

		auto map = MappedKnob{.panel_knob_id = *selected_knob};

		if (map.is_midi_cc()) {
			auto name = get_panel_name(ParamElement{}, Midi::set_midi_channel(*selected_knob, selected_midi_chan));
			lv_label_set_text(ui_MapDetected, name.c_str());

		} else if (map.is_midi_notegate()) {
			auto name = get_panel_name(ParamElement{}, Midi::set_midi_channel(*selected_knob, selected_midi_chan));
			name = "Note (gate) " + name;
			lv_label_set_text(ui_MapDetected, name.c_str());
		}
	}

	static void button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<AddMapPopUp *>(event->user_data);

		if (event->target == ui_OkAdd) {

			if (page->selected_knob.has_value()) {
				auto map = MappedKnob{
					.panel_knob_id = page->selected_knob.value(),
					.module_id = page->module_idx,
					.param_id = page->param_idx,
					.min = 0.f,
					.max = 1.f,
				};
				if (map.is_panel_knob()) {
					// TODO: just have AddMapping type (not AddMidiMap) and use set_id to indicate MidiMap?
					page->patch_mod_queue.put(AddMapping{.map = map, .set_id = page->set_id});

				} else if (map.is_midi()) {
					map.midi_chan = page->selected_midi_chan;
					page->patch_mod_queue.put(AddMidiMap{.map = map});
				}
			}
			page->hide();

		} else if (event->target == ui_CancelAdd) {
			page->hide();
		}
	}

	static void drop_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<AddMapPopUp *>(event->user_data);

		page->midi_learn_channel = false;
		page->selected_midi_chan = lv_dropdown_get_selected(page->midi_channel_dropdown);
		page->set_midi_detected_name();
	}

	PatchModQueue &patch_mod_queue;
	lv_group_t *base_group = nullptr;
	lv_group_t *popup_group = nullptr;
	lv_obj_t *midi_channel_dropdown;
	bool midi_learn_channel = true;

	PatchData *patch = nullptr;

	uint16_t module_idx = 0;
	uint16_t param_idx = 0;
	uint32_t set_id = 0;
	bool visible = false;
	std::optional<uint16_t> selected_knob{};
	uint8_t selected_midi_chan = 0;
};

} // namespace MetaModule
