#pragma once
#include "fs/helpers.hh"
#include "gui/gui_state.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/ui_local.h"
#include "user_settings/midi_pc_settings.hh"
#include <algorithm>
#include <string>

namespace MetaModule
{

struct MidiPCAssignDialog : ConfirmPopup {
	lv_obj_t *chan_dropdown = nullptr;
	lv_obj_t *pc_dropdown = nullptr;

	MidiPCPatchLoadSettings &midi_settings;
	GuiState &gui_state;
	std::string current_path;

	MidiPCAssignDialog(MidiPCPatchLoadSettings &settings, GuiState &gs)
		: ConfirmPopup{}
		, midi_settings{settings}
		, gui_state{gs} {
		init_widgets();
	}

	void init(lv_obj_t *base, lv_group_t *parent_group) {
		ConfirmPopup::init(base, parent_group);
	}

	void show(std::string_view path) {
		current_path = path;

		uint32_t init_chan = 0;
		uint32_t init_pc = 0;
		bool found = false;
		for (auto const &e : midi_settings.entries) {
			if (e.path == current_path) {
				init_chan = e.channel;
				init_pc = e.pc;
				found = true;
				break;
			}
		}
		if (!found) {
			init_chan = 0;
			init_pc = find_free_pc(0);
		}

		lv_obj_remove_event_cb(chan_dropdown, chan_changed_cb);
		lv_dropdown_set_selected(chan_dropdown, init_chan);
		rebuild_pc_options(init_chan);
		lv_dropdown_set_selected(pc_dropdown, init_pc);
		lv_obj_add_event_cb(chan_dropdown, chan_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_hide(message_label);

		ConfirmPopup::show(
			[this](unsigned) {
				uint32_t chan = lv_dropdown_get_selected(chan_dropdown);
				uint32_t pc = lv_dropdown_get_selected(pc_dropdown);

				auto &entries = midi_settings.entries;
				std::erase_if(entries, [=, this](auto const &e) {
					bool path_match = e.path == current_path;
					bool pc_match = e.pc == pc && (chan == 0 || e.channel == 0 || (chan == e.channel));
					return path_match || pc_match;
				});
				entries.push_back({current_path, chan, pc});

				gui_state.do_write_settings = true;
			},
			"",
			"OK");

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, pc_dropdown);
		lv_group_add_obj(group, chan_dropdown);
		lv_group_add_obj(group, cancel_button);
		lv_group_add_obj(group, confirm_button);
		lv_group_set_wrap(group, false);
		lv_group_focus_obj(confirm_button);
	}

	void hide() {
		if (lv_dropdown_is_open(chan_dropdown)) {
			lv_dropdown_close(chan_dropdown);
			lv_obj_clear_state(chan_dropdown, LV_STATE_EDITED);
			lv_group_set_editing(group, false);
		} else if (lv_dropdown_is_open(pc_dropdown)) {
			lv_dropdown_close(pc_dropdown);
			lv_obj_clear_state(pc_dropdown, LV_STATE_EDITED);
			lv_group_set_editing(group, false);
		} else {
			ConfirmPopup::hide();
		}
	}

	bool is_visible() {
		return visible;
	}

private:
	uint32_t find_free_pc(uint32_t channel) {
		for (uint32_t pc = 0; pc <= 127; pc++) {
			bool taken = false;
			for (auto const &e : midi_settings.entries) {
				if (e.path == current_path)
					continue;
				bool chan_match = (channel == 0) || (e.channel == 0) || (e.channel == channel);
				if (chan_match && e.pc == pc) {
					taken = true;
					break;
				}
			}
			if (!taken)
				return pc;
		}
		return 0;
	}

	void rebuild_pc_options(uint32_t channel) {
		std::string options;
		for (uint32_t pc = 0; pc <= 127; pc++) {
			options += std::to_string(pc);
			for (auto const &e : midi_settings.entries) {
				bool chan_match = (channel == 0) || (e.channel == 0) || (e.channel == channel);
				if (chan_match && e.pc == pc) {
					auto [fname, vol] = split_volume(e.path);
					auto name = std::string(fname);
					if (auto pos = name.rfind('/'); pos != std::string::npos)
						name = name.substr(pos + 1);
					if (name.ends_with(".yml"))
						name.resize(name.size() - 4);
					options += " " + name + "";
				}
			}
			if (pc < 127)
				options += '\n';
		}
		lv_dropdown_set_options(pc_dropdown, options.c_str());
	}

	void init_widgets() {
		lv_obj_set_width(panel, 300);
		lv_obj_set_height(panel, 185);
		lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_row(panel, 12, LV_PART_MAIN);

		auto title = create_title_level_2(panel, "Load patch on MIDI PC");
		lv_obj_move_to_index(title, 0);

		auto pc_label = create_midi_map_label(panel, "PC #:");
		lv_obj_add_flag(pc_label, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

		pc_dropdown = create_midi_map_dropdown(panel, "");
		lv_obj_set_width(pc_dropdown, 220);
		lv_obj_set_height(pc_dropdown, LV_SIZE_CONTENT);

		auto chan_label = create_midi_map_label(panel, "MIDI Channel:");
		lv_obj_add_flag(chan_label, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

		chan_dropdown = create_midi_map_dropdown(panel, "");
		lv_obj_set_width(chan_dropdown, 100);
		lv_obj_set_height(chan_dropdown, LV_SIZE_CONTENT);
		lv_dropdown_set_options(chan_dropdown,
								"Any\nChan. 1\nChan. 2\nChan. 3\nChan. 4\nChan. 5\nChan. 6\nChan. 7\nChan. 8\nChan. "
								"9\nChan. 10\nChan. 11\nChan. 12\nChan. 13\nChan. 14\nChan. 15\nChan. 16");

		auto button_panel = lv_obj_get_parent(cancel_button);
		lv_obj_add_flag(button_panel, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_obj_move_to_index(button_panel, -1);
		lv_obj_set_style_pad_top(button_panel, 12, LV_PART_MAIN);
	}

	static void chan_changed_cb(lv_event_t *event) {
		printf("chan changed\n");
		auto self = static_cast<MidiPCAssignDialog *>(event->user_data);
		uint32_t chan = lv_dropdown_get_selected(self->chan_dropdown);
		uint32_t cur_pc = lv_dropdown_get_selected(self->pc_dropdown);
		self->rebuild_pc_options(chan);
		lv_dropdown_set_selected(self->pc_dropdown, cur_pc);
	}
};

} // namespace MetaModule
