#pragma once
#include "midi_def.hh"
#include "midi_message.hh"
#include "params.hh"

namespace MetaModule
{

namespace Midi
{

// Converts MIDI 7-bit to volts
template<unsigned MaxVolts>
constexpr float u7_to_volts(uint8_t val) {
	return (float)val / (127.f / (float)MaxVolts);
}

template<unsigned NumSemitones>
constexpr float s14_to_semitones(int16_t val) {
	return (float)val / (8192.f / ((float)NumSemitones / 12.f));
}
static_assert(s14_to_semitones<2>(-8192) == -0.16666667f);
static_assert(s14_to_semitones<2>(8192) == 0.16666667f);

constexpr float note_to_volts(uint8_t note) {
	return (note - 24) / 12.f;
}
static_assert(note_to_volts(60) == 3);
static_assert(note_to_volts(72) == 4);

} // namespace Midi

void process_midi(MidiMessage msg, Params::Midi::Note &midi_note, Params::Midi::Event &event) {

	// Monophonic MIDI CV/Gate
	if (msg.is_noteoff()) {
		midi_note.gate = false;
		midi_note.vel = 0;

		event.type = Params::Midi::Event::Type::GateNote;
		event.chan = msg.note();
		event.val = 0;

	} else if (msg.is_command<MidiCommand::NoteOn>()) {

		midi_note.pitch = Midi::note_to_volts(msg.note());
		midi_note.vel = Midi::u7_to_volts<10>(msg.velocity());
		midi_note.gate = true;

		event.type = Params::Midi::Event::Type::GateNote;
		event.chan = msg.note();
		event.val = Midi::u7_to_volts<10>(msg.velocity());

	} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
		if (((msg.note() - 24) / 12.f) == midi_note.pitch)
			midi_note.aft = Midi::u7_to_volts<10>(msg.aftertouch());

	} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
		midi_note.aft = Midi::u7_to_volts<10>(msg.chan_pressure());

	} else if (msg.is_command<MidiCommand::ControlChange>()) {
		event.type = Params::Midi::Event::Type::CC;
		event.chan = msg.ccnum();
		event.val = Midi::u7_to_volts<10>(msg.ccval());

	} else if (msg.is_command<MidiCommand::PitchBend>()) {
		event.type = Params::Midi::Event::Type::Bend;
		event.chan = 0;
		event.val = Midi::s14_to_semitones<2>(msg.bend());

	} else if (msg.is_clock()) {
		event.type = Params::Midi::Event::Type::Clock;
		event.chan = 0;
	}
}

} // namespace MetaModule
