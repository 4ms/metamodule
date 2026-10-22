#pragma once
#include "drivers/pin_change_conf.hh"

namespace MetaModule
{

// An interrupt on each audio frame, from the SAI's frame clock (LRCLK in codec_sai_conf.hh, which
// the MCU drives): the M33 runs the controls from it, as MP1's M4 does (core_m33/panel_controls.hh).
// Lower priority than the HSEM interrupt that starts each param block.
struct FrameRatePinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 11;
	static constexpr mdrivlib::GPIO port = mdrivlib::GPIO::E;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 1;
	static constexpr uint32_t priority2 = 0;
};

} // namespace MetaModule
