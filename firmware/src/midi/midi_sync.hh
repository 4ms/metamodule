#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include "midi_router.hh"
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <unordered_map>
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
    
    // Fixed-size arrays for CC and note gate tracking
    struct CCValue {
        std::optional<SyncKey> key;
        uint8_t value;
    };
    std::array<CCValue, 128> cc_values;
    
    struct NoteGateValue {
        std::optional<SyncKey> key;
        bool value;
    };
    std::array<NoteGateValue, 128> note_gate_values;

    struct PitchWheelValue {
        std::optional<uint8_t> key;
        uint16_t value;  // Changed to uint16_t for 14-bit resolution
    };
    std::array<PitchWheelValue, 16> pitchwheel_values;

public:
    MidiSync() {
        if (!queue_subscribed) {
            MetaModule::MidiRouter::subscribe_tx(&midi_out_queue);
            queue_subscribed = true;
        }
        // Initialize arrays
        cc_values.fill({std::nullopt, 0});
        note_gate_values.fill({std::nullopt, false});
        pitchwheel_values.fill({std::nullopt, 8192});  // Center position (0x2000)
    }

    ~MidiSync() {
        if (queue_subscribed) {
            MetaModule::MidiRouter::unsubscribe_tx(&midi_out_queue);
        }
    }
    
    // Clear all stored last values
    void clear_last_values() {
        cc_values.fill({std::nullopt, 0});
        note_gate_values.fill({std::nullopt, false});
    }
    
    // Send MIDI CC message for parameter value change
    // Only sends if the value has changed from last time
    void sync_param_to_midi(float value, uint8_t midi_chan, uint8_t cc_num) {
        if (cc_num >= 128) return;
        
        uint8_t cc_value = std::clamp(static_cast<int>(value * 127.0f), 0, 127);
        
        auto& cc_val = cc_values[cc_num];
        bool should_send = !cc_val.key.has_value() || 
                          cc_val.key->first != midi_chan || 
                          cc_val.value != cc_value;
        
        if (should_send) {
            MidiMessage cc_msg;
            cc_msg.status = MidiStatusByte{MidiCommand::ControlChange, midi_chan};
            cc_msg.data.byte[0] = cc_num;
            cc_msg.data.byte[1] = cc_value;
            
            midi_out_queue.put(cc_msg);
            
            // Update stored value
            cc_val.key = SyncKey(midi_chan, cc_num);
            cc_val.value = cc_value;
        }
    }

    void sync_param_to_midi_notegate(float value, uint8_t midi_chan, uint8_t note_num) {
        if (midi_chan >= 16 || note_num >= 128) {
            return;
        }   

        bool gate_on = value > 0.5f;
        auto& note_val = note_gate_values[note_num];
        bool should_send = !note_val.key.has_value() || 
                          note_val.key->first != midi_chan || 
                          note_val.value != gate_on;
        
        if (should_send) {
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
            note_val.key = SyncKey(midi_chan, note_num);
            note_val.value = gate_on;
        }
    }

    void sync_param_to_midi_pitchwheel(float value, uint8_t midi_chan) {
        if (midi_chan >= 16) return;

        // Convert float [-1.0, 1.0] to 14-bit MIDI value [0, 16383]
        // Center position is 8192 (0x2000)
        uint16_t pitchwheel_value = std::clamp(
            static_cast<int>((value + 1.0f) * 8191.5f),  // Scale to 0-16383
            0, 16383
        );

        auto& pitch_val = pitchwheel_values[midi_chan];
        bool should_send = !pitch_val.key.has_value() || 
                          pitch_val.value != pitchwheel_value;

        if (should_send) {
            MidiMessage pitchwheel_msg;
            pitchwheel_msg.status = MidiStatusByte{MidiCommand::PitchBend, midi_chan};
            pitchwheel_msg.data.byte[0] = pitchwheel_value & 0x7F;
            pitchwheel_msg.data.byte[1] = (pitchwheel_value >> 7) & 0x7F;
            
            midi_out_queue.put(pitchwheel_msg);
            
            // Update stored value
            pitch_val.key = midi_chan;
            pitch_val.value = pitchwheel_value;
        }
    }
};

} // namespace MetaModule 