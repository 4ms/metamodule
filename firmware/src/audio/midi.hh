#pragma once
#include "midi/midi_message.hh"
#include "midi/midi_router.hh"
#include "params/sync_params.hh"
#include "patch_play/patch_player.hh"

namespace MetaModule
{

struct AudioStreamMidi {
	//
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

		// All other MIDI events: 150ns min (no listeners) + more... 150-600ns for some listeners
		if (event.type == Midi::Event::Type::NoteOn) {
			player.set_midi_note_pitch(event.poly_chan, Midi::note_to_volts(event.note));
			player.set_midi_note_gate(event.poly_chan, 10.f);
			player.set_midi_note_velocity(event.poly_chan, event.val);
			player.set_midi_note_retrig(event.poly_chan, 10.f);
			player.set_midi_gate(event.note, 10.f);
			sync_params.midi_events.put(event);

		} else if (event.type == Midi::Event::Type::NoteOff) {
			player.set_midi_note_gate(event.poly_chan, 0);
			player.set_midi_gate(event.note, 0);
			sync_params.midi_events.put(event);

		} else if (event.type == Midi::Event::Type::Aft) {
			player.set_midi_note_aftertouch(event.poly_chan, event.val);

		} else if (event.type == Midi::Event::Type::ChanPress) {
			for (unsigned i = 0; i < poly_num; i++)
				player.set_midi_note_aftertouch(i, event.val);

		} else if (event.type == Midi::Event::Type::CC) {
			player.set_midi_cc(event.note, event.val, event.midi_chan);
			sync_params.midi_events.put(event);

		} else if (event.type == Midi::Event::Type::Bend) {
			player.set_midi_cc(128, event.val, event.midi_chan);

		} else if (event.type == Midi::Event::Type::Time) {
			player.send_midi_time_event(event.note, 10.f);
		}
	}
};

} // namespace MetaModule
