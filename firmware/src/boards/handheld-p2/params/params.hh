#pragma once
#include "conf/panel_conf.hh"
#include "midi/midi_message.hh"
#include "midi_params.hh"
#include <array>

namespace MetaModule
{

struct Params {
	std::array<float, 3> accel{};

	Midi::Event usb_midi_event{}; //6B
	MidiMessage usb_raw_midi{};	  //3B

	void clear() {
		for (auto &a : accel)
			a = 0.f;

		usb_midi_event = Midi::Event{};
		usb_raw_midi = {};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
