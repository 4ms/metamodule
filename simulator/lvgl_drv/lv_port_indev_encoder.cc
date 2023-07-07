// SPDX-License-Identifier: MIT

#include "lv_port_indev.h"
#include "lvgl.h"
#include <SDL2/SDL.h>

LvglEncoderSimulatorDriver::LvglEncoderSimulatorDriver(RotaryEncoderKeys &keys)
	: keys{keys} {

	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	lv_indev_drv_init(&indev_drv_keyboard_encoder);
	indev_drv_keyboard_encoder.type = LV_INDEV_TYPE_ENCODER;
	indev_drv_keyboard_encoder.read_cb = keyboard_rotary_read_cb;
	indev_encoder = lv_indev_drv_register(&indev_drv_keyboard_encoder);

	set_quit(LV_QUIT_NONE);
	aux_pressed = false;
	_instance = this;

	lv_log("Starting LVGL\n");
}

lv_quit_event_t LvglEncoderSimulatorDriver::get_quit() {
	return quit_event;
}

void LvglEncoderSimulatorDriver::set_quit(lv_quit_event_t event) {
	quit_event = event;
}

bool LvglEncoderSimulatorDriver::get_aux_button() {
	return aux_pressed;
}

void LvglEncoderSimulatorDriver::keyboard_rotary_read_cb(lv_indev_drv_t *, lv_indev_data_t *data) {
	auto &keys = _instance->keys;
	auto &rotary_pressed = _instance->rotary_pressed;
	auto &aux_pressed = _instance->aux_pressed;

	// why static?
	static SDL_Event e;

	data->continue_reading = false;

	if (!SDL_PollEvent(&e))
		return;

	if (e.type == SDL_WINDOWEVENT) {
		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			_instance->set_quit(LV_QUIT);
		}
	}

	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == keys.click) {
			if (!rotary_pressed) {
				rotary_pressed = true;
				data->state = LV_INDEV_STATE_REL;
				printf("click down\n");
			}
		}

		if (e.key.keysym.sym == keys.aux_button) {
			//push back event to meta_params
			if (!aux_pressed) {
				aux_pressed = true;
				printf("aux down\n");
			}
		}
	}

	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == keys.quit) {
			_instance->set_quit(LV_QUIT);
		}

		if (e.key.keysym.sym == keys.aux_button) {
			if (aux_pressed) {
				aux_pressed = false;
				printf("aux up\n");
			}
		}

		if (e.key.keysym.sym == keys.click) {
			if (rotary_pressed) {
				rotary_pressed = false;
				data->state = LV_INDEV_STATE_PR;
				printf("click up\n");
			}
		}

		if (e.key.keysym.sym == keys.turn_cw) {
			data->enc_diff = 1;
		}

		if (e.key.keysym.sym == keys.turn_ccw) {
			data->enc_diff = -1;
		}
	}

	//Is there more input events?
	data->continue_reading = (SDL_PollEvent(NULL) != 0);
}

LvglEncoderSimulatorDriver::~LvglEncoderSimulatorDriver() {
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}
