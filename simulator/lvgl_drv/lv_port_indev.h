#pragma once

#include "lvgl.h"
#include <SDL2/SDL.h>

enum QuitEvent {
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

enum class ButtonEvent { None, Pressed, Released };

struct LvglEncoderSimulatorDriver {

	LvglEncoderSimulatorDriver(RotaryEncoderKeys &keys);
	~LvglEncoderSimulatorDriver();

	QuitEvent get_quit();
	bool aux_button_just_pressed();
	bool aux_button_just_released();

private:
	void set_quit(QuitEvent);
	static void keyboard_rotary_read_cb(lv_indev_drv_t *, lv_indev_data_t *);

	RotaryEncoderKeys &keys;
	lv_indev_drv_t indev_drv_keyboard_encoder;
	lv_indev_t *indev_encoder;
	QuitEvent quit_event = LV_QUIT_NONE;

	ButtonEvent rotary_pressed = ButtonEvent::None;
	ButtonEvent aux_pressed = ButtonEvent::None;

	static inline LvglEncoderSimulatorDriver *_instance;
};
