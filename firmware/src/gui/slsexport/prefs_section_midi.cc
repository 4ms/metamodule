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

	// Knob Set Control
	auto knobset_cont = create_prefs_labeled_check(parent, "Knob Set Control:");
	knobset_control_check = lv_obj_get_child(knobset_cont, 1);

	create_prefs_note(knobset_cont, "Change knobsets via MIDI CC");

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

} // namespace MetaModule
