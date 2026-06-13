#pragma once
#include "midi/midi_message.hh"
#include "params/midi_params.hh"
#include "patch/midi_def.hh"
#include <algorithm>
#include <optional>

namespace MetaModule::Midi
{

struct MessageParser {
	std::array<Midi::Note, MaxMidiPolyphony> all_midi_notes;
	std::span<Midi::Note> midi_notes{all_midi_notes};

	// 14-bit CC mode: when enabled, CC 0-31 are MSBs and CC 32-63 are the matching
	// LSBs (CC n+32). The last MSB received for each CC is stored so it can be
	// combined with a later LSB. Storage is not per-channel (see parse()).
	bool midi_14bit_mode = false;
	std::array<uint8_t, 32> cc_msb{};

	void set_poly_num(uint32_t poly_chans) {
		poly_chans = std::clamp<uint32_t>(poly_chans, 1U, all_midi_notes.size());

		if (poly_chans != midi_notes.size()) {
			midi_notes = std::span{all_midi_notes.begin(), poly_chans};
		}
	}

	void set_14bit_mode(bool enabled) {
		midi_14bit_mode = enabled;
	}

	Midi::Event parse(MidiMessage msg) {

		Midi::Event event{};

		// Monophonic MIDI CV/Gate
		if (msg.is_noteoff()) {

			// Find the note in held midi_notes, and get the poly chan if found.
			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note() && midi_note.gate) {
					midi_note.gate = false;
					event.poly_chan = i;
					break;
				}
				i++;
			}
			event.type = Midi::Event::Type::NoteOff;
			event.note = msg.note();
			event.midi_chan = msg.status.channel;

		} else if (msg.is_command<MidiCommand::NoteOn>()) {

			auto poly_chan = find_polyphonic_slot_rotate(midi_notes, msg.note());
			Midi::Note &midi_note = midi_notes[poly_chan];
			midi_note.note = msg.note();
			midi_note.gate = true;

			event.type = Midi::Event::Type::NoteOn;
			event.poly_chan = poly_chan;
			event.note = msg.note();
			event.val = msg.velocity();
			event.midi_chan = msg.status.channel;

		} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
			for (unsigned i = 0; auto &midi_note : midi_notes) {
				if (midi_note.note == msg.note()) {
					event.type = Midi::Event::Type::Aft;
					event.poly_chan = i;
					event.val = msg.aftertouch();
					event.midi_chan = msg.status.channel;
					break;
				}
				i++;
			}

		} else if (msg.is_command<MidiCommand::ControlChange>()) {
			// The A7 core always treats CC values as 14-bit, so we left-shift 7-bit
			// values by 7 (CC 127 => 16256) and only build true 14-bit values when
			// 14-bit mode is on. This keeps the A7 conversion identical in either mode.
			event.type = Midi::Event::Type::CC;
			event.midi_chan = msg.status.channel;
			auto ccnum = msg.ccnum();
			auto ccval = msg.ccval();

			if (midi_14bit_mode && ccnum < 32) {
				// MSB: store it (resetting the implicit LSB to 0) and emit a coarse value.
				// Maps on the matching LSB (CC ccnum+32) are ignored, so only emit on ccnum.
				cc_msb[ccnum] = ccval;
				event.note = ccnum;
				event.val = static_cast<int16_t>(ccval << 7);
			} else if (midi_14bit_mode && ccnum < 64) {
				// LSB: combine with the last MSB and emit on the MSB's CC number (ccnum-32).
				auto msb_ccnum = ccnum - 32;
				event.note = msb_ccnum;
				event.val = static_cast<int16_t>((cc_msb[msb_ccnum] << 7) | ccval);
			} else {
				// 7-bit CC (or CC 64-127 while in 14-bit mode): shift up to 14-bit range.
				event.note = ccnum;
				event.val = static_cast<int16_t>(ccval << 7);
			}

		} else if (msg.is_command<MidiCommand::ProgramChange>()) {
			event.type = Midi::Event::Type::PC;
			event.val = msg.pcval();
			event.midi_chan = msg.status.channel;

		} else if (msg.is_command<MidiCommand::ChannelPressure>()) {
			event.type = Midi::Event::Type::ChanPress;
			event.val = msg.chan_pressure();
			event.midi_chan = msg.status.channel;

		} else if (msg.is_command<MidiCommand::PitchBend>()) {
			event.type = Midi::Event::Type::Bend;
			event.val = msg.bend();
			event.midi_chan = msg.status.channel;

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

		auto first = next;

		while (midi_notes[next].gate == true) {
			if (next == last_poly_chan) {
				next = first;
				break;
			}

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
