#pragma once
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

		// for (auto &rot : rotary_motion)
		// 	rot = 0;

		// buttons = 0;

		usb_midi_event = Midi::Event{};
		usb_raw_midi = {};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
