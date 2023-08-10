#pragma once
#include <SDL2/SDL.h>

struct SDLAudio {
	SDLAudio(unsigned dev_id);
	~SDLAudio();

	void pause();
	void unpause();

private:
	bool is_init = false;
	SDL_AudioDeviceID device;
	SDL_AudioSpec audio_spec;

	static void audio_callback(void *userdata, uint8_t *stream, int len);
};
