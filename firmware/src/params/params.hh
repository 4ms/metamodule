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

	// Which port raw_msg is tied to (same values as Midi::Event::Port)
	uint8_t midi_port : 4 {};

	// Bits 0 and 1 are GateIn1 and GateIn2
	uint8_t gate_ins : 4 {};

	TogglerCompact button{};

	void clear() {
		gate_ins = 0;
		button.reset();

		for (float &knob : knobs)
			knob = 0.f;

		midi_event = Midi::Event{};
		raw_msg = {};
		midi_port = 0;
	}
};

// 60B -- copied every audio block, so keep it that way
static constexpr auto Params_Size = sizeof(Params);
static_assert(Params_Size == PanelDef::NumPot * sizeof(float) + 12, "Params grew: check the audio block copy cost");

} // namespace MetaModule
