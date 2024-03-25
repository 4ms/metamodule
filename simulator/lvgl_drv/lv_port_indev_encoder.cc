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

	if (e.type == SDL_KEYDOWN && e.key.state == SDL_PRESSED) {
		if (e.key.keysym.sym == keys.click) {
			if (rotary_pressed != ButtonEvent::Pressed) {
				rotary_pressed = ButtonEvent::Pressed;
				data->state = LV_INDEV_STATE_PR;
				// printf("rotary pressed\n");
			}
		}

		if (e.key.keysym.sym == keys.aux_button) {
			//push back event to meta_params
			if (aux_pressed != ButtonEvent::Pressed) {
				aux_pressed = ButtonEvent::Pressed;
				// printf("aux down\n");
			}
		}

		if (e.key.keysym.sym == keys.turn_cw) {
			data->enc_diff += 1;
		}

		if (e.key.keysym.sym == keys.turn_ccw) {
			data->enc_diff -= 1;
		}
	}

	else if (e.type == SDL_KEYUP && e.key.state == SDL_RELEASED)
	{
		_instance->handle_key_up(e.key.keysym.sym, data);
	}

	//Is there more input events?
	data->continue_reading = (SDL_PollEvent(NULL) != 0);
}

void LvglEncoderSimulatorDriver::handle_key_up(SDL_Keycode key, lv_indev_data_t *data) {
	if (key == keys.quit) {
		_instance->set_quit(LV_QUIT);
	}

	if (key == keys.aux_button) {
		if (aux_pressed != ButtonEvent::Released) {
			aux_pressed = ButtonEvent::Released;
			// printf("aux up\n");
		}
	}

	if (key == keys.click) {
		if (rotary_pressed != ButtonEvent::Released) {
			rotary_pressed = ButtonEvent::Released;
			data->state = LV_INDEV_STATE_REL;
			// printf("rotary released\n");
		}
	}

	if (key == keys.param_inc) {
		_instance->param_inc_pressed = true;
	}

	if (key == keys.param_dec) {
		_instance->param_dec_pressed = true;
	}

	if (key == keys.next_knobset) {
		_instance->knobset_change++;
	}

	if (key == keys.prev_knobset) {
		_instance->knobset_change--;
	}

	// 1-8 select which patch output to route to the soundcard left output.
	// Patch output (L + 1) % 8 will be routed to the soundcard right output.
	if (key >= '1' && key <= '8') {
		last_selected_outchan = key - '1';
	}
	// Shift + 1-8 select which patch input to connect to the soundcard left input channel.
	// Soundcard right input channel is routed to patch input (L+1)%8
	// Patch inputs 7 and 8 are Gate In 1 and 2.
	if (key == '!')
		last_selected_inchan = 0;
	if (key == '@')
		last_selected_inchan = 1;
	if (key == '#')
		last_selected_inchan = 2;
	if (key == '$')
		last_selected_inchan = 3;
	if (key == '%')
		last_selected_inchan = 4;
	if (key == '^')
		last_selected_inchan = 5;
	if (key == '&')
		last_selected_inchan = 6;
	if (key == '*')
		last_selected_inchan = 7;

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

int LvglEncoderSimulatorDriver::knobset_changed() {
	auto change = knobset_change;
	knobset_change = 0;
	return change;
}

unsigned LvglEncoderSimulatorDriver::selected_param() {
	return last_selected_param;
}

unsigned LvglEncoderSimulatorDriver::selected_outchan() {
	return last_selected_outchan;
}

unsigned LvglEncoderSimulatorDriver::selected_inchan() {
	return last_selected_inchan;
}
