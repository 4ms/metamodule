#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include "midi_router.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>

namespace MetaModule
{

class MidiSync {
private:
	MidiQueue midi_out_queue;
	bool queue_subscribed = false;

	// cc_values[midichan][ccnum]: valueless => not set, otherwise value is last value sent
	std::array<std::array<std::optional<uint8_t>, 128>, 16> cc_values{};

	// note_gate_values[midichan][note_num]
	std::array<std::array<std::optional<uint8_t>, 128>, 16> note_gate_values{};

	// pitchwheel_values[midichan]
	std::array<std::optional<uint16_t>, 16> pitchwheel_values{};

public:
	MidiSync() {
		if (!queue_subscribed) {
			MetaModule::MidiRouter::subscribe_tx(&midi_out_queue);
			queue_subscribed = true;
		}
	}

	~MidiSync() {
		if (queue_subscribed) {
			MetaModule::MidiRouter::unsubscribe_tx(&midi_out_queue);
		}
	}

	// Clear all stored last values
	void clear_last_values() {
		// Initialize arrays
		for (auto &chan : cc_values)
			chan.fill(std::nullopt);

		for (auto &chan : note_gate_values)
			chan.fill(std::nullopt);

		pitchwheel_values.fill(std::nullopt);
	}

	// Send MIDI CC message for parameter value change
	// Only sends if the value has changed from last time
	void sync_param_to_midi(float value, uint8_t midi_chan, uint8_t cc_num) {
		if (midi_chan >= cc_values.size() || cc_num >= cc_values[midi_chan].size())
			return;

		uint8_t cc_value = std::clamp(static_cast<int>(value * 127.0f), 0, 127);

		auto &cc_val = cc_values[cc_num][midi_chan];

		if (cc_val != cc_value) {
			MidiMessage cc_msg;
			cc_msg.status = MidiStatusByte{MidiCommand::ControlChange, midi_chan};
			cc_msg.data.byte[0] = cc_num;
			cc_msg.data.byte[1] = cc_value;

			midi_out_queue.put(cc_msg);

			// Update stored value
			cc_val = cc_value;
		}
	}

	void sync_param_to_midi_notegate(float value, uint8_t midi_chan, uint8_t note_num) {
		if (midi_chan >= note_gate_values.size() || note_num >= note_gate_values[midi_chan].size())
			return;

		bool gate_on = value > 0.5f;
		auto &note_val = note_gate_values[note_num][midi_chan];

		if (note_val != gate_on) {
			if (gate_on) {
				MidiMessage note_msg;
				note_msg.status = MidiStatusByte{MidiCommand::NoteOn, midi_chan};
				note_msg.data.byte[0] = note_num;
				note_msg.data.byte[1] = 127;
				midi_out_queue.put(note_msg);
			} else {
				MidiMessage note_msg;
				note_msg.status = MidiStatusByte{MidiCommand::NoteOff, midi_chan};
				note_msg.data.byte[0] = note_num;
				note_msg.data.byte[1] = 0;
				midi_out_queue.put(note_msg);
			}

			// Update stored value
			note_val = gate_on;
		}
	}

	void sync_param_to_midi_pitchwheel(float value, uint8_t midi_chan) {
		if (midi_chan >= 16)
			return;

		// Convert float [-1.0, 1.0] to 14-bit MIDI value [0, 16383]
		// Center position is 8192 (0x2000)
		uint16_t pitchwheel_value = std::clamp(static_cast<int>((value + 1.0f) * 8191.5f), // Scale to 0-16383
											   0,
											   16383);

		auto &pitch_val = pitchwheel_values[midi_chan];

		if (pitch_val != pitchwheel_value) {
			MidiMessage pitchwheel_msg;
			pitchwheel_msg.status = MidiStatusByte{MidiCommand::PitchBend, midi_chan};
			pitchwheel_msg.data.byte[0] = pitchwheel_value & 0x7F;
			pitchwheel_msg.data.byte[1] = (pitchwheel_value >> 7) & 0x7F;

			midi_out_queue.put(pitchwheel_msg);

			// Update stored value
			pitch_val = pitchwheel_value;
		}
	}
};

//8656

} // namespace MetaModule
