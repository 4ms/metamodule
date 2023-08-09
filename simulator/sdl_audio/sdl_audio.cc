#include "sdl_audio.hh"
#include <SDL2/SDL.h>
#include <iostream>

SDLAudio::SDLAudio(unsigned dev_id) {

	auto num_dev = SDL_GetNumAudioDevices(0);

	std::string_view device_name;
	std::cout << "SDL: " << num_dev << " audio devices found\n";
	for (unsigned i = 0; i < num_dev; i++) {
		auto name = SDL_GetAudioDeviceName(i, 0);
		if (dev_id == i)
			device_name = name;
		std::string_view marker = (dev_id == i) ? "> " : "# ";
		std::cout << marker << i << ": " << name << "\n";
	}

	want.freq = 48000;
	want.format = AUDIO_F32;
	want.channels = 2;
	want.samples = 512;
	want.callback = audio_callback;
	want.userdata = this;

	if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)) {
		std::cout << "Error: SDL_INIT_AUDIO not initialized\n";
		return;
	}

	device = SDL_OpenAudioDevice(NULL, 0, &want, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (device == 0) {
		std::cout << "SDL: failed to open audio device: %s\n" << SDL_GetError();
		return;
	}

	std::cout << "SDL: Audio device opened at " << want.freq << "Hz, ";
	std::cout << want.channels << " channels, ";
	std::cout << want.samples << " blocksize, ";
	std::cout << std::hex << want.format << " format code, ";
	// unpauseAudio();
	is_init = true;
}

void SDLAudio::audio_callback(void *userdata, uint8_t *stream, int len) {
	auto instance = static_cast<SDLAudio *>(userdata);
}
