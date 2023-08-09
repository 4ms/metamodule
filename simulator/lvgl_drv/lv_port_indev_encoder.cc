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
	_instance = this;

	lv_log("Starting LVGL\n");
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
			if (rotary_pressed != ButtonEvent::Pressed) {
				rotary_pressed = ButtonEvent::Pressed;
				data->state = LV_INDEV_STATE_REL;
				printf("click down\n");
			}
		}

		if (e.key.keysym.sym == keys.aux_button) {
			//push back event to meta_params
			if (aux_pressed != ButtonEvent::Pressed) {
				aux_pressed = ButtonEvent::Pressed;
				printf("aux down\n");
			}
		}
	}

	if (e.type == SDL_KEYUP) {
		_instance->handle_key_press(e.key.keysym.sym, data);
	}

	//Is there more input events?
	data->continue_reading = (SDL_PollEvent(NULL) != 0);
}

void LvglEncoderSimulatorDriver::handle_key_press(SDL_Keycode key, lv_indev_data_t *data) {
	if (key == keys.quit) {
		_instance->set_quit(LV_QUIT);
	}

	if (key == keys.aux_button) {
		if (aux_pressed != ButtonEvent::Released) {
			aux_pressed = ButtonEvent::Released;
			printf("aux up\n");
		}
	}

	if (key == keys.click) {
		if (rotary_pressed != ButtonEvent::Released) {
			rotary_pressed = ButtonEvent::Released;
			data->state = LV_INDEV_STATE_PR;
			printf("click up\n");
		}
	}

	if (key == keys.turn_cw) {
		data->enc_diff = 1;
	}

	if (key == keys.turn_ccw) {
		data->enc_diff = -1;
	}

	if (key == keys.param_inc) {
		_instance->param_inc_pressed = true;
	}

	if (key == keys.param_dec) {
		_instance->param_dec_pressed = true;
	}

	// Keys 0-9 select params 0 - 9, minus => 10, equal => 11
	if (key >= '0' && key <= '9') {
		last_selected_param = key - '0';
	}
	if (key == '-') {
		last_selected_param = 10;
	}
	if (key == '=') {
		last_selected_param = 11;
	}

	// Keys A - F select params 0 - 5 (knobs A,B,C,D,E,F)
	// Keys u - z select params 6 - 11 (knobs u,v,w,x,y,z)
	if (key >= 'a' && key <= 'f')
		last_selected_param = key - 'a';
	if (key >= 'u' && key <= 'z')
		last_selected_param = key - 'u' + 6;
}

LvglEncoderSimulatorDriver::~LvglEncoderSimulatorDriver() {
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

// Getter and Setters

QuitEvent LvglEncoderSimulatorDriver::get_quit() {
	return quit_event;
}

void LvglEncoderSimulatorDriver::set_quit(QuitEvent event) {
	quit_event = event;
}

bool LvglEncoderSimulatorDriver::aux_button_just_pressed() {
	if (aux_pressed == ButtonEvent::Pressed) {
		aux_pressed = ButtonEvent::None;
		return true;
	}
	return false;
}

bool LvglEncoderSimulatorDriver::aux_button_just_released() {
	if (aux_pressed == ButtonEvent::Released) {
		aux_pressed = ButtonEvent::None;
		return true;
	}
	return false;
}

bool LvglEncoderSimulatorDriver::param_inc() {
	bool pressed = param_inc_pressed;
	param_inc_pressed = false;
	return pressed;
}

bool LvglEncoderSimulatorDriver::param_dec() {
	bool pressed = param_dec_pressed;
	param_dec_pressed = false;
	return pressed;
}

unsigned LvglEncoderSimulatorDriver::selected_param() {
	return last_selected_param;
}
