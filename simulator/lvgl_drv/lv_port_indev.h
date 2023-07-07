#pragma once

#include "lvgl.h"
#include <SDL2/SDL.h>

enum lv_quit_event_t {
	LV_QUIT_NONE,
	LV_REBOOT,
	LV_SHUTDOWN,
	LV_QUIT,
	LV_QUIT_OTHER,
};

struct RotaryEncoderKeys {
	SDL_Keycode turn_cw;
	SDL_Keycode turn_ccw;
	SDL_Keycode click;
	SDL_Keycode aux_button;
	SDL_Keycode quit;
};

struct LvglEncoderSimulatorDriver {

	LvglEncoderSimulatorDriver(RotaryEncoderKeys &keys);
	~LvglEncoderSimulatorDriver();

	lv_quit_event_t get_quit();
	bool get_aux_button();

private:
	void set_quit(lv_quit_event_t);
	static void keyboard_rotary_read_cb(lv_indev_drv_t *, lv_indev_data_t *);

	RotaryEncoderKeys &keys;
	lv_indev_drv_t indev_drv_keyboard_encoder;
	lv_indev_t *indev_encoder;
	lv_quit_event_t quit_event = LV_QUIT_NONE;
	bool rotary_pressed = false;
	bool aux_pressed = false;

	static inline LvglEncoderSimulatorDriver *_instance;
};
