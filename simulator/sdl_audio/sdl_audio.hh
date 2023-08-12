#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <iostream>
#include <span>

template<typename Frame>
struct SDLAudio {
	using Callback = std::function<void(std::span<Frame>)>;

	SDLAudio(unsigned dev_id = 0) {

		auto num_dev = SDL_GetNumAudioDevices(0);

		const char *device_name = nullptr; //nullptr tells SDL to select the default

		std::cout << "SDL: " << num_dev << " audio devices found\n";
		for (unsigned i = 0; i < num_dev; i++) {
			auto name = SDL_GetAudioDeviceName(i, 0);
			std::cout << i << ": " << name;
			if (dev_id == i) {
				device_name = name;
				std::cout << " (selected)";
			}
			std::cout << "\n";
		}

		SDL_AudioSpec requested{
			.freq = 48000,
			.format = AUDIO_F32,
			.channels = 2,
			.samples = 512,
			.callback = audio_callback,
			.userdata = this,
		};

		std::memset(&audio_spec, 0, sizeof audio_spec);

		if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)) {
			std::cout << "Error: SDL_INIT_AUDIO not initialized\n";
			return;
		}

		device = SDL_OpenAudioDevice(device_name, 0, &requested, &audio_spec, SDL_AUDIO_ALLOW_ANY_CHANGE);
		if (device == 0) {
			std::cout << "SDL: failed to open audio device: %s\n" << SDL_GetError();
			return;
		}
		is_init = true;

		bytes_per_frame = (int)audio_spec.channels * ((audio_spec.format == AUDIO_F32) ? 4 : 4);

		std::cout << "SDL: Audio device " << device << " opened at " << audio_spec.freq << "Hz, ";
		std::cout << (int)audio_spec.channels << " channels, ";
		std::cout << audio_spec.samples << " blocksize, ";
		std::cout << bytes_per_frame << " bytes per frame, ";
		std::cout << std::hex << audio_spec.format << " format code\n";

		pause();
	}

	~SDLAudio() {
		if (!is_init)
			return;

		pause();

		SDL_CloseAudioDevice(device);
	}

	void start(Callback &&cb) {
		callback = std::move(cb);
	}

	void pause() {
		if (is_init) {
			SDL_PauseAudioDevice(device, 1);
		}
	}

	void unpause() {
		if (is_init) {
			SDL_PauseAudioDevice(device, 0);
		}
	}

private:
	bool is_init = false;
	SDL_AudioDeviceID device;
	SDL_AudioSpec audio_spec;
	unsigned bytes_per_frame;
	Callback callback;

	static void audio_callback(void *userdata, uint8_t *stream, int len) {
		auto instance = static_cast<SDLAudio *>(userdata);

		auto buffer = std::span<Frame>(reinterpret_cast<Frame *>(stream), len / instance->bytes_per_frame);

		instance->callback(buffer);
	}
};
