#pragma once
// #include "conf/hsem_conf.hh"
#include "conf/stream_conf.hh"
// #include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include "util/debouncer.hh"
#include <array>

// using namespace MetaModule;

struct Params {
	float cvjacks[4] = {0.f, 0.f, 0.f, 0.f};
	float patchcv = 0.f;
	float knobs[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

	Toggler gate_ins[2];
	Toggler clock_in;
	Toggler jack_senses[15];

	Toggler buttons[2];

	Toggler rotary_button;
	int32_t rotary_motion = 0;
	int32_t rotary_pushed_motion = 0;
	int32_t rotary_position = 0;

	// SelbusQueue selbus_commands;
	// bool clock_out

	void init()
	{
		cvjacks[0] = 0.f;
		cvjacks[1] = 0.f;
		cvjacks[2] = 0.f;
		cvjacks[3] = 0.f;
		knobs[0] = 0.f;
		knobs[1] = 0.f;
		knobs[2] = 0.f;
		knobs[3] = 0.f;
		knobs[4] = 0.f;
		knobs[5] = 0.f;
		knobs[6] = 0.f;
		knobs[7] = 0.f;
		patchcv = 0.f;
		rotary_motion = 0;
		rotary_pushed_motion = 0;
		clock_in.register_rising_edge();
		clock_in.is_just_pressed();
		clock_in.set_state(0);
		gate_ins[0].register_rising_edge();
		gate_ins[0].is_just_pressed();
		gate_ins[0].set_state(0);
		gate_ins[1].register_rising_edge();
		gate_ins[1].is_just_pressed();
		gate_ins[1].set_state(0);

		for (int i = 0; i < 15; i++) {
			jack_senses[i].register_rising_edge();
			jack_senses[i].is_just_pressed();
			jack_senses[i].set_state(0);
		}
	}
};

using ParamBlock = std::array<Params, StreamConf::Audio::BlockSize>;
