#pragma once
#include "conf/panel_conf.hh"
#include "conf/stream_conf.hh"
#include "util/analyzed_signal.hh"
#include "util/colors.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
#include <array>

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
	std::array<float, PanelDef::NumCVIn> cvjacks{};
	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};
	std::array<Toggler, PanelDef::NumRgbButton> buttons{};
	std::array<float, PanelDef::NumPot> knobs{};
	//Note 0 => -1.0 => should become -5V or -5oct on modules
	//Note 60 => 0
	//Note 120 => 1.0 => should become 5V or +5oct on modules
	//Note 121-127.. => ..?1.0?
	//monophonic -1..1 => notes 0..127 => C-2..G8 => 4.0875Hz..6271.93Hz => -2V..~8.5V
	float midi_note;
	bool midi_gate; //monophonic on/off
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
		for (unsigned i = 0; i < PanelDef::NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (unsigned i = 0; i < PanelDef::NumGateIn; i++)
			gate_ins[i].copy_state(that.gate_ins[i]);
		for (unsigned i = 0; i < PanelDef::NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (unsigned i = 0; i < PanelDef::NumPot; i++)
			knobs[i] = that.knobs[i];
		jack_senses = that.jack_senses;
	}
};

constexpr inline auto sizeof_Toggler = sizeof(Toggler);
constexpr inline auto sizeof_Params = sizeof(Params);

struct MetaParams {
	float patchcv = 0.f;
	Toggler rotary_button;
	RotaryMotion rotary;
	RotaryMotion rotary_pushed;
	std::array<Toggler, PanelDef::NumMetaRgbButton> meta_buttons{};
	std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> ins;
	bool midi_connected = false;

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

struct ParamBlock {
	std::array<Params, StreamConf::Audio::BlockSize> params;
	MetaParams metaparams;
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
