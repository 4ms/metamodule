#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "params_state.hh"
#include "patch-serial/patch/midi_def.hh"
#include <functional>
#include <optional>
#include <string_view>

namespace MetaModule
{

struct MidiMapPopup {
	lv_obj_t *midi_channel_dropdown;

	MidiMapPopup(ParamsMidiState &params)
		: group(lv_group_create())
		, params{params} {

		auto label = create_midi_map_label(ui_MidiMapCont, "Channel: ");
		lv_obj_add_flag(label, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		midi_channel_dropdown =
			create_midi_map_dropdown(ui_MidiMapCont, "All\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16");
		lv_obj_set_width(midi_channel_dropdown, 90);
		lv_obj_move_to_index(label, -3);
		lv_obj_move_to_index(midi_channel_dropdown, -2);

		sources = {{
			{.checkbox = ui_MidiMapNoteCheck, .dropdowns = {ui_MidiMapNoteDrop, ui_MidiMapNotePolyDrop}},
			{.checkbox = ui_MidiMapCCCheck, .dropdowns = {ui_MidiMapCCDrop}},
			{.checkbox = ui_MidiMapPitchWheelCheck, .dropdowns = {}},
			{.checkbox = ui_MidiMapGateCheck, .dropdowns = {ui_MidiMapGateDrop}},
			{.checkbox = ui_MidiMapClockCheck, .dropdowns = {ui_MidiMapClockDrop}},
			{.checkbox = ui_MidiMapTransportCheck, .dropdowns = {ui_MidiMapTransportDrop}},
			{.checkbox = nullptr, .dropdowns = {midi_channel_dropdown}},
		}};

		// Group:
		for (auto &source : sources) {
			if (source.checkbox)
				lv_group_add_obj(group, source.checkbox);
			for (auto drop : source.dropdowns) {
				lv_group_add_obj(group, drop);
				lv_obj_set_user_data(drop, source.checkbox);
			}
		}

		lv_group_add_obj(group, ui_MidiMapCancelButton);
		lv_group_add_obj(group, ui_MidiMapOKButton);

		for (auto &source : sources) {
			if (source.checkbox)
				lv_obj_add_event_cb(source.checkbox, check_callback, LV_EVENT_VALUE_CHANGED, this);

			for (auto dropdown : source.dropdowns) {
				lv_obj_remove_style(dropdown, &Gui::dropdown_style, LV_PART_MAIN);
				lv_obj_remove_style(dropdown, &Gui::dropdown_style_selected, LV_PART_SELECTED);
				lv_obj_remove_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY);
				lv_obj_remove_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY | LV_STATE_PRESSED);
				lv_obj_remove_style(dropdown, &Gui::focus_style, LV_STATE_EDITED);

				lv_obj_add_style(dropdown, &Gui::dropdown_style, LV_PART_MAIN);
				lv_obj_set_style_pad_ver(dropdown, 8, LV_PART_MAIN);
				lv_obj_add_style(dropdown, &Gui::dropdown_style_selected, LV_PART_SELECTED);
				lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY);
				lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY | LV_STATE_PRESSED);
				lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_EDITED);

