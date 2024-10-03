#pragma once
#include "expanders.hh"
#include "params_state.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_mods.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "stream_conf.hh"
#include "util/countzip.hh"
#include "util/edge_detector.hh"
#include <iostream>
#include <span>

namespace MetaModule
{

class AudioStream {
	ParamsState &params;
	PatchPlayer &player;
	PatchPlayLoader &patch_loader;
	PatchModQueue &patch_mod_queue;

	CalData cal;
	CalData ext_cal;

public:
	AudioStream(ParamsState &params_state,
				PatchPlayer &player,
				PatchPlayLoader &play_loader,
				PatchModQueue &patch_mod_queue)
		: params{params_state}
		, player{player}
		, patch_loader{play_loader}
		, patch_mod_queue{patch_mod_queue} {

		// Pretend that we found an audio expander
		Expanders::ext_audio_found(true);
	}

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
			for (auto [i, knob] : enumerate(params.knobs)) {
				if (knob.changed)
					player.set_panel_param(i, knob.val);
			}

			// MIDI: random stream
			{
				static unsigned random_midi_ctr = 0;
				static uint8_t last_note = 0;

				if (random_midi_ctr % 24000 == 0) {
					last_note = random() & 0x3F + 0x20;
					player.send_raw_midi({0x90, last_note, (uint8_t)random()});
				} else if (random_midi_ctr % 24000 == 12000) {
					player.send_raw_midi({0x80, last_note, 0x00});
				} else if (random_midi_ctr % 36000 == 0) {
					player.send_raw_midi({0xB0, 0x74, (uint8_t)random()});
				}
				random_midi_ctr++;
			}

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
				if (params.is_output_plugged(i)) {
					outjack = player.get_panel_output(i);
					player.set_output_jack_patched_status(i, true);
				} else {
					outjack = 0;
					player.set_output_jack_patched_status(i, false);
				}
			}
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
};

} // namespace MetaModule
