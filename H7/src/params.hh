#pragma once
#include "accel_param.hh"
#include "controls.hh"
#include "drivers/stm32xx.h"
#include "drivers/uart.hh"
#include "patch/patch.hh"
#include "util/debouncer.hh"

class Params {
public:
	Params(ControlData &c);

	ControlData &control_data;

	// SelbusQueue selbus_commands;

	// bool clock_out
};

class PatchList {
	static constexpr uint32_t num_patches = 6;
	uint8_t audio_load = 0;

	// Todo: move this into PatchManager or PatchList
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

private:
	// bool _rotary_moved_while_pressed = false;
	uint32_t _cur_patch = 0;
	PatchRef _patches[num_patches];
};

