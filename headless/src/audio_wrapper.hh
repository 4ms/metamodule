#pragma once
#include "patch_play/patch_player.hh"

struct AudioWrapper {
	AudioWrapper(PatchPlayer &patch_player)
		: patch_player{patch_player} {
	}

	void process(StreamConfSim::Audio::AudioInBuffer in_buff, StreamConfSim::Audio::AudioOutBuffer out_buff) {

		for (unsigned i = 0; auto &out : out_buff) {
			auto &in = in_buff[i++];

			// TODO: enable "recording" in SDL
			// Input jacks

			for (auto [i, injack] : enumerate(in.chan)) {
				if (params.is_input_plugged(i)) {
					player.set_panel_input(i, injack);
					player.set_input_jack_patched_status(i, true);
				} else
					player.set_input_jack_patched_status(i, false);
			}

			// Step patch
			player.update_patch();

			// Get outputs
			for (auto [i, outjack] : enumerate(out.chan)) {
				outjack = player.get_panel_output(i);
				player.set_output_jack_patched_status(i, true);
			}
		}
	}

private:
	PatchPlayer &patch_player;
};
