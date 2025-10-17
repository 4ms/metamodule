#include "prefs_section_midi.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionMidi::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "MIDI");

	auto midi_cont = create_prefs_labeled_check(parent, "Enable Feedback:");
	feedback_check = lv_obj_get_child(midi_cont, 1);

	create_prefs_note(midi_cont, "Sends MIDI to controller\nwhen MIDI-mapped params\nchange");
}

} // namespace MetaModule
