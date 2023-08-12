#pragma once
#include "frame.hh"
#include "params_state.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "util/countzip.hh"
#include <span>

namespace MetaModule
{

class AudioStream {
	ParamsState &params;
	PatchPlayer &player;
	PatchPlayLoader &patch_loader;

public:
	AudioStream(ParamsState &params_state, PatchPlayer &player, PatchPlayLoader &play_loader)
		: params{params_state}
		, player{player}
		, patch_loader{play_loader} {
	}

	void play(std::span<Frame> output_buffer) {

		if (patch_loader.is_loading_new_patch()) {
			if (!patch_loader.is_audio_muted()) {
				// output_silence(out);
				patch_loader.audio_is_muted();
			}
			return;
		} else {
			patch_loader.audio_not_muted();
		}

		if (!player.is_loaded) {
			// output_silence(out);
			return;
		}

		for (auto &sample : output_buffer) {
			// Update knobs
			for (auto [i, knob] : enumerate(params.knobs)) {
				if (knob.changed)
					player.set_panel_param(i, knob.val);
			}

			// TODO: route audio input to input jacks

			// Step patch
			player.update_patch();

			// Get outputs
			// TODO: keyboard-assignable outputs
			sample.l = player.get_panel_output(0);
			sample.r = player.get_panel_output(1);
		}
	}
};

} // namespace MetaModule
