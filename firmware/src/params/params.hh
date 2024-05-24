#pragma once
#include "conf/panel_conf.hh"
#include "midi_params.hh"
#include "patch/midi_def.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
#include <array>

namespace MetaModule
{
struct Params {
	std::array<float, PanelDef::NumCVIn> cvjacks{};
	std::array<bool, PanelDef::NumGateIn> gate_ins{};
	std::array<Toggler, PanelDef::NumRgbButton> buttons{};
	std::array<float, PanelDef::NumPot> knobs{};

	Midi::Event midi_event{};

	uint32_t jack_senses{};

	Params() {
		clear();
	}

	void clear() {
		for (float &cvjack : cvjacks)
			cvjack = 0.f;
		for (auto &gate_in : gate_ins)
			gate_in = false;
		for (auto &button : buttons)
			button.reset();
		for (float &knob : knobs)
			knob = 0.f;

		midi_event = Midi::Event{};

		jack_senses = 0;
	}

	void copy(const Params &that) {
		for (unsigned i = 0; i < PanelDef::NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (unsigned i = 0; i < PanelDef::NumGateIn; i++)
			gate_ins[i] = that.gate_ins[i];
		for (unsigned i = 0; i < PanelDef::NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (unsigned i = 0; i < PanelDef::NumPot; i++)
			knobs[i] = that.knobs[i];

		midi_event = that.midi_event;

		jack_senses = that.jack_senses;
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
