#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch-serial/patch/midi_def.hh"
#include <functional>
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
			}
		}

		lv_obj_add_event_cb(ui_MidiMapCancelButton, button_callback, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MidiMapOKButton, button_callback, LV_EVENT_CLICKED, this);
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

	void show(auto cb) {
		callback = std::move(cb);

		//TODO: limit polyphony menu to patch's max poly number

		lv_indev_set_group(lv_indev_get_next(nullptr), group);

		// initial state: Note checked
		lv_group_focus_obj(ui_MidiMapNoteCheck);
		lv_obj_add_state(ui_MidiMapNoteCheck, LV_STATE_CHECKED);

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
			if (event->target == ui_MidiMapCancelButton)
				page->callback(0);

			else if (event->target == ui_MidiMapOKButton)
				page->callback(1);
		}

		printf("clicked\n");
		page->hide();
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

protected:
	lv_obj_t *base{};
	lv_group_t *group;
	lv_group_t *orig_group{};

	bool visible = false;
	bool done = true;

	std::function<void(unsigned)> callback;

	std::array<MidiSourceGUI, 6> sources;
};

} // namespace MetaModule
