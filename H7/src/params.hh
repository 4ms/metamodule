#pragma once
#include "accel_param.hh"
#include "controls.hh"
#include "drivers/stm32xx.h"
#include "drivers/uart.hh"

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{}

	void update();
	Controls &controls;

	float cvjacks[4];
	float knobs[8];
	bool gate_ins[3];
	bool jack_senses[15];
	bool buttons[2];

	// SelbusQueue selbus_commands;

	float dac_out[2];
	bool clock_out;

private:
	bool knob_moved_while_pressed = false;
};

