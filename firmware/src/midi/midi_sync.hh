#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include "midi_router.hh"
#include "util/sequential_map.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

namespace MetaModule
{

class MidiSync {
private:
	MidiQueue midi_out_queue;
	bool queue_subscribed = false;

	// Store last sent values by channel and CC number
	// Key: pair of (midi_chan, cc_num), Value: last sent CC value
	using SyncKey = std::pair<uint8_t, uint8_t>;

	// Map [CCnum, channel] -> 7-bit value
	SequentialMap<SyncKey, uint8_t, 128> cc_values;

	// Map [note, channel] -> on/off
	SequentialMap<SyncKey, bool, 128> note_gate_values;

	// Map channel -> pitchwheel
	SequentialMap<uint8_t, uint16_t, 16> pitchwheel_values;

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
		cc_values.clear();
		note_gate_values.clear();
		pitchwheel_values.clear();
	}

	// Send MIDI CC message for parameter value change
	// Only sends if the value has changed from last time
	void sync_param_to_midi(float value, uint8_t midi_chan, uint8_t cc_num) {
		if (midi_chan >= 16 || cc_num >= 128)
			return;

		uint8_t cc_value = std::clamp(static_cast<int>(value * 127.0f), 0, 127);

		SyncKey key(midi_chan, cc_num);

		auto it = cc_values.find(key);

		if (it == cc_values.end() || it->second != cc_value) {
			MidiMessage cc_msg;
			cc_msg.status = MidiStatusByte{MidiCommand::ControlChange, midi_chan};
			cc_msg.data.byte[0] = cc_num;
			cc_msg.data.byte[1] = cc_value;

			midi_out_queue.put(cc_msg);

			// Update stored value, or create entry
			cc_values[key] = cc_value;
		}
	}

	void sync_param_to_midi_notegate(float value, uint8_t midi_chan, uint8_t note_num) {
		if (midi_chan >= 16 || note_num >= 128)
			return;

		bool gate_on = value > 0.5f;

		SyncKey key(midi_chan, note_num);

		auto it = note_gate_values.find(key);

		if (it == note_gate_values.end() || it->second != gate_on) {
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

			// Update stored value or create entry
			note_gate_values[key] = gate_on;
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

		auto it = pitchwheel_values.find(midi_chan);

		if (it == pitchwheel_values.end() || it->second != pitchwheel_value) {
			MidiMessage pitchwheel_msg;
			pitchwheel_msg.status = MidiStatusByte{MidiCommand::PitchBend, midi_chan};
			pitchwheel_msg.data.byte[0] = pitchwheel_value & 0x7F;
			pitchwheel_msg.data.byte[1] = (pitchwheel_value >> 7) & 0x7F;

			midi_out_queue.put(pitchwheel_msg);

			// Update stored value or create entry
			pitchwheel_values[midi_chan] = pitchwheel_value;
		}
	}
};

} // namespace MetaModule
