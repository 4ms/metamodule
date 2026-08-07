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

	uint8_t last_connected = false;

	AudioStreamMidi(PatchPlayer &player, SyncParams &sync_params)
		: player{player}
		, sync_params{sync_params} {
	}

	// `rx_port` is the port raw_msg arrived on (Midi::Event::Port)
	void process(
		uint8_t ports_connected, Midi::Event const &event, unsigned poly_num, MidiMessage *raw_msg, uint8_t rx_port) {

		if (event.type == Midi::Event::Type::PC) {
			sync_params.midi_events.put(event);
		}

		// Consume the incoming message even if MIDI is not connected
		MidiMessage rx_msg = *raw_msg;
		*raw_msg = MidiMessage{};

		// Discard MIDI generated while not connected so it won't transmit
		// on MIDI attachment
		if (ports_connected == 0) {
			while (MidiRouter::pop_outgoing_message())
				;
		}

		if (!player.is_loaded)
			return;

		if (ports_connected && !last_connected) {
			player.set_midi_connected();
		} else if (!ports_connected && last_connected) {
			player.set_midi_disconnected();
		}

		last_connected = ports_connected;

		if (!ports_connected)
			return;

		// Transfer MIDI RX message to router (from hardware)
		// Ignore active-sensing
		if (rx_msg.is_sysex() || (rx_msg.status != 0xfe && rx_msg.status != 0)) {
			// 50ns with no listeners + ~100ns additional per listener
			MidiRouter::push_incoming_message(rx_msg, rx_port);
		}

		// Transfer MIDI TX message from router (towards hardware)
		if (auto tx_msg = MidiRouter::pop_outgoing_message()) {
			*raw_msg = *tx_msg;
		}

		if (event.type == Midi::Event::Type::None)
			return;

		// All other MIDI events: 150ns min (no listeners) + more... 150-600ns for some listeners
		if (event.type == Midi::Event::Type::NoteOn) {
			player.set_midi_note_pitch(event.poly_chan, Midi::note_to_volts(event.note), event.midi_chan);
			player.set_midi_note_gate(event.poly_chan, 10.f, event.midi_chan);
			player.set_midi_note_velocity(event.poly_chan, event.val, event.midi_chan);
			player.set_midi_note_retrig(event.poly_chan, 10.f, event.midi_chan);
			player.set_midi_gate(event.note, 10.f, event.midi_chan);
			sync_params.midi_events.put(event);

		} else if (event.type == Midi::Event::Type::NoteOff) {
			if (event.poly_chan < poly_num) {
				player.set_midi_note_gate(event.poly_chan, 0, event.midi_chan);
			}
			player.set_midi_gate(event.note, 0, event.midi_chan);
			sync_params.midi_events.put(event);

		} else if (event.type == Midi::Event::Type::Aft) {
			player.set_midi_note_aftertouch(event.poly_chan, event.val, event.midi_chan);

		} else if (event.type == Midi::Event::Type::ChanPress) {
			for (unsigned i = 0; i < poly_num; i++)
				player.set_midi_note_aftertouch(i, event.val, event.midi_chan);

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
