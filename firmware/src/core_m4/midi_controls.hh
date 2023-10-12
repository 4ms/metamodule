#pragma once
#include "midi_def.hh"
#include "midi_message.hh"
#include "params.hh"

namespace MetaModule
{

// void process_midi(MidiMessage msg, Params::Midi::Note *midi_note, Params::Midi::Event *gate_event) {
// 	// Monophonic MIDI CV/Gate
// 	if (msg.is_command<MidiCommand::NoteOff>() || (msg.is_command<MidiCommand::NoteOn>() && msg.velocity() == 0)) {
// 		midi_note->gate = false;
// 		midi_note->vel = 0;

// 		if (gate_event) {
// 			gate_event->notenum = msg.note();
// 			gate_event->gateamp = 0;
// 		}

// 	} else if (msg.is_command<MidiCommand::NoteOn>()) {

// 		midi_note->pitch = (msg.note() - 24) / 12.f; //60 = C3 = 3V. 72 = C4 = 4V etc...
// 		midi_note->vel = msg.velocity() / 12.7f;	 //0..127 => 0..10V
// 		midi_note->gate = true;

// 		if (gate_event) {
// 			gate_event->notenum = msg.note();
// 			gate_event->gateamp = msg.velocity() / 12;
// 		}

// 	} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
// 		if (((msg.note() - 24) / 12.f) == midi_note->pitch)
// 			midi_note->aft = msg.aftertouch();

// 	} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
// 		midi_note->aft = (float)msg.chan_pressure() / 12.7f;
// 	}
// }

} // namespace MetaModule
