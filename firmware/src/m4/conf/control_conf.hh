#pragma once
#include "conf/panel_conf.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

namespace MetaModule
{
const mdrivlib::TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 20800, // must be just a hair faster than 48kHz
	.priority1 = 0,
	.priority2 = 3,
};

struct MMControlPins {
	static constexpr PinNoInit rotA{GPIO::C, 7};
	static constexpr PinNoInit rotB{GPIO::C, 8};
	static constexpr PinNoInit rotS{GPIO::C, 6};

	static constexpr PinNoInit but0{GPIO::C, 10};
	static constexpr PinNoInit but1{GPIO::C, 11};

	static constexpr PinNoInit clkin{GPIO::D, 12};
	static constexpr PinNoInit gate1{GPIO::G, 6};
	static constexpr PinNoInit gate2{GPIO::G, 7};
};

} // namespace MetaModule
