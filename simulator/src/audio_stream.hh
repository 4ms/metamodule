#pragma once
#include "core_m4/midi_controls.hh"
#include "expanders.hh"
#include "midi/midi_router.hh"
#include "params_state.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_mods.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "sim_midi.hh"
#include "stream_conf.hh"
#include "util/countzip.hh"
#include "util/edge_detector.hh"
#include <iostream>
#include <span>

namespace MetaModule
{

class AudioStream {
	ParamsState &param_state;
	PatchPlayer &player;
	PatchPlayLoader &patch_loader;
	PatchModQueue &patch_mod_queue;
	SimMidi &sim_midi;

	CalData cal;
	CalData ext_cal;

	Midi::MessageParser midi_parser;
	bool midi_last_connected = false;

public:
	AudioStream(ParamsState &params_state,
				PatchPlayer &player,
				PatchPlayLoader &play_loader,
				PatchModQueue &patch_mod_queue,
				SimMidi &sim_midi)
		: param_state{params_state}
		, player{player}
		, patch_loader{play_loader}
		, patch_mod_queue{patch_mod_queue}
		, sim_midi{sim_midi} {

		// Pretend that we found an audio expander
		Expanders::ext_audio_found(true);
	}

	std::array<float, PanelDef::NumPot> last_knob_val{};

	void process(StreamConfSim::Audio::AudioInBuffer in_buff, StreamConfSim::Audio::AudioOutBuffer out_buff) {

		if (!is_playing_patch()) {
			output_silence(out_buff);
			return;
		}

		std::optional<bool> update_cal;
		handle_patch_mods(patch_mod_queue, player, {&cal, &ext_cal}, update_cal);

		if (in_buff.size() != out_buff.size()) {
			std::cout << "Buffer size mis-match!\n";
			return;
		}

		for (unsigned i = 0; auto &out : out_buff) {
			auto &in = in_buff[i++];

			// Knobs
			for (auto i = 0u; auto &knob : param_state.knobs) {
				// if (knob.did_change()) { // Why does the changed flag not sync with the SDL audio callback?
				if (std::abs(last_knob_val[i] - knob.val) > 2.5f / 4096.f) {
					last_knob_val[i] = knob.val;
					player.set_panel_param(i, knob.val);
				}
				// }
				i++;
			}

			process_midi();

			// TODO: enable "recording" in SDL
			// Input jacks
			(void)in;
			// for (auto [i, injack] : enumerate(in.chan)) {
			// 	if (params.is_input_plugged(i)) {
			// 		player.set_panel_input(i, injack);
			// 		player.set_input_jack_patched_status(i, true);
			// 	} else
			// 		player.set_input_jack_patched_status(i, false);
			// }

			// Step patch
			player.update_patch();

			// Get outputs
			for (auto [i, outjack] : enumerate(out.chan)) {
				if (param_state.is_output_plugged(i)) {
					outjack = player.get_panel_output(i) / volts_peak;
					player.set_output_jack_patched_status(i, true);
				} else {
					outjack = 0;
					player.set_output_jack_patched_status(i, false);
				}
			}
		}
	}

