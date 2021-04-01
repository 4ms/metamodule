#pragma once
#include "conf/control_conf.hh"
#include "conf/stream_conf.hh"
#include "debug.hh"
#include "drivers/stm32xx.h"
#include "util/debouncer.hh"
#include <array>

namespace MetaModule
{
struct RotaryMotion {
	int32_t abs_pos = 0;
	int32_t motion = 0;

	int32_t use_motion()
	{
		auto tmp = motion;
		motion = 0;
		return tmp;
	}
	void add_motion(const RotaryMotion &that)
	{
		motion += that.motion;
		abs_pos += that.motion;
	}
	void transfer_motion(RotaryMotion &that)
	{
		auto that_motion = that.use_motion();
		motion += that_motion;
		abs_pos += that_motion;
	}
};

struct Params {
	// Sampled at audio sample rate:
	float cvjacks[NumCVIn] = {0.f};
	Toggler gate_ins[NumGateIn];
	Toggler buttons[2];

	// Same value for an entire block:
	float knobs[NumPot] = {0.f};
	uint16_t jack_senses;

	Params()
	{
		clear();
	}

	void clear()
	{
		for (int i = 0; i < NumCVIn; i++)
			cvjacks[i] = 0.f;
		for (int i = 0; i < NumGateIn; i++)
			gate_ins[i].reset();
		for (int i = 0; i < NumRgbButton; i++)
			buttons[i].reset();
		for (int i = 0; i < NumPot; i++)
			knobs[i] = 0.f;
		jack_senses = 0;
	}

	void copy(const Params &that)
	{
		for (int i = 0; i < NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (int i = 0; i < NumGateIn; i++)
			gate_ins[i].copy_state(that.gate_ins[i]);
		for (int i = 0; i < NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (int i = 0; i < NumPot; i++)
			knobs[i] = that.knobs[i];
		jack_senses = that.jack_senses;
	}
};

struct MetaParams {
	float patchcv = 0.f;
	Toggler rotary_button;
	RotaryMotion rotary;
	RotaryMotion rotary_pushed;

	MetaParams()
	{
		clear();
	}

	void clear()
	{
		patchcv = 0.f;
		rotary_button.reset();
		rotary.motion = 0;
		rotary.abs_pos = 0;
		rotary_pushed.motion = 0;
		rotary_pushed.abs_pos = 0;
	}

	// Copies some data, adds other data (rotary motion)
	void update_with(const MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary.add_motion(that.rotary);
		rotary_pushed.add_motion(that.rotary_pushed);
	}
	void copy(const MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary = that.rotary;
		rotary_pushed = that.rotary_pushed;
	}
	void transfer(MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary.transfer_motion(that.rotary);
		rotary_pushed.transfer_motion(that.rotary_pushed);
	}
};

struct ParamCache {
	Params p;
	MetaParams m;
	bool _new_data = true;

	void write_sync(Params &p_, MetaParams &m_)
	{
		_new_data = false; // protects against multiple write_syncs without a read_sync, and then one write_sync
						   // interupting a read_sync in progress
		Debug::Pin1::high();
		p.copy(p_);
		m.update_with(m_);
		_new_data = true;
		Debug::Pin1::low();
	}
	bool read_sync_params(Params *params)
	{
		if (!_new_data)
			return false;

		Debug::Pin2::high();

		if (!_new_data)
			return false;
		params->copy(p);
		Debug::Pin2::low();
		_new_data = false;
		return true;
	}
	bool read_sync_metaparams(MetaParams *metaparams)
	{
		if (!_new_data)
			return false;

		Debug::Pin2::high();

		if (!_new_data)
			return false;
		metaparams->transfer(m);
		Debug::Pin2::low();
		_new_data = false;
		return true;
	}
	void clear()
	{
		p.clear();
		m.clear();
	}

	bool load_new_patch = false;
	uint32_t new_patch_index;
};

// using ParamBlock = std::array<Params, StreamConf::Audio::BlockSize>;
struct ParamBlock {
	std::array<Params, StreamConf::Audio::BlockSize> params;
	MetaParams metaparams;
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
