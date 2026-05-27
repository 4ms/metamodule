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
			"Load on MIDI PC",
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
				// if (e.path == current_path)
				// 	continue;
				bool chan_match = (channel == 0) || (e.channel == 0) || (e.channel == channel);
				if (chan_match && e.pc == pc) {
					auto [fname, vol] = split_volume(e.path);
					auto name = std::string(fname);
					if (auto pos = name.rfind('/'); pos != std::string::npos)
						name = name.substr(pos + 1);
					if (name.ends_with(".yml"))
						name.resize(name.size() - 4);
					options += " [" + name + "]";
					// break;
				}
			}
			if (pc < 127)
				options += '\n';
		}
		lv_dropdown_set_options(pc_dropdown, options.c_str());
	}

	void init_widgets() {
		lv_obj_set_width(panel, 300);
		lv_obj_set_width(message_label, LV_SIZE_CONTENT);

		auto pc_row = create_labeled_dropdown(panel);
		lv_obj_set_width(pc_row, 290);
		lv_obj_move_to_index(pc_row, 1);
		lv_label_set_text(lv_obj_get_child(pc_row, 0), "PC #:");
		pc_dropdown = lv_obj_get_child(pc_row, 1);
		lv_obj_set_width(pc_dropdown, 220);

		auto chan_row = create_labeled_dropdown(panel);
		lv_obj_set_width(chan_row, 290);
		lv_obj_move_to_index(chan_row, 2);
		lv_label_set_text(lv_obj_get_child(chan_row, 0), "MIDI Channel:");
		chan_dropdown = lv_obj_get_child(chan_row, 1);

		lv_dropdown_set_options(chan_dropdown,
								"Any\nChan. 1\nChan. 2\nChan. 3\nChan. 4\nChan. 5\nChan. 6\nChan. 7\nChan. 8\nChan. "
								"9\nChan. 10\nChan. 11\nChan. 12\nChan. 13\nChan. 14\nChan. 15\nChan. 16");
		lv_obj_set_width(chan_dropdown, 100);
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
