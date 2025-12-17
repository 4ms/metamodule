#pragma once
#include "conf/neopixel_conf.hh"
#include "util/colors.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

struct LedStates {

	// Bit-field indexed by MousaiMix::ButtonMux0
	uint16_t leds0;

	// Bit-field indexed by MousaiMix::ButtonMux1
	uint16_t leds1;

	// Bit-field indexed by MousaiMix::ButtonMux2
	uint16_t leds2;

	// Neopixel lines
	std::array<Color, Neopixels::num_leds_a> neo_a{};
	std::array<Color, Neopixels::num_leds_b> neo_b{};
	std::array<Color, Neopixels::num_leds_vu> neo_vu{};
};

} // namespace MetaModule
