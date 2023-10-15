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

Params::Midi::Note *find_polyphonic_slot(std::span<Params::Midi::Note> midi_notes, float pitch);

} // namespace Midi

void process_midi(MidiMessage msg,
				  std::span<Params::Midi::Note> all_midi_notes,
				  Params::Midi::Event &event,
				  uint32_t poly_chans) {

	auto midi_notes = all_midi_notes.subspan(0, poly_chans);

	// Only allow retrig to be true on a NoteOn event
	for (auto &midi_note : midi_notes)
		midi_note.retrig = false;

	// Monophonic MIDI CV/Gate
	if (msg.is_noteoff()) {
		auto pitch = Midi::note_to_volts(msg.note());

		for (auto &midi_note : midi_notes) {
			if (midi_note.pitch == pitch) {
				midi_note.gate = false;
				midi_note.vel = 0;
			}
		}

		event.type = Params::Midi::Event::Type::GateNote;
		event.chan = msg.note();
		event.val = 0;

	} else if (msg.is_command<MidiCommand::NoteOn>()) {
		auto pitch = Midi::note_to_volts(msg.note());

		auto empty_slot = Midi::find_polyphonic_slot(midi_notes, pitch);
		Params::Midi::Note &midi_note = empty_slot ? *empty_slot : midi_notes.back();
		midi_note.pitch = pitch;
		midi_note.vel = Midi::u7_to_volts<10>(msg.velocity());
		midi_note.gate = true;
		midi_note.retrig = true;

		event.type = Params::Midi::Event::Type::GateNote;
		event.chan = msg.note();
		event.val = Midi::u7_to_volts<10>(msg.velocity());

	} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
		for (auto &midi_note : midi_notes) {
			if (midi_note.pitch == Midi::note_to_volts(msg.note()))
				midi_note.aft = Midi::u7_to_volts<10>(msg.aftertouch());
		}

	} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
		for (auto &midi_note : midi_notes)
			midi_note.aft = Midi::u7_to_volts<10>(msg.chan_pressure());

	} else if (msg.is_command<MidiCommand::ControlChange>()) {
		event.type = Params::Midi::Event::Type::CC;
		event.chan = msg.ccnum();
		event.val = Midi::u7_to_volts<10>(msg.ccval());

	} else if (msg.is_command<MidiCommand::PitchBend>()) {
		event.type = Params::Midi::Event::Type::Bend;
		event.chan = 0;
		event.val = Midi::s14_to_semitones<2>(msg.bend());

	} else if (msg.is_timing_transport()) {
		event.type = Params::Midi::Event::Type::Time;
		event.chan = msg.status == MidiSystemRealTimeCommand::TimingClock ? TimingEvents::Clock :
					 msg.status == MidiSystemRealTimeCommand::Start		  ? TimingEvents::Start :
					 msg.status == MidiSystemRealTimeCommand::Stop		  ? TimingEvents::Stop :
					 msg.status == MidiSystemRealTimeCommand::Continue	  ? TimingEvents::Cont :
																			0xFF; //unsupported
	}
}

namespace Midi
{

Params::Midi::Note *find_polyphonic_slot(std::span<Params::Midi::Note> midi_notes, float pitch) {
	Params::Midi::Note *empty_slot = nullptr;

	for (auto &midi_note : midi_notes) {
		if (midi_note.gate == false)
			empty_slot = &midi_note;
	}
	return empty_slot;
}

} // namespace Midi

} // namespace MetaModule
