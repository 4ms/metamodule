#pragma once
#include <SDL2/SDL.h>

struct SDLAudio {
	SDLAudio(unsigned dev_id);

private:
	bool is_init = false;
	SDL_AudioDeviceID device;
	SDL_AudioSpec want;

	static void audio_callback(void *userdata, uint8_t *stream, int len);
};
