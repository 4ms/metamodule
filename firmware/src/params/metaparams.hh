#pragma once
#include "util/rotary_motion.hh"
#include <array>
#include <cmath>
#include <cstdint>

namespace MetaModule
{

// Block-rate parameters
struct MetaParams {

	// Indexed by MousaiMix::ButtonMux0
	uint16_t buttons0;
	// Indexed by MousaiMix::ButtonMux1
	uint16_t buttons1;
	// Indexed by MousaiMix::ButtonMux2
	uint16_t buttons2;

	// Encoders
	std::array<RotaryMotion, 2> encoder{};

	uint16_t haptic_out{}; //Haptic PWM value

	bool usb_midi_connected = false;

	uint32_t sample_rate = 48000;

	MetaParams() {
		clear();
	}

	void clear() {
		for (auto &enc : encoder) {
			enc.motion = 0;
			enc.abs_pos = 0;
		}
		haptic_out = 0;
		usb_midi_connected = false;
	}
};

} // namespace MetaModule
