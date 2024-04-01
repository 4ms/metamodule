#pragma once
#include "util/rgbled.hh"

namespace MetaModule
{

struct NoPin {
	void set(bool) const {
	}
};
using green_LED = NoPin;
using blue_LED = NoPin;
using red_LED = NoPin;

using ButtonLED = MixedRgbLed<red_LED, green_LED, blue_LED>;

} // namespace MetaModule
