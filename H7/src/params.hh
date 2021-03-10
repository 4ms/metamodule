#pragma once
#include "conf/control_conf.hh"
#include "conf/stream_conf.hh"
#include "drivers/stm32xx.h"
#include "util/debouncer.hh"
#include <array>

namespace MetaModule
{
struct Params {
	// Sampled at audio sample rate:
	float cvjacks[NumCVIn] = {0.f};
	Toggler gate_ins[NumGateIn];
	Toggler buttons[2];

	// Same value for an entire block:
	float knobs[NumPot] = {0.f};
	Toggler jack_senses[15];
	float patchcv = 0.f;

	Toggler rotary_button;
	int32_t rotary_motion = 0;
	int32_t rotary_pushed_motion = 0;
	int32_t rotary_position = 0;

	Params &operator=(const Params &that)
	{
		if (this == &that)
			return *this;

		for (int i = 0; i < NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (int i = 0; i < NumGateIn; i++)
			gate_ins[i].copy_state(that.gate_ins[i]);
		for (int i = 0; i < NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (int i = 0; i < NumPot; i++)
			knobs[i] = that.knobs[i];
		for (int i = 0; i < 15; i++)
			jack_senses[i].copy_state(that.jack_senses[i]);
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary_motion = that.rotary_motion;
		rotary_pushed_motion = that.rotary_pushed_motion;
		rotary_position = that.rotary_position;

		return *this;
	}
};

using ParamBlock = std::array<Params, StreamConf::Audio::BlockSize>;
} // namespace MetaModule
