#pragma once
#include "util/rgbled.hh"

// FIXME: MP1's knobset button LED is PWM'd from TIM1 (src/medium/button_led.hh). The pro's
// button LEDs are on LP5018 drivers over I2C (conf/led_driver_conf.hh). Until that's ported, the
// knobset button doesn't light up.

namespace MetaModule
{

struct NoLedPin {
	void set(bool) const {
	}
};

using ButtonLED = MixedRgbLed<NoLedPin, NoLedPin, NoLedPin>;

} // namespace MetaModule
