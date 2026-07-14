#pragma once
#include "midi/midi_message.hh"
#include "params/midi_params.hh"
#include "patch/midi_def.hh"
#include "util/zip.hh"
#include <algorithm>
#include <optional>

namespace MetaModule::Midi
{

struct MessageParser {
	struct Note {
		uint8_t note = 0;
		bool gate = 0;
	};
	static constexpr unsigned NumMidiChannels = 16;

	std::array<std::array<Note, MaxMidiPolyphony>, NumMidiChannels> all_midi_notes;
	std::array<std::span<Note>, NumMidiChannels> midi_notes;

	std::array<size_t, NumMidiChannels> last_poly_chan;

	// 14-bit CC mode: when enabled, CC 0-31 are MSBs and CC 32-63 are the matching
	// LSBs (CC n+32). The last MSB received for each CC is stored so it can be
	// combined with a later LSB. Storage is not per-channel (see parse()).
	bool midi_14bit_mode = false;
	std::array<uint8_t, 32> cc_msb{};

	MessageParser() {
		for (auto [span, backing] : zip(midi_notes, all_midi_notes)) {
			span = backing;
		}
		std::ranges::fill(last_poly_chan, MaxMidiPolyphony);
	}

	void set_poly_num(uint32_t poly_chans) {
		poly_chans = std::clamp<uint32_t>(poly_chans, 1U, all_midi_notes.size());

		for (auto [chan, backing] : zip(midi_notes, all_midi_notes)) {
			if (poly_chans != chan.size()) {
				chan = std::span{backing.begin(), poly_chans};
			}
		}
	}

	void set_14bit_mode(bool enabled) {
		midi_14bit_mode = enabled;
	}

	Midi::Event parse(MidiMessage msg) {

		Midi::Event event{};

		auto chan = msg.status.channel;

		// Monophonic MIDI CV/Gate
		if (msg.is_noteoff()) {

			// Find the note in held midi_notes, and get the poly chan if found.
			event.poly_chan = -1;
			for (unsigned i = 0; auto &midi_note : midi_notes[chan]) {
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

			last_poly_chan[chan] = find_polyphonic_slot_rotate(midi_notes[chan], msg.note(), last_poly_chan[chan]);
			Note &midi_note = midi_notes[chan][last_poly_chan[chan]];
			midi_note.note = msg.note();
			midi_note.gate = true;

			event.type = Midi::Event::Type::NoteOn;
			event.poly_chan = last_poly_chan[chan];
			event.note = msg.note();
			event.val = msg.velocity();
			event.midi_chan = msg.status.channel;

		} else if (msg.is_command<MidiCommand::PolyKeyPressure>()) { //aka Aftertouch
			for (unsigned i = 0; auto &midi_note : midi_notes[chan]) {
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

	size_t find_polyphonic_slot_rotate(std::span<Note> midi_notes, uint8_t note, size_t last_poly_ch) {
		auto next = last_poly_ch + 1;
		if (next >= midi_notes.size())
			next = 0;

		auto first = next;

		while (midi_notes[next].gate == true) {
			if (next == last_poly_ch) {
				next = first;
				break;
			}

			next++;
			if (next >= midi_notes.size())
				next = 0;
		}
		return next;
	}

	size_t find_polyphonic_slot_first_available(std::span<Note> midi_notes, uint8_t note) {
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
	uint8_t noteoff_seq_chan = 0;

	void start_all_notes_off_sequence() {
		noteoff_seq_in_progress = true;
		noteoff_seq_cur_step = 0;
		noteoff_seq_chan = 0;
	}

	// Sends NoteOff to all poly channels, one by one, each time it's called
	// Returns Event Type None when done, and returns nullopt if not running
	std::optional<Midi::Event> step_all_notes_off_sequence() {
		if (!noteoff_seq_in_progress)
			return std::nullopt;

		if (noteoff_seq_chan < NumMidiChannels) {
			auto event = Midi::Event{
				.type = Midi::Event::Type::NoteOff, .midi_chan = noteoff_seq_chan, .poly_chan = noteoff_seq_cur_step};
			midi_notes[noteoff_seq_chan][noteoff_seq_cur_step].gate = false;

			noteoff_seq_cur_step++;
			if (noteoff_seq_cur_step >= 128) {
				noteoff_seq_cur_step = 0;
				noteoff_seq_chan++;
			}
			return event;
		}

		noteoff_seq_in_progress = false;
		noteoff_seq_cur_step = 0;
		return Midi::Event{.type = Midi::Event::Type::None};
	}
};

} // namespace MetaModule::Midi
