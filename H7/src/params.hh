#pragma once
#include "accel_param.hh"
#include "controls.hh"
#include "drivers/stm32xx.h"
#include "drivers/uart.hh"
#include "util/debouncer.hh"

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{}

	void update();
	Controls &controls;

	float cvjacks[4] = {0.f};
	float patchcv = 0.f;
	float knobs[8] = {0.f};

	Toggler gate_ins[2];
	Toggler clock_in;
	Toggler jack_senses[15];

	Toggler buttons[2];
	Toggler rotary_button;

	int32_t rotary_motion = 0;
	int32_t rotary_pushed_motion = 0;

	// SelbusQueue selbus_commands;

	float dac_out[2];
	bool clock_out;

	uint8_t audio_load = 0;
private:
	bool _rotary_moved_while_pressed = false;
};

