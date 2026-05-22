#pragma once
#include "fs/helpers.hh"
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "user_settings/midi_pc_settings.hh"
#include <algorithm>
#include <string>

namespace MetaModule
{

struct MidiPCAssignDialog {
	lv_obj_t *panel;
	lv_obj_t *chan_dropdown;
	lv_obj_t *pc_dropdown;
	lv_obj_t *cancel_button;
	lv_obj_t *ok_button;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	MidiPCPatchLoadSettings *midi_settings = nullptr;
	GuiState *gui_state = nullptr;
	std::string current_path;

	MidiPCAssignDialog()
		: group(lv_group_create()) {
		init_widgets();
	}

	void init(lv_obj_t *base, lv_group_t *parent_group) {
		lv_obj_set_parent(panel, base);
		base_group = parent_group;
		lv_hide(panel);
	}

	void show(std::string_view path, MidiPCPatchLoadSettings &settings, GuiState &gs) {
		midi_settings = &settings;
		gui_state = &gs;
		current_path = path;

		uint32_t init_chan = 0;
		uint32_t init_pc = 0;
		bool found = false;
		for (auto const &e : settings.entries) {
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

		// Remove callback before setting initial values to avoid spurious rebuilds
		lv_obj_remove_event_cb(chan_dropdown, chan_changed_cb);
		lv_dropdown_set_selected(chan_dropdown, init_chan);
		rebuild_pc_options(init_chan);
		lv_dropdown_set_selected(pc_dropdown, init_pc);
		lv_obj_add_event_cb(chan_dropdown, chan_changed_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, chan_dropdown);
		lv_group_add_obj(group, pc_dropdown);
		lv_group_add_obj(group, cancel_button);
		lv_group_add_obj(group, ok_button);
		lv_group_set_wrap(group, false);

		lv_show(panel);
		lv_group_activate(group);
		lv_group_focus_obj(ok_button);
		visible = true;
	}

	void hide() {
		lv_obj_remove_event_cb(chan_dropdown, chan_changed_cb);
		lv_hide(panel);
		lv_group_activate(base_group);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

private:
	uint32_t find_free_pc(uint32_t channel) {
		for (uint32_t pc = 0; pc <= 127; pc++) {
			bool taken = false;
			for (auto const &e : midi_settings->entries) {
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
			for (auto const &e : midi_settings->entries) {
				if (e.path == current_path)
					continue;
				bool chan_match = (channel == 0) || (e.channel == 0) || (e.channel == channel);
				if (chan_match && e.pc == pc) {
					auto [fname, vol] = split_volume(e.path);
					auto name = std::string(fname);
					if (auto pos = name.rfind('/'); pos != std::string::npos)
						name = name.substr(pos + 1);
					if (name.ends_with(".yml"))
						name.resize(name.size() - 4);
					options += " [" + name + "]";
					break;
				}
			}
			if (pc < 127)
				options += '\n';
		}
		lv_dropdown_set_options(pc_dropdown, options.c_str());
	}

	static void chan_changed_cb(lv_event_t *event) {
		auto self = static_cast<MidiPCAssignDialog *>(event->user_data);
		uint32_t chan = lv_dropdown_get_selected(self->chan_dropdown);
		uint32_t cur_pc = lv_dropdown_get_selected(self->pc_dropdown);
		self->rebuild_pc_options(chan);
		lv_dropdown_set_selected(self->pc_dropdown, cur_pc);
	}

	static void button_cb(lv_event_t *event) {
		auto self = static_cast<MidiPCAssignDialog *>(event->user_data);

		if (event->target == self->ok_button && self->midi_settings) {
			uint32_t chan = lv_dropdown_get_selected(self->chan_dropdown);
			uint32_t pc = lv_dropdown_get_selected(self->pc_dropdown);

			auto &entries = self->midi_settings->entries;
			entries.erase(
				std::remove_if(entries.begin(), entries.end(),
					[self](auto const &e) { return e.path == self->current_path; }),
				entries.end());
			entries.push_back({self->current_path, chan, pc});

			if (self->gui_state)
				self->gui_state->do_write_settings = true;
		}

		self->hide();
	}

	lv_obj_t *make_dialog_button(lv_obj_t *parent, const char *text, uint32_t bg_color) {
		auto btn = lv_btn_create(parent);
		lv_obj_set_width(btn, LV_SIZE_CONTENT);
		lv_obj_set_height(btn, LV_SIZE_CONTENT);
		lv_obj_set_align(btn, LV_ALIGN_CENTER);
		lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(btn,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_radius(btn, 20, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(btn, lv_color_hex(bg_color), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(btn, 255, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(btn, 10, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(btn, 10, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(btn, 6, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(btn, 6, LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(btn, 0, LV_STATE_PRESSED);
		lv_obj_set_style_outline_color(btn, lv_color_hex(0xFFFFFF), LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(btn, 255, LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_width(btn, 2, LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_pad(btn, 3, LV_STATE_FOCUS_KEY);

		auto label = lv_label_create(btn);
		lv_obj_set_align(label, LV_ALIGN_CENTER);
		lv_label_set_text(label, text);
		lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded50016, LV_STATE_DEFAULT);

		return btn;
	}

	void init_widgets() {
		panel = lv_obj_create(lv_layer_top());
		lv_obj_set_width(panel, 200);
		lv_obj_set_height(panel, LV_SIZE_CONTENT);
		lv_obj_set_align(panel, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_add_flag(panel, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(panel,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_radius(panel, 4, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(panel, lv_color_hex(0x333333), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(panel, 255, LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(panel, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(panel, lv_color_hex(0x777777), LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(panel, 255, LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(panel, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_outline_pad(panel, 1, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(panel, 6, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(panel, 8, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(panel, 8, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(panel, 8, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(panel, 8, LV_STATE_DEFAULT);

		auto title = lv_label_create(panel);
		lv_obj_set_width(title, LV_SIZE_CONTENT);
		lv_obj_set_height(title, LV_SIZE_CONTENT);
		lv_obj_set_align(title, LV_ALIGN_CENTER);
		lv_label_set_text(title, "Load on MIDI PC");
		lv_obj_set_style_text_color(title, lv_color_hex(0xEEEEEE), LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(title, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

		auto chan_row = create_labeled_dropdown(panel);
		lv_label_set_text(lv_obj_get_child(chan_row, 0), "Channel:");
		chan_dropdown = lv_obj_get_child(chan_row, 1);
		lv_dropdown_set_options(chan_dropdown,
								"Any\nChan. 1\nChan. 2\nChan. 3\nChan. 4\nChan. 5\nChan. 6\nChan. 7\nChan. 8\nChan. "
								"9\nChan. 10\nChan. 11\nChan. 12\nChan. 13\nChan. 14\nChan. 15\nChan. 16");
		lv_obj_set_width(chan_dropdown, 80);

		auto pc_row = create_labeled_dropdown(panel);
		lv_label_set_text(lv_obj_get_child(pc_row, 0), "PC #:");
		pc_dropdown = lv_obj_get_child(pc_row, 1);
		lv_obj_set_width(pc_dropdown, 110);

		auto button_row = lv_obj_create(panel);
		lv_obj_remove_style_all(button_row);
		lv_obj_set_width(button_row, LV_SIZE_CONTENT);
		lv_obj_set_height(button_row, LV_SIZE_CONTENT);
		lv_obj_set_align(button_row, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(button_row, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(button_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_clear_flag(button_row,
						  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_pad_column(button_row, 12, LV_STATE_DEFAULT);

		cancel_button = make_dialog_button(button_row, "Cancel", 0x777777);
		ok_button = make_dialog_button(button_row, "OK", 0x2095F6);

		lv_obj_add_event_cb(cancel_button, button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ok_button, button_cb, LV_EVENT_CLICKED, this);

		lv_hide(panel);
	}
};

} // namespace MetaModule
