#pragma once
#include "conf/panel_conf.hh"
#include "conf/stream_conf.hh"
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
	std::array<float, NumCVIn> cvjacks{};
	std::array<Toggler, NumGateIn> gate_ins{};
	std::array<Toggler, 2> buttons{};

	// Same value for an entire block:
	std::array<float, NumPot> knobs{};
	uint16_t jack_senses;

	Params()
	{
		clear();
	}

	void clear()
	{
		for (float &cvjack : cvjacks)
			cvjack = 0.f;
		for (auto &gate_in : gate_ins)
			gate_in.reset();
		for (auto &button : buttons)
			button.reset();
		for (float &knob : knobs)
			knob = 0.f;
		jack_senses = 0;
	}

	void copy(const Params &that)
	{
		for (unsigned i = 0; i < NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (unsigned i = 0; i < NumGateIn; i++)
			gate_ins[i].copy_state(that.gate_ins[i]);
		for (unsigned i = 0; i < NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (unsigned i = 0; i < NumPot; i++)
			knobs[i] = that.knobs[i];
		jack_senses = that.jack_senses;
	}
};

struct MetaParams {
	float patchcv = 0.f;
	Toggler rotary_button;
	RotaryMotion rotary;
	RotaryMotion rotary_pushed;
	uint8_t audio_load = 0;

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
		audio_load = 0;
	}

	// Copies some data, adds other data (rotary motion)
	void update_with(const MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary.add_motion(that.rotary);
		rotary_pushed.add_motion(that.rotary_pushed);
		audio_load = that.audio_load;
	}
	void copy(const MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary = that.rotary;
		rotary_pushed = that.rotary_pushed;
		audio_load = that.audio_load;
	}
	void transfer(MetaParams &that)
	{
		patchcv = that.patchcv;
		rotary_button.copy_state(that.rotary_button);
		rotary.transfer_motion(that.rotary);
		rotary_pushed.transfer_motion(that.rotary_pushed);
		audio_load = that.audio_load;
	}
};

// ParamCache class
// Stores a copy of Params and MetaParams and allows access from single core
// where a higher-priority ISR does write_sync(), and a lower-priority ISR does read_sync()
// The users of this class should each have their own copy of Params and MetaParams.
//
// Todo: use HSEM to allow for multiple cores and inverted ISR priorities
// Todo: "cache" isn't the best name for this, think of something better...
struct ParamCache {
	Params p;
	MetaParams m;

	ParamCache()
	{
		clear();
	}
	void write_sync(Params &p_, MetaParams &m_)
	{
		_new_data = false; // protects against multiple write_syncs without a read_sync, and then one write_sync
						   // interupting a read_sync in progress
		p.copy(p_);
		m.update_with(m_);
		_new_data = true;
	}

	bool read_sync(Params *params, MetaParams *metaparams)
	{
		if (!_new_data)
			return false;
		if (!_new_data)
			return false;
		params->copy(p);
		metaparams->transfer(m);
		_new_data = false;
		return true;
	}

	void clear()
	{
		_new_data = false;
		p.clear();
		m.clear();
		_new_data = true;
	}

private:
	volatile bool _new_data = true;
};

struct ParamBlock {
	std::array<Params, StreamConf::Audio::BlockSize> params;
	MetaParams metaparams;
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

struct UiAudioMailbox {
	bool loading_new_patch = true;
	bool audio_is_muted = true;
	uint32_t new_patch_index;
};

} // namespace MetaModule
