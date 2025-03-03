#pragma once
#include "patch_play/patch_player.hh"
#include "stream_conf.hh"
#include <jack/jack.h>

namespace MetaModule::Headless
{

struct AudioWrapper {

	AudioWrapper(PatchPlayer &patch_player)
		: player{patch_player} {

		for (auto i = 0u; i < AudioConf::NumInChans; i++)
			player.set_input_jack_patched_status(i, true);

		for (auto i = 0u; i < AudioConf::NumOutChans; i++)
			player.set_output_jack_patched_status(i, true);

		client = jack_client_open("MetaModule", {}, {});
		if (!client) {
			return;
		}

		for (auto i = 0u; i < out.size(); i++) {
			const std::string name = "out_" + std::to_string(i);
			out[i] = jack_port_register(client, name.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
			if (!out[i]) {
				return;
			}
		}

		for (auto i = 0u; i < in.size(); i++) {
			const std::string name = "in_" + std::to_string(i);
			in[i] = jack_port_register(client, name.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
			if (!in[i]) {
				return;
			}
		}

		if (jack_set_process_callback(client, onJackProcess, this)) {
			return;
		}
	}

	~AudioWrapper() {
		for (auto &i : in) {
			jack_port_unregister(client, i);
		}

		for (auto &o : out) {
			jack_port_unregister(client, o);
		}

		jack_client_close(client);
	}

	bool start() {
		if (jack_activate(client)) {
			jack_client_close(client);
			return false;
		}

		const auto ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical | JackPortIsInput);
		if (ports == NULL) {
			printf("no phys playback ports\n");
			return false;
		}

		for (auto i = 0; i < 2; ++i) {
			if (jack_connect(client, jack_port_name(out[i]), ports[i])) {
				printf("cannon connect port\n");
				return false;
			}
		}

		jack_free(ports);

		return true;
	}

	bool stop() {
		if (jack_deactivate(client)) {
			jack_client_close(client);
			return false;
		}
		return true;
	}

private:
	jack_client_t *client{};
	std::array<jack_port_t *, AudioConf::NumOutChans> out;
	std::array<jack_port_t *, AudioConf::NumInChans> in;

	PatchPlayer &player;

	void onJackProcess(jack_nframes_t nFrames) {
		std::array<float *, 2> ip{};
		std::array<float *, 2> op{};

		for (auto i = 0u; i < in.size(); i++) {
			ip[i] = reinterpret_cast<float *>(jack_port_get_buffer(in[i], nFrames));
		}

		for (auto i = 0u; i < out.size(); i++) {
			op[i] = reinterpret_cast<float *>(jack_port_get_buffer(out[i], nFrames));
		}

		for (auto i = 0u; i < nFrames; ++i) {
			player.set_panel_input(0, ip[0][i] * 10);
			player.set_panel_input(1, ip[1][i] * 10);

			player.update_patch();

			op[0][i] = player.get_panel_output(0) / 12;
			op[1][i] = player.get_panel_output(1) / 12;
		}
	}

	static int onJackProcess(jack_nframes_t nFrames, void *args) {
		static_cast<AudioWrapper *>(args)->onJackProcess(nFrames);
		return 0;
	}
};

} // namespace MetaModule::Headless
