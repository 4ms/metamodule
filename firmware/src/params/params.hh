#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include "patch/midi_def.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
#include <array>

namespace MetaModule
{

struct Params {
	std::array<float, PanelDef::NumPot> knobs{};

	Midi::Event midi_event{}; //6B
	MidiMessage raw_msg{};	  //3B
	uint8_t gate_ins{};
	Toggler button;

	Params() {
		clear();
	}

	void clear() {
		gate_ins = 0;
		button.reset();
		for (float &knob : knobs)
			knob = 0.f;

		midi_event = Midi::Event{};
	}

	void copy(const Params &that) {
		gate_ins = that.gate_ins;

		button.copy_state(that.button);

		for (unsigned i = 0; i < PanelDef::NumPot; i++)
			knobs[i] = that.knobs[i];

		midi_event = that.midi_event;
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
