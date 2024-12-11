#pragma once

#include "lvgl.h"
#include <SDL2/SDL.h>
#include <array>

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
	SDL_Keycode param_inc;
	SDL_Keycode param_dec;
	SDL_Keycode param_fine_toggle;
	SDL_Keycode prev_knobset;
	SDL_Keycode next_knobset;
};

enum class ButtonEvent { None, Pressed, Released };

struct LvglEncoderSimulatorDriver {

	LvglEncoderSimulatorDriver(RotaryEncoderKeys &keys);
	~LvglEncoderSimulatorDriver();

	QuitEvent get_quit();
	bool aux_button_just_pressed();
	bool aux_button_just_released();

	bool param_inc();
	bool param_dec();
	bool param_fine();
	int knobset_changed();
	unsigned selected_param();
	unsigned selected_outchan();
	unsigned selected_inchan();

private:
	void set_quit(QuitEvent);
	void handle_key_up(SDL_Keycode key, lv_indev_data_t *data);

	static void keyboard_rotary_read_cb(lv_indev_t *, lv_indev_data_t *);
	static inline LvglEncoderSimulatorDriver *_instance;

	RotaryEncoderKeys &keys;
	lv_indev_t *indev_encoder;
	QuitEvent quit_event = LV_QUIT_NONE;

	ButtonEvent rotary_pressed = ButtonEvent::None;
	ButtonEvent aux_pressed = ButtonEvent::None;

	bool param_inc_pressed = false;
	bool param_dec_pressed = false;
	bool param_fine_mode = false;
	int knobset_change = 0;
	unsigned last_selected_param = 0;
	unsigned last_selected_outchan = 0;
	unsigned last_selected_inchan = 0;
};
