#pragma once
#include "midi_def.hh"
#include "midi_message.hh"
#include "params.hh"
#include <algorithm>

namespace MetaModule::Midi
{

struct MessageParser {
	std::array<Params::Midi::Note, MaxMidiPolyphony> all_midi_notes;
	std::span<Params::Midi::Note> midi_notes{all_midi_notes};

	void set_poly_num(uint32_t poly_chans) {
		poly_chans = std::clamp<uint32_t>(poly_chans, 1U, all_midi_notes.size());

		if (poly_chans != midi_notes.size())
			midi_notes = std::span<Params::Midi::Note>{all_midi_notes.begin(), poly_chans - 1};
	}

	Params::Midi::Event parse(MidiMessage msg) {
		Params::Midi::Event event;

		// Clear events from previous
		event.type = Params::Midi::Event::Type::None;

		// Monophonic MIDI CV/Gate
		if (msg.is_noteoff()) {

			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note() && midi_note.gate) {
					midi_note.gate = false;

					event.type = Params::Midi::Event::Type::NoteOff;
					event.poly_chan = i;
					break;
				}
				i++;
			}

		} else if (msg.is_command<MidiCommand::NoteOn>()) {

			auto poly_chan = find_polyphonic_slot(midi_notes, msg.note());
			Params::Midi::Note &midi_note = midi_notes[poly_chan];
			midi_note.note = msg.note();
			midi_note.gate = true;

			event.type = Params::Midi::Event::Type::NoteOn;
			event.poly_chan = poly_chan;
			event.note = msg.note();
			event.val = Midi::u7_to_volts<10>(msg.velocity());
			printf_("On[%d] %d v%d\n", event.poly_chan, event.note, msg.velocity());

		} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note()) {
					event.type = Params::Midi::Event::Type::Aft;
					event.poly_chan = i;
					event.val = Midi::u7_to_volts<10>(msg.aftertouch());
					break;
				}
				i++;
			}

		} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
			event.type = Params::Midi::Event::Type::ChanPress;
			event.val = Midi::u7_to_volts<10>(msg.chan_pressure());

		} else if (msg.is_command<MidiCommand::ControlChange>()) {
			event.type = Params::Midi::Event::Type::CC;
			event.note = msg.ccnum();
			event.val = Midi::u7_to_volts<10>(msg.ccval());

		} else if (msg.is_command<MidiCommand::PitchBend>()) {
			event.type = Params::Midi::Event::Type::Bend;
			event.val = Midi::s14_to_semitones<2>(msg.bend());

		} else if (msg.is_timing_transport()) {
			event.type = Params::Midi::Event::Type::Time;
			event.note = msg.status == MidiSystemRealTimeCommand::TimingClock ? TimingEvents::Clock :
						 msg.status == MidiSystemRealTimeCommand::Start		  ? TimingEvents::Start :
						 msg.status == MidiSystemRealTimeCommand::Stop		  ? TimingEvents::Stop :
						 msg.status == MidiSystemRealTimeCommand::Continue	  ? TimingEvents::Cont :
																				0xFF; //unsupported
		}

		return event;
	}

	size_t find_polyphonic_slot(std::span<Params::Midi::Note> midi_notes, uint8_t note) {
		size_t empty_slot = midi_notes.size() - 1;

		for (unsigned i = 0; auto &midi_note : midi_notes) {
			if (midi_note.gate == false)
				empty_slot = i;
			i++;
		}
		return empty_slot;
	}
};

} // namespace MetaModule::Midi
