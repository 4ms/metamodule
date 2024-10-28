#pragma once
#include "midi/midi_message.hh"
#include "params.hh"
#include "patch/midi_def.hh"
#include <algorithm>
#include <optional>

namespace MetaModule::Midi
{

struct MessageParser {
	std::array<Midi::Note, MaxMidiPolyphony> all_midi_notes;
	std::span<Midi::Note> midi_notes{all_midi_notes};

	void set_poly_num(uint32_t poly_chans) {
		poly_chans = std::clamp<uint32_t>(poly_chans, 1U, all_midi_notes.size());

		if (poly_chans != midi_notes.size()) {
			midi_notes = std::span{all_midi_notes.begin(), poly_chans};
		}
	}

	Midi::Event parse(MidiMessage msg) {
		Midi::Event event{};

		// Monophonic MIDI CV/Gate
		if (msg.is_noteoff()) {

			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note() && midi_note.gate) {
					midi_note.gate = false;

					event.type = Midi::Event::Type::NoteOff;
					event.note = msg.note();
					event.poly_chan = i;
					break;
				}
				i++;
			}

		} else if (msg.is_command<MidiCommand::NoteOn>()) {

			auto poly_chan = find_polyphonic_slot_rotate(midi_notes, msg.note());
			Midi::Note &midi_note = midi_notes[poly_chan];
			midi_note.note = msg.note();
			midi_note.gate = true;

			event.type = Midi::Event::Type::NoteOn;
			event.poly_chan = poly_chan;
			event.note = msg.note();
			event.val = msg.velocity(); //Midi::u7_to_volts<10>(msg.velocity());

		} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note()) {
					event.type = Midi::Event::Type::Aft;
					event.poly_chan = i;
					event.val = msg.aftertouch(); //Midi::u7_to_volts<10>(msg.aftertouch());
					break;
				}
				i++;
			}

		} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
			event.type = Midi::Event::Type::ChanPress;
			event.val = msg.chan_pressure(); //Midi::u7_to_volts<10>(msg.chan_pressure());

		} else if (msg.is_command<MidiCommand::ControlChange>()) {
			event.type = Midi::Event::Type::CC;
			event.note = msg.ccnum();
			event.val = msg.ccval(); //Midi::u7_to_volts<10>(msg.ccval());

		} else if (msg.is_command<MidiCommand::PitchBend>()) {
			event.type = Midi::Event::Type::Bend;
			event.val = msg.bend(); //Midi::s14_to_semitones<2>(msg.bend());

		} else if (msg.is_timing_transport()) {
			event.type = Midi::Event::Type::Time;
			event.note = msg.status == MidiSystemRealTimeCommand::TimingClock ? TimingEvents::Clock :
						 msg.status == MidiSystemRealTimeCommand::Start		  ? TimingEvents::Start :
						 msg.status == MidiSystemRealTimeCommand::Stop		  ? TimingEvents::Stop :
						 msg.status == MidiSystemRealTimeCommand::Continue	  ? TimingEvents::Cont :
																				0xFF; //unsupported
		}

		return event;
	}

	size_t last_poly_chan = MaxMidiPolyphony;

	size_t find_polyphonic_slot_rotate(std::span<Midi::Note> midi_notes, uint8_t note) {
		auto next = last_poly_chan + 1;
		if (next >= midi_notes.size())
			next = 0;

		while (midi_notes[next].gate == true) {
			if (next == last_poly_chan)
				break;

			next++;
			if (next >= midi_notes.size())
				next = 0;
		}
		last_poly_chan = next;
		return next;
	}

	size_t find_polyphonic_slot_first_available(std::span<Midi::Note> midi_notes, uint8_t note) {
		size_t empty_slot = midi_notes.size() - 1;

		for (unsigned i = 0; auto &midi_note : midi_notes) {
			if (midi_note.gate == false)
				empty_slot = i;
			i++;
		}
		return empty_slot;
	}

	bool noteoff_seq_in_progress = false;
	uint8_t noteoff_seq_cur_step = 0;

	void start_all_notes_off_sequence() {
		noteoff_seq_in_progress = true;
		noteoff_seq_cur_step = 0;
	}

	// Sends NoteOff to all poly channels, one by one, each time it's called
	// Returns Event Type None when done, and returns nullopt if not running
	std::optional<Midi::Event> step_all_notes_off_sequence() {
		if (!noteoff_seq_in_progress)
			return std::nullopt;

		if (noteoff_seq_cur_step < MaxMidiPolyphony) {
			auto event = Midi::Event{.type = Midi::Event::Type::NoteOff, .poly_chan = noteoff_seq_cur_step};
			midi_notes[noteoff_seq_cur_step].gate = false;

			noteoff_seq_cur_step++;
			return event;
		}

		noteoff_seq_in_progress = false;
		noteoff_seq_cur_step = 0;
		return Midi::Event{.type = Midi::Event::Type::None};
	}
};

} // namespace MetaModule::Midi
