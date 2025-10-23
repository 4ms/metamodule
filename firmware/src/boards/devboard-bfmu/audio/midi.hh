#pragma once
#include "midi/midi_message.hh"
#include "midi/midi_router.hh"
#include "params/sync_params.hh"
#include "patch_play/patch_player.hh"

namespace MetaModule
{

struct AudioStreamMidi {
	PatchPlayer &player;
	SyncParams &sync_params;

	bool last_connected = false;

	AudioStreamMidi(PatchPlayer &player, SyncParams &sync_params)
		: player{player}
		, sync_params{sync_params} {
	}

	void process(bool is_connected, Midi::Event const &event, unsigned poly_num, MidiMessage *raw_msg) {

		if (!player.is_loaded)
			return;

		if (is_connected && !last_connected) {
			player.set_midi_connected();
		} else if (!is_connected && last_connected) {
			player.set_midi_disconnected();
		}

		last_connected = is_connected;

		if (!is_connected)
			return;

		// Transfer MIDI RX message to router (from hardware)
		// Ignore active-sensing
		if (raw_msg->status != 0xfe && raw_msg->status != 0) {
			// 50ns with no listeners + ~100ns additional per listener
			MidiRouter::push_incoming_message(*raw_msg);
		}

		// Transfer MIDI TX message from router (towards hardware)
		if (auto tx_msg = MidiRouter::pop_outgoing_message()) {
			*raw_msg = *tx_msg;
		} else {
			*raw_msg = MidiMessage{};
		}

		if (event.type == Midi::Event::Type::None)
			return;
	}
};

} // namespace MetaModule
