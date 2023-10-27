#pragma once
#include "frame.hh"
#include "params_state.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_mods.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "stream_conf.hh"
#include "util/countzip.hh"
#include "util/zip.hh"
#include <iostream>
#include <span>

namespace MetaModule
{

class AudioStream {
	ParamsState &params;
	PatchPlayer &player;
	PatchPlayLoader &patch_loader;
	PatchModQueue &patch_mod_queue;

public:
	AudioStream(ParamsState &params_state,
				PatchPlayer &player,
				PatchPlayLoader &play_loader,
				PatchModQueue &patch_mod_queue)
		: params{params_state}
		, player{player}
		, patch_loader{play_loader}
		, patch_mod_queue{patch_mod_queue} {
	}

	void process(StreamConfSim::Audio::AudioInBuffer in_buff, StreamConfSim::Audio::AudioOutBuffer out_buff) {

		if (mute_on_patch_load(out_buff))
			return;

		handle_patch_mods(patch_mod_queue, player);

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
		if (patch_loader.is_loading_new_patch()) {
			output_silence(out_buff);
			// Acknowlegde patch loader's request to mute audio
			patch_loader.notify_audio_is_muted();
			return true;
		} else {
			patch_loader.audio_not_muted();
		}

		if (!player.is_loaded) {
			output_silence(out_buff);
			return true;
		}

		return false;
	}

	// Fill buffer with 0's
	void output_silence(StreamConfSim::Audio::AudioOutBuffer out_buff) {
		for (auto &frame : out_buff) {
			for (auto &chan : frame.chan)
				chan = 0;
		}
	}
};

} // namespace MetaModule
