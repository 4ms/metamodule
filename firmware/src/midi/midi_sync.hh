#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include "midi_router.hh"
#include <cstdint>
#include <algorithm>
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
    struct KeyHash {
        std::size_t operator()(const SyncKey& k) const {
            return (static_cast<std::size_t>(k.first) << 8) | k.second;
        }
    };
    std::unordered_map<SyncKey, uint8_t, KeyHash> last_values;

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
        last_values.clear();
    }
    
    // Send MIDI CC message for parameter value change
    // Only sends if the value has changed from last time
    void sync_param_to_midi(float value, uint8_t midi_chan, uint8_t cc_num) {
        uint8_t cc_value = std::clamp(static_cast<int>(value * 127.0f), 0, 127);
        
        MidiMessage cc_msg;
        cc_msg.status = MidiStatusByte{MidiCommand::ControlChange, midi_chan};
        cc_msg.data.byte[0] = cc_num;
        cc_msg.data.byte[1] = cc_value;
        
        midi_out_queue.put(cc_msg);
    }
};

} // namespace MetaModule 