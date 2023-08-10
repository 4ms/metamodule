#include "sdl_audio.hh"
#include <SDL2/SDL.h>
#include <iostream>
#include <span>

SDLAudio::SDLAudio(unsigned dev_id) {

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

SDLAudio::~SDLAudio() {
	if (!is_init)
		return;

	pause();

	SDL_CloseAudioDevice(device);
}

void SDLAudio::pause() {
	if (is_init) {
		SDL_PauseAudioDevice(device, 1);
	}
}

void SDLAudio::unpause(void) {
	if (is_init) {
		SDL_PauseAudioDevice(device, 0);
	}
}

void SDLAudio::audio_callback(void *userdata, uint8_t *stream, int len) {
	auto instance = static_cast<SDLAudio *>(userdata);

	auto buffer = std::span<Frame>(reinterpret_cast<Frame *>(stream), len / instance->bytes_per_frame);

	instance->callback(buffer);
}
