#pragma once
#include "drivers/pin.hh"
#include "drivers/pin_change_conf.hh"

namespace ListenClosely
{

// Must be set to the LRCLK pin of the codec
// this pin drives the reading of audio-rate gate input pins
struct FrameRatePinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 12;
	static constexpr mdrivlib::GPIO port = mdrivlib::GPIO::D;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 3;
};

} // namespace ListenClosely
