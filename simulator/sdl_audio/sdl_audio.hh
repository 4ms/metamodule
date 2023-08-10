#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <span>

struct SDLAudio {
	struct Frame {
		float l;
		float r;
	};
	using Callback = std::function<void(std::span<Frame>)>;

	SDLAudio(unsigned dev_id = 0);
	~SDLAudio();

	void start(Callback &&cb) {
		callback = std::move(cb);
	}

	void pause();
	void unpause();

private:
	bool is_init = false;
	SDL_AudioDeviceID device;
	SDL_AudioSpec audio_spec;
	unsigned bytes_per_frame;
	Callback callback;

	static void audio_callback(void *userdata, uint8_t *stream, int len);
};