	// Process one frame's worth of MIDI I/O. Combines the firmware's M4-side
	// parse step (Controls::parse_midi) with the A7-side routing/mapping
	// (AudioStreamMidi::process) since the simulator has no cross-core split.
	void process_midi() {
		unsigned poly_num = player.get_midi_poly_num();
		midi_parser.set_poly_num(poly_num);

		bool connected = sim_midi.is_connected();

		// Pull one received message (if any) and parse it into an event.
		MidiMessage rx_msg{};
		Midi::Event event{};
		if (auto msg = sim_midi.get_incoming()) {
			rx_msg = *msg;
			event = midi_parser.parse(*msg);
		}

		// While disconnected, discard queued outgoing messages so they don't burst
		// out stale when a device is (re)connected.
		if (!connected) {
			while (MidiRouter::pop_outgoing_message())
				;
		}

		// Connection edge -> notify the patch player.
		if (connected != midi_last_connected) {
			if (connected)
				player.set_midi_connected();
			else
				player.set_midi_disconnected();
			midi_last_connected = connected;
		}

		if (!connected)
			return;

		// Forward the received message to subscribed modules (ignore active sensing).
		if (rx_msg.is_sysex() || (rx_msg.status != 0xfe && rx_msg.status != 0)) {
			MidiRouter::push_incoming_message(rx_msg);
		}

		// Pull one message that a module wants to transmit and send it out.
		if (auto tx_msg = MidiRouter::pop_outgoing_message()) {
			sim_midi.send(*tx_msg);
		}

		// Map the parsed event to CV/gate on the patch player (MIDI-map feature).
		using Type = Midi::Event::Type;
		switch (event.type) {
			case Type::NoteOn:
				player.set_midi_note_pitch(event.poly_chan, Midi::note_to_volts(event.note), event.midi_chan);
				player.set_midi_note_gate(event.poly_chan, 10.f, event.midi_chan);
				player.set_midi_note_velocity(event.poly_chan, event.val, event.midi_chan);
				player.set_midi_note_retrig(event.poly_chan, 10.f, event.midi_chan);
				player.set_midi_gate(event.note, 10.f, event.midi_chan);
				break;

			case Type::NoteOff:
				if (event.poly_chan < poly_num)
					player.set_midi_note_gate(event.poly_chan, 0, event.midi_chan);
				player.set_midi_gate(event.note, 0, event.midi_chan);
				break;

			case Type::Aft:
				player.set_midi_note_aftertouch(event.poly_chan, event.val, event.midi_chan);
				break;

			case Type::ChanPress:
				for (unsigned i = 0; i < poly_num; i++)
					player.set_midi_note_aftertouch(i, event.val, event.midi_chan);
				break;

			case Type::CC:
				player.set_midi_cc(event.note, event.val, event.midi_chan);
				break;

			case Type::Bend:
				player.set_midi_cc(128, event.val, event.midi_chan);
				break;

			case Type::Time:
				player.send_midi_time_event(event.note, 10.f);
				break;

			default:
				break;
		}
	}

	// Communicate with PatchLoader to mute audio when changing patches
	bool mute_on_patch_load(StreamConfSim::Audio::AudioOutBuffer out_buff) {
		if (patch_loader.should_fade_down_audio()) {
			output_silence(out_buff);
			// Acknowlegde patch loader's request to mute audio
			patch_loader.notify_audio_is_muted();
			return true;

		} else if (patch_loader.should_fade_up_audio()) {
			patch_loader.notify_audio_not_muted();
		}

		if (!player.is_loaded) {
			output_silence(out_buff);
			return true;
		}

		return false;
	}

	bool is_playing_patch() {
		if (patch_loader.should_fade_down_audio()) {
			output_fade_delta = -1.f / (sample_rate_ * 0.02f);
			if (output_fade_amt <= 0.f) {
				output_fade_amt = 0.f;
				output_fade_delta = 0.f;
				patch_loader.notify_audio_is_muted();
			}

		} else if (patch_loader.should_fade_up_audio()) {
			output_fade_delta = 1.f / (sample_rate_ * 0.02f);
			if (output_fade_amt >= 1.f) {
				output_fade_amt = 1.f;
				output_fade_delta = 0.f;
				patch_loader.notify_audio_not_muted();
				handle_patch_just_loaded();
			}
		}

		return patch_loader.is_playing();
	}

	void handle_patch_just_loaded() {
		// Reset the plug detects
		// this ensures any patched jacks will be detected as a new event
		// and will propagate to the patch player
		for (auto &p : plug_detects)
			p.reset();
	}

	// Fill buffer with 0's
	void output_silence(StreamConfSim::Audio::AudioOutBuffer out_buff) {
		for (auto &frame : out_buff) {
			for (auto &chan : frame.chan)
				chan = 0;
		}
	}

	EdgeStateDetector plug_detects[PanelDef::NumJacks];
	float output_fade_amt = -1.f;
	float output_fade_delta = 0.f;
	float sample_rate_ = 48000.f;
	float volts_peak = 5.f;
};

} // namespace MetaModule
