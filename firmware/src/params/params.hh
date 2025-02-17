#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include "util/debouncer.hh"
#include <array>

namespace MetaModule
{

struct Params {
	std::array<float, PanelDef::NumPot> knobs{};

	Midi::Event midi_event{};  //6B
	MidiMessage raw_msg{};	   //3B
	MidiMessage raw_msg_out{}; //3B
	uint8_t gate_ins{};
	Toggler button{};

	void clear() {
		gate_ins = 0;
		button.reset();

		for (float &knob : knobs)
			knob = 0.f;

		midi_event = Midi::Event{};
		raw_msg = {};
		raw_msg_out = {};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
