#pragma once
#include "accel_param.hh"
#include "controls.hh"
#include "drivers/stm32xx.h"
#include "drivers/uart.hh"
#include "patch/patch.hh"
#include "util/debouncer.hh"

class Params {
public:
	static constexpr uint32_t num_patches = 3;

	Params(Controls &c);

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

	bool should_redraw_patch = false;
	const Patch &cur_patch()
	{
		return _patches[_cur_patch].patch;
	}
	void next_patch()
	{
		_cur_patch++;
		if (_cur_patch == num_patches)
			_cur_patch = 0;
	}
	void prev_patch()
	{
		if (_cur_patch == 0)
			_cur_patch = num_patches - 1;
		else
			_cur_patch--;
	}

	void set_knob_val(uint32_t knob_id, float val)
	{
		knobs[_pot_map[knob_id]] = val;
	}

private:
	bool _rotary_moved_while_pressed = false;
	uint32_t _cur_patch = 0;
	PatchRef _patches[num_patches];

	const uint8_t _pot_map[8] = {1, 4, 0, 5, 3, 6, 7, 2};
};

