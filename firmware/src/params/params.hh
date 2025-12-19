#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include <array>

namespace MetaModule
{

struct Params {

	std::array<float, PanelDef::NumPot> knobs{};
	std::array<float, PanelDef::NumCVIn> cvs{};

	uint16_t dac0{};
	uint16_t dac1{};

	MidiMessage usb_raw_midi{};	 //4B
	MidiMessage uart_raw_midi{}; //4B
	uint16_t gate_ins{};		 //bit mask for 4 gate ins
	uint16_t clock_out{};		 //clock out

	void clear() {
		*this = Params{};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
