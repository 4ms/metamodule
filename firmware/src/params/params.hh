#pragma once
#include "conf/panel_conf.hh"
#include "util/debouncer.hh"
#include <array>

namespace MetaModule
{
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

} // namespace MetaModule
