#pragma once
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
};

} // namespace MetaModule