				lv_obj_add_event_cb(dropdown, drop_callback, LV_EVENT_VALUE_CHANGED, this);
				lv_obj_add_event_cb(dropdown, drop_callback, LV_EVENT_READY, this);
			}
		}

		lv_obj_add_event_cb(ui_MidiMapCancelButton, button_callback, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MidiMapOKButton, button_callback, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_MidiMapNoteCheck, scroll_to_top, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_MidiMapNotePolyDrop, scroll_to_top, LV_EVENT_FOCUSED, this);

		lv_dropdown_set_selected(ui_MidiMapCCDrop, 20);
		lv_dropdown_set_selected(ui_MidiMapGateDrop, 60);

		lv_label_set_text(ui_MidiMapNoteLabel, "Note:");
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
		lv_hide(ui_MIDIMapPanel);
	}

	void set_header_text(std::string_view title) {
		lv_label_set_text(ui_MidiMapJackTitle, title.data());
	}

	void show(auto cb, std::optional<uint32_t> panel_jack_id) {
		callback = std::move(cb);

		//TODO: limit polyphony menu to patch's max poly number

		lv_indev_set_group(lv_indev_get_next(nullptr), group);

		if (panel_jack_id)
			select_options(*panel_jack_id);
		else {
			// initial state: Note checked
			lv_group_focus_obj(ui_MidiMapNoteCheck);
			lv_obj_add_state(ui_MidiMapNoteCheck, LV_STATE_CHECKED);
			check_only(ui_MidiMapNoteCheck);
		}

		// Make visible
		lv_obj_set_parent(ui_MIDIMapPanel, base);

		lv_show(ui_MIDIMapPanel);
		visible = true;
		done = false;
		midi_learn_channel = true;
	}

	void update() {
		if (midi_learn) {
			for (auto ccnum = 0u; auto &cc : params.midi_ccs) {
				if (cc.changed) {
					cc.changed = 0;
					if (ccnum < lv_dropdown_get_option_cnt(ui_MidiMapCCDrop))
						lv_dropdown_set_selected(ui_MidiMapCCDrop, ccnum);
					if (midi_learn_channel && cc.val < 16)
						lv_dropdown_set_selected(midi_channel_dropdown, cc.val + 1);
				}
				ccnum++;
			}

			auto &note = params.last_midi_note;
			if (note.changed) {
				note.changed = 0;
				if (note.val < lv_dropdown_get_option_cnt(ui_MidiMapGateDrop))
					lv_dropdown_set_selected(ui_MidiMapGateDrop, note.val);
				if (midi_learn_channel && params.last_midi_note_channel < 16)
					lv_dropdown_set_selected(midi_channel_dropdown, params.last_midi_note_channel + 1);
			}
		}
	}

	void hide() {
		lv_hide(ui_MIDIMapPanel);
		if (orig_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), orig_group);
		visible = false;
	}

	void back() {
		for (auto &source : sources) {
			for (auto drop : source.dropdowns) {
				if (lv_obj_has_state(drop, LV_STATE_EDITED)) {
					lv_dropdown_close(drop);
					lv_obj_clear_state(drop, LV_STATE_EDITED);
					lv_group_set_editing(group, false);
					done = false;
					return;
				}
			}
		}
		done = true;
	}

	bool should_close() {
		return done;
	}

	bool is_visible() {
		return visible;
	}

	static void button_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<MidiMapPopup *>(event->user_data);
		if (!page)
			return;

		if (page->callback) {
			std::optional<MidiMappings> midi_map_number;

			if (event->target == ui_MidiMapCancelButton)
				midi_map_number = std::nullopt;

			else if (event->target == ui_MidiMapOKButton)
				midi_map_number = page->calc_midi_signal_number();

			page->callback(midi_map_number);
		}

		page->hide();
	}

	static void scroll_to_top(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_MIDIMapPanel, 0, LV_ANIM_ON);
	}

	static void check_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<MidiMapPopup *>(event->user_data);
		if (!page)
			return;

		page->check_only(event->target);
	}

	static void drop_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<MidiMapPopup *>(event->user_data);
		if (!page)
			return;

		// Channel dropdown: if user sets it manually then don't overwrite with midi learn
		if (event->target == page->midi_channel_dropdown)
			page->midi_learn_channel = false;

		auto source_check = static_cast<lv_obj_t *>(lv_obj_get_user_data(event->target));
		if (!source_check)
			return;

		page->check_only(source_check);
	}

	void check_only(lv_obj_t *source_check) {
		for (auto &source : sources) {
			if (source.checkbox) {
				if (source.checkbox == source_check)
					lv_obj_add_state(source.checkbox, LV_STATE_CHECKED);
				else
					lv_obj_clear_state(source.checkbox, LV_STATE_CHECKED);
			}
		}
	}

	std::optional<MidiMappings> calc_midi_signal_number() {
		auto midi_chan = lv_dropdown_get_selected(midi_channel_dropdown);

		auto set_channels = [=](MidiMappings m, unsigned offset) -> std::optional<MidiMappings> {
			return Midi::set_midi_channel(m + offset, midi_chan);
		};

		if (lv_is_checked(ui_MidiMapNoteCheck)) {
			auto eventnum = lv_dropdown_get_selected(ui_MidiMapNoteDrop);
			auto polynum = lv_dropdown_get_selected(ui_MidiMapNotePolyDrop);

			if (polynum == 0) {
				return eventnum == 0 ? MidiNotePolyJack :
					   eventnum == 1 ? MidiGatePolyJack :
					   eventnum == 2 ? MidiVelPolyJack :
					   eventnum == 3 ? MidiAftPolyJack :
					   eventnum == 4 ? MidiRetrigPolyJack :
									   std::optional<MidiMappings>{std::nullopt};

			} else {
				polynum = std::min<unsigned>(polynum - 1, 7);

				return eventnum == 0 ? set_channels(MidiMonoNoteJack, polynum) :
					   eventnum == 1 ? set_channels(MidiMonoGateJack, polynum) :
					   eventnum == 2 ? set_channels(MidiMonoVelJack, polynum) :
					   eventnum == 3 ? set_channels(MidiMonoAftertouchJack, polynum) :
					   eventnum == 4 ? set_channels(MidiMonoRetrigJack, polynum) :
									   std::optional<MidiMappings>{std::nullopt};
			}

		} else if (lv_is_checked(ui_MidiMapCCCheck)) {
			auto ccnum = lv_dropdown_get_selected(ui_MidiMapCCDrop);
			return ccnum <= 127 ? set_channels(MidiCC0, ccnum) : std::optional<MidiMappings>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapPitchWheelCheck)) {
			return set_channels(MidiPitchWheelJack, 0);

		} else if (lv_is_checked(ui_MidiMapGateCheck)) {
			auto notenum = lv_dropdown_get_selected(ui_MidiMapGateDrop);
			return notenum <= 127 ? set_channels(MidiGateNote0, notenum) : std::optional<MidiMappings>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapClockCheck)) {
			auto clock = lv_dropdown_get_selected(ui_MidiMapClockDrop);
			return clock == 0 ? MidiClockJack :// 24PPQN
							   clock == 1 ? MidiClockDiv2Jack :// 12PPQN (/2)
							   clock == 2 ? MidiClockDiv3Jack :// 32nd note (/3)
							   clock == 3 ? MidiClockDiv6Jack :// 16th note (/6)
							   clock == 4 ? MidiClockDiv12Jack :// 8th note (/12)
							   clock == 5 ? MidiClockDiv24Jack :// Quarter note (/24)
							   clock == 6 ? MidiClockDiv48Jack :// Half note (/48)
							   clock == 7 ? MidiClockDiv96Jack :// Whole note (/96)
										std::optional<MidiMappings>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapTransportCheck)) {
			auto event = lv_dropdown_get_selected(ui_MidiMapTransportDrop);
			return event == 0 ? MidiStartJack :
				   event == 1 ? MidiStopJack :
				   event == 2 ? MidiContinueJack :
								std::optional<MidiMappings>{std::nullopt};

		} else {
			return std::optional<MidiMappings>{std::nullopt};
		}
	}

	void select_options(uint32_t panel_jack_id) {
		auto midi_chan = Midi::midi_channel(panel_jack_id);
		lv_dropdown_set_selected(midi_channel_dropdown, midi_chan);

		auto polychan = Midi::polychan(panel_jack_id); //1-8 for poly note chan, or nullopt for poly cables
		auto midi_jack_id = Midi::strip_midi_channel(panel_jack_id);

		if (polychan.has_value()) {
			check_only(ui_MidiMapNoteCheck);
			lv_group_focus_obj(ui_MidiMapNoteCheck);

			lv_dropdown_set_selected(ui_MidiMapNotePolyDrop, polychan.value());
			auto event_sel = Midi::midi_note_pitch(midi_jack_id)  ? 0 :
							 Midi::midi_note_gate(midi_jack_id)	  ? 1 :
							 Midi::midi_note_vel(midi_jack_id)	  ? 2 :
							 Midi::midi_note_aft(midi_jack_id)	  ? 3 :
							 Midi::midi_note_retrig(midi_jack_id) ? 4 :
																	0;
			lv_dropdown_set_selected(ui_MidiMapNoteDrop, event_sel);
		}

		else if (Midi::is_midi_poly_cable(midi_jack_id))
		{
			check_only(ui_MidiMapNoteCheck);
			lv_group_focus_obj(ui_MidiMapNoteCheck);

			lv_dropdown_set_selected(ui_MidiMapNotePolyDrop, 0); // "Poly 1-4"
			auto event_sel = midi_jack_id == MidiNotePolyJack	  ? 0 :
							 midi_jack_id == MidiGatePolyJack	  ? 1 :
							 Midi::midi_note_vel(midi_jack_id)	  ? 2 :
							 Midi::midi_note_aft(midi_jack_id)	  ? 3 :
							 Midi::midi_note_retrig(midi_jack_id) ? 4 :
																	0;
			lv_dropdown_set_selected(ui_MidiMapNoteDrop, event_sel);
		}

		else if (midi_jack_id == MidiPitchWheelJack)
		{
			check_only(ui_MidiMapPitchWheelCheck);
			lv_group_focus_obj(ui_MidiMapPitchWheelCheck);
		}

		else if (auto ccnum = Midi::midi_cc(midi_jack_id))
		{
			check_only(ui_MidiMapCCCheck);
			lv_group_focus_obj(ui_MidiMapCCCheck);

			lv_dropdown_set_selected(ui_MidiMapCCDrop, ccnum.value());
		}

		else if (auto notenum = Midi::midi_gate(midi_jack_id))
		{
			check_only(ui_MidiMapGateCheck);
			lv_group_focus_obj(ui_MidiMapGateCheck);

			lv_dropdown_set_selected(ui_MidiMapGateDrop, notenum.value());
		}

		else if (Midi::midi_clk(midi_jack_id))
		{
			check_only(ui_MidiMapClockCheck);
			lv_group_focus_obj(ui_MidiMapClockCheck);

			lv_dropdown_set_selected(ui_MidiMapClockDrop, 0);
		}

		else if (auto clk = Midi::midi_divclk(midi_jack_id))
		{
			check_only(ui_MidiMapClockCheck);
			lv_group_focus_obj(ui_MidiMapClockCheck);

			lv_dropdown_set_selected(ui_MidiMapClockDrop,
									 midi_jack_id == MidiClockDiv1Jack	? 0 :
									 midi_jack_id == MidiClockDiv2Jack	? 1 :
									 midi_jack_id == MidiClockDiv3Jack	? 2 :
									 midi_jack_id == MidiClockDiv6Jack	? 3 :
									 midi_jack_id == MidiClockDiv12Jack ? 4 :
									 midi_jack_id == MidiClockDiv24Jack ? 5 :
									 midi_jack_id == MidiClockDiv48Jack ? 6 :
									 midi_jack_id == MidiClockDiv96Jack ? 7 :
																		  0);
		}

		else if (Midi::midi_transport(midi_jack_id))
		{
			check_only(ui_MidiMapTransportCheck);
			lv_group_focus_obj(ui_MidiMapTransportCheck);

			lv_dropdown_set_selected(ui_MidiMapTransportDrop,
									 midi_jack_id == MidiStartJack	  ? 0 :
									 midi_jack_id == MidiStopJack	  ? 1 :
									 midi_jack_id == MidiContinueJack ? 2 :
																		0);
		}
	}

protected:
	lv_obj_t *base{};
	lv_group_t *group;
	lv_group_t *orig_group{};
	ParamsMidiState &params;
	uint16_t panel_jack_id = MidiMonoNoteJack;

	bool visible = false;
	bool done = true;
	bool midi_learn = true;
	bool midi_learn_channel = true;

	std::function<void(std::optional<MidiMappings>)> callback;

	struct MidiSourceGUI {
		lv_obj_t *checkbox{};
		std::vector<lv_obj_t *> dropdowns;
	};

	std::array<MidiSourceGUI, 7> sources;
};

} // namespace MetaModule
