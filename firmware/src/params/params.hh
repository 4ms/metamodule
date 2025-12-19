#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include <array>

namespace MetaModule
{

struct Params {
	std::array<float, PanelDef::NumPot> knobs{};

	std::array<float, PanelDef::NumCVIn> cvs{};

	uint16_t dac0{};
	uint16_t dac1{};

	Midi::Event usb_midi_event{};  //6B
	Midi::Event uart_midi_event{}; //6B

	MidiMessage usb_raw_midi{}; //3B
	uint8_t gate_ins{};			//bit mask for 4 gate ins

	MidiMessage uart_raw_midi{}; //3B
	uint8_t clock_out{};		 //clock out

	void clear() {
		*this = Params{};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
