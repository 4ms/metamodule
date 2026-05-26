#include "prefs_section_midi.hh"
#include "ui_local.h"
#include <string>

namespace MetaModule
{

void PrefsSectionMidi::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "MIDI");

	auto midi_cont = create_prefs_labeled_check(parent, "Enable Feedback:");
	feedback_check = lv_obj_get_child(midi_cont, 1);

	create_prefs_note(midi_cont, "Sends MIDI to controller\nwhen MIDI-mapped params\nchange");

	// MIDI PC Patch Load
	create_prefs_section_title(parent, "MIDI PC PATCH LOAD");

	auto pc_cont = create_prefs_labeled_check(parent, "Enable:");
	pc_patch_load_check = lv_obj_get_child(pc_cont, 1);

	show_pc_table_button = create_button(pc_cont, "Show List");
	lv_obj_add_event_cb(show_pc_table_button, show_pc_table, LV_EVENT_CLICKED, this);

	create_prefs_note(pc_cont, "Load patches via MIDI\nProgram Change events");

	// Knob Set Control
	create_prefs_section_title(parent, "MIDI KNOB SET SELECT");

	auto knobset_cont = create_prefs_labeled_check(parent, "Enable:");
	knobset_control_check = lv_obj_get_child(knobset_cont, 1);

	create_prefs_note(knobset_cont, "MIDI CC values 0-7       \nselect Knob Set       ");

	// MIDI CC number (0-127)
	std::string cc_opts;
	for (int i = 0; i <= 127; i++) {
		cc_opts += std::to_string(i) + "\n";
	}
	cc_opts.pop_back();
	auto cc_cont = create_prefs_labeled_dropdown(parent, "MIDI CC:", cc_opts);
	knobset_cc_dropdown = lv_obj_get_child(cc_cont, 1);
	lv_obj_set_width(knobset_cc_dropdown, 60);

	// MIDI Channel (1-16)
	std::string ch_opts;
	for (int i = 1; i <= 16; i++) {
		ch_opts += std::to_string(i) + "\n";
	}
	ch_opts.pop_back();
	auto ch_cont = create_prefs_labeled_dropdown(parent, "MIDI Channel:", ch_opts);
	knobset_channel_dropdown = lv_obj_get_child(ch_cont, 1);
	lv_obj_set_width(knobset_channel_dropdown, 50);
}

void PrefsSectionMidi::init_popup(lv_obj_t *parent, lv_group_t *group, MidiPCPatchLoadSettings &settings) {
	this->settings = &settings;

	pc_roller.init(lv_layer_top(), group);
	lv_obj_set_width(pc_roller.popup, 312);
	lv_obj_set_height(pc_roller.popup, 230);
	lv_obj_set_width(pc_roller.roller, 290);
	lv_obj_set_style_text_font(pc_roller.roller, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
	lv_obj_set_style_text_font(pc_roller.roller, &ui_font_MuseoSansRounded50014, LV_STATE_EDITED);
	lv_obj_set_style_text_font(pc_roller.roller, &ui_font_MuseoSansRounded50014, LV_PART_ITEMS);
}

bool PrefsSectionMidi::close_popup() {
	if (pc_roller.is_visible()) {
		pc_roller.hide();
		return true;
	}
	return false;
}

void PrefsSectionMidi::show_pc_table(lv_event_t *event) {
	if (!event || !event->user_data)
		return;
	auto page = static_cast<PrefsSectionMidi *>(event->user_data);

	std::string text = "";
	for (auto const &entry : page->settings->entries) {

		char c[8];
		snprintf(c, 8, "PC%03d", entry.pc);
		text += c;

		if (entry.channel > 0)
			text += " Ch. " + std::to_string(entry.channel);
		else
			text += " Any Ch.";

		text += " " + entry.path;
		text += "\n";
	}
	if (text.size())
		text.pop_back();

	page->pc_roller.show([](unsigned) {}, "", text.c_str(), 0);
}

} // namespace MetaModule
