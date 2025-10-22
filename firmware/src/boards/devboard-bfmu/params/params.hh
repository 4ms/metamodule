#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include <array>

namespace MetaModule
{

struct Params {
	// TODO: make this the actual number of pots, not the mux size
	std::array<float, PanelDef::NumPot> knobs{};
	std::array<float, PanelDef::NumCVIn> cvs{};
	std::array<uint16_t, PanelDef::NumDACOut> dacs{};

	Midi::Event usb_midi_event{};  //6B
	Midi::Event uart_midi_event{}; //6B
	MidiMessage usb_raw_midi{};	   //3B
	MidiMessage uart_raw_midi{};   //3B

	uint8_t gate_ins{};	 //bit mask for 4 gate ins
	uint8_t clock_out{}; //clock out

	void clear() {
		for (auto &knob : knobs)
			knob = 0.f;

		for (auto &cv : cvs)
			cv = 0.f;

		for (auto &dac : dacs)
			dac = 0;

		usb_midi_event = Midi::Event{};
		usb_raw_midi = {};
		uart_midi_event = Midi::Event{};
		uart_raw_midi = {};

		gate_ins = 0;
		clock_out = 0;
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
