#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include "util/debouncer_compact.hh"
#include <array>

namespace MetaModule
{

struct Params {
	std::array<float, PanelDef::NumPot> knobs{};

	MidiMessage raw_msg{};	  //4B
	Midi::Event midi_event{}; //6B
	uint8_t gate_ins{};
	TogglerCompact button{};

	void clear() {
		gate_ins = 0;
		button.reset();

		for (float &knob : knobs)
			knob = 0.f;

		midi_event = Midi::Event{};
		raw_msg = {};
	}
};

// 60B
static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
