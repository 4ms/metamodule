#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch-serial/patch/midi_def.hh"
#include <functional>
#include <optional>
#include <string_view>

namespace MetaModule
{

struct MidiMapPopup {

	MidiMapPopup()
		: group(lv_group_create()) {

		sources = {{
			{ui_MidiMapNoteCheck, {ui_MidiMapNoteDrop, ui_MidiMapNotePolyDrop}},
			{ui_MidiMapCCCheck, {ui_MidiMapCCDrop}},
			{ui_MidiMapPitchWheelCheck, {}},
			{ui_MidiMapGateCheck, {ui_MidiMapGateDrop}},
			{ui_MidiMapClockCheck, {ui_MidiMapClockDrop}},
			{ui_MidiMapTransportCheck, {ui_MidiMapTransportDrop}},
		}};

		// Group:
		for (auto &source : sources) {
			lv_group_add_obj(group, source.checkbox);
			for (auto drop : source.dropdowns) {
				lv_group_add_obj(group, drop);
				lv_obj_set_user_data(drop, source.checkbox);
			}
		}

		lv_group_add_obj(group, ui_MidiMapCancelButton);
		lv_group_add_obj(group, ui_MidiMapOKButton);

		for (auto &source : sources) {
			lv_obj_add_event_cb(source.checkbox, check_callback, LV_EVENT_VALUE_CHANGED, this);
			for (auto dropdown : source.dropdowns) {
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
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
		lv_hide(ui_MIDIMapPanel);
	}

	struct MidiSourceGUI {
		lv_obj_t *checkbox{};
		std::vector<lv_obj_t *> dropdowns;
	};

	void set_header_text(std::string_view title) {
		lv_label_set_text(ui_MidiMapJackTitle, title.data());
	}

	void show(auto cb) {
		callback = std::move(cb);

		//TODO: limit polyphony menu to patch's max poly number

		lv_indev_set_group(lv_indev_get_next(nullptr), group);

		// initial state: Note checked
		lv_group_focus_obj(ui_MidiMapNoteCheck);
		lv_obj_add_state(ui_MidiMapNoteCheck, LV_STATE_CHECKED);
		check_only(ui_MidiMapNoteCheck);

		// Make visible
		lv_obj_set_parent(ui_MIDIMapPanel, base);

		lv_show(ui_MIDIMapPanel);
		visible = true;
		done = false;
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
			std::optional<unsigned> midi_map_number;

			if (event->target == ui_MidiMapCancelButton)
				midi_map_number = std::nullopt;

			else if (event->target == ui_MidiMapOKButton)
				midi_map_number = page->calc_midi_signal_number();

			page->callback(midi_map_number);
		}

		printf("clicked\n");
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
		auto source_check = static_cast<lv_obj_t *>(lv_obj_get_user_data(event->target));
		if (!source_check)
			return;

		page->check_only(source_check);
	}

	void check_only(lv_obj_t *source_check) {
		for (auto &source : sources) {
			if (source.checkbox == source_check)
				lv_obj_add_state(source.checkbox, LV_STATE_CHECKED);
			else
				lv_obj_clear_state(source.checkbox, LV_STATE_CHECKED);
		}
	}

	std::optional<unsigned> calc_midi_signal_number() {
		if (lv_is_checked(ui_MidiMapNoteCheck)) {
			auto polynum = lv_dropdown_get_selected(ui_MidiMapNotePolyDrop);
			polynum = std::min<unsigned>(polynum, 7);

			auto eventnum = lv_dropdown_get_selected(ui_MidiMapNoteDrop);
			unsigned midibase = eventnum == 0 ? MidiMonoNoteJack :
								eventnum == 1 ? MidiMonoGateJack :
								eventnum == 2 ? MidiMonoVelJack :
								eventnum == 3 ? MidiMonoAftertouchJack :
								eventnum == 4 ? MidiMonoRetrigJack :
												0;
			return midibase ? midibase + polynum : std::optional<unsigned>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapCCCheck)) {
			auto ccnum = lv_dropdown_get_selected(ui_MidiMapCCDrop);
			unsigned midibase = MidiCC0;
			return ccnum <= 127 ? midibase + ccnum : std::optional<unsigned>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapPitchWheelCheck)) {
			return static_cast<unsigned>(MidiPitchWheelJack);

		} else if (lv_is_checked(ui_MidiMapGateCheck)) {
			auto notenum = lv_dropdown_get_selected(ui_MidiMapGateDrop);
			unsigned midibase = MidiGateNote0;
			return notenum <= 127 ? midibase + notenum : std::optional<unsigned>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapClockCheck)) {
			auto clock = lv_dropdown_get_selected(ui_MidiMapClockDrop);
			unsigned midinum = clock == 0 ? MidiClockJack :// 24PPQN
							   clock == 1 ? MidiClockDiv2Jack :// 12PPQN (/2)
							   clock == 2 ? MidiClockDiv3Jack :// 32nd note (/3)
							   clock == 3 ? MidiClockDiv6Jack :// 16th note (/6)
							   clock == 4 ? MidiClockDiv12Jack :// 8th note (/12)
							   clock == 5 ? MidiClockDiv24Jack :// Quarter note (/24)
							   clock == 6 ? MidiClockDiv48Jack :// Half note (/48)
							   clock == 7 ? MidiClockDiv96Jack :// Whole note (/96)
											0;

			return midinum ? midinum : std::optional<unsigned>{std::nullopt};

		} else if (lv_is_checked(ui_MidiMapTransportCheck)) {
			auto event = lv_dropdown_get_selected(ui_MidiMapTransportDrop);
			unsigned midinum = event == 0 ? MidiStartJack :
							   event == 1 ? MidiStopJack :
							   event == 2 ? MidiContinueJack :
											0;

			return midinum ? midinum : std::optional<unsigned>{std::nullopt};

		} else {
			return std::optional<unsigned>{std::nullopt};
		}
	}

protected:
	lv_obj_t *base{};
	lv_group_t *group;
	lv_group_t *orig_group{};

	bool visible = false;
	bool done = true;

	std::function<void(std::optional<unsigned>)> callback;

	std::array<MidiSourceGUI, 6> sources;
};

} // namespace MetaModule
