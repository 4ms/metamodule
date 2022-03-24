#pragma once
#include "conf/panel_conf.hh"
#include "conf/stream_conf.hh"
#include "util/analyzed_signal.hh"
#include "util/colors.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
#include <array>
#include <string>

namespace MetaModule
{
struct RotaryMotion {
	int32_t abs_pos = 0;
	int32_t motion = 0;

	int32_t use_motion() {
		auto tmp = motion;
		motion = 0;
		return tmp;
	}
	void add_motion(const RotaryMotion &that) {
		motion += that.motion;
		abs_pos += that.motion;
	}
	void transfer_motion(RotaryMotion &that) {
		auto that_motion = that.use_motion();
		motion += that_motion;
		abs_pos += that_motion;
	}
};

struct Params {
	std::array<float, NumCVIn> cvjacks{};
	std::array<Toggler, NumGateIn> gate_ins{};
	std::array<Toggler, NumRgbButton> buttons{};
	std::array<float, NumPot> knobs{};
	uint32_t jack_senses;

	Params() {
		clear();
	}

	void clear() {
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

	void copy(const Params &that) {
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
	std::array<Toggler, NumMetaRgbButton> meta_buttons{};
	std::array<AnalyzedSignal<1000>, NumAudioIn> ins;

	uint8_t audio_load = 0;

	MetaParams() {
		clear();
	}

	void clear() {
		patchcv = 0.f;
		for (auto &but : meta_buttons)
			but.reset();
		rotary_button.reset();
		rotary.motion = 0;
		rotary.abs_pos = 0;
		rotary_pushed.motion = 0;
		rotary_pushed.abs_pos = 0;
		audio_load = 0;
		for (auto &in : ins)
			in.reset_to(0);
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		patchcv = that.patchcv;
		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);
		rotary_button.transfer_events(that.rotary_button);
		rotary.add_motion(that.rotary);
		rotary_pushed.add_motion(that.rotary_pushed);
		audio_load = that.audio_load;
		for (auto [in, thatin] : zip(ins, that.ins)) {
			in.min = thatin.min;
			in.max = thatin.max;
			in.avg = thatin.avg;
			in.iir = thatin.iir;
			thatin.reset_to(thatin.iir);
		}
	}

	// TODO: check if this is used, then remove it if it's not
	void copy(const MetaParams &that) {
		patchcv = that.patchcv;
		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.copy_state(thatbut);
		rotary_button.copy_state(that.rotary_button);
		rotary = that.rotary;
		rotary_pushed = that.rotary_pushed;
		audio_load = that.audio_load;
	}

	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Moves rotary motion events from `that` to `this` (removing them from `that`, and adding them to existing events
	// in `this`
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		patchcv = that.patchcv;
		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);
		rotary_button.transfer_events(that.rotary_button);
		rotary.transfer_motion(that.rotary);
		rotary_pushed.transfer_motion(that.rotary_pushed);
		audio_load = that.audio_load;
		for (auto [in, thatin] : zip(ins, that.ins)) {
			in.min = thatin.min;
			in.max = thatin.max;
			in.avg = thatin.avg;
			in.iir = thatin.iir;
			thatin.reset_to(thatin.iir);
		}
	}
};

// ParamCache class
// Stores a copy of Params and MetaParams and allows access from single core
// where a higher-priority ISR does write_sync(), and a lower-priority ISR does read_sync()
// The users of this class should each have their own copy of Params and MetaParams.
//
// Todo: use HSEM to allow for multiple cores and inverted ISR priorities
struct ParamQueue {
	Params p;
	MetaParams m;

	ParamQueue() {
		clear();
	}

	void write_sync(Params &p_, MetaParams &m_) {
		//FIXME: Use an atomic (STREX and LDREX) for new_data to prevent data race

		_new_data = false; // protects against multiple write_syncs without a read_sync, and then one write_sync
						   // interupting a read_sync in progress
		p.copy(p_);
		m.update_with(m_);
		_new_data = true;
	}

	bool read_sync(Params *params, MetaParams *metaparams) {
		if (!_new_data)
			return false;
		if (!_new_data)
			return false;
		params->copy(p);
		metaparams->transfer(m);
		_new_data = false;
		return true;
	}

	void clear() {
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
	bool patchlist_updated = false;
	std::string message{""};

	void set_message(const std::string_view m) {
		message = m;
	}

	void clear_message() {
		message = "";
	}

	[[nodiscard]] std::string_view get_message() const {
		return message;
	}

	void append_message(const std::string_view m) {
		message.append(m);
	}
};

} // namespace MetaModule
