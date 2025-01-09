#pragma once
#include "patch_play/patch_player.hh"
#include "stream_conf.hh"

namespace MetaModule::Headless
{

struct AudioWrapper {
	AudioWrapper(PatchPlayer &patch_player)
		: player{patch_player} {

		for (auto i = 0u; i < AudioConf::NumInChans; i++)
			player.set_input_jack_patched_status(i, true);

		for (auto i = 0u; i < AudioConf::NumOutChans; i++)
			player.set_output_jack_patched_status(i, true);
	}

	void process(AudioConf::AudioInBuffer in_buff, AudioConf::AudioOutBuffer out_buff) {

		for (unsigned i = 0; auto &out : out_buff) {
			auto &in = in_buff[i++];

			for (auto [i, injack] : enumerate(in.chan)) {
				player.set_panel_input(i, injack);
			}

			// Step patch
			player.update_patch();

			// Get outputs
			for (auto [i, outjack] : enumerate(out.chan)) {
				outjack = player.get_panel_output(i);
			}
		}
	}

private:
	PatchPlayer &player;
};

} // namespace MetaModule::Headless
