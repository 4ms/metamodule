#pragma once
#include "conf/panel_conf.hh"
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
	static constexpr PinNoInit rotA{GPIO::G, 12};
	static constexpr PinNoInit rotB{GPIO::G, 13};
	static constexpr PinNoInit rotS{GPIO::A, 3};

	static constexpr PinNoInit but0{GPIO::F, 11};
	static constexpr PinNoInit but1{GPIO::C, 3};

	static constexpr PinNoInit clkin{GPIO::A, 14};
	static constexpr PinNoInit gate1{GPIO::F, 5};
	static constexpr PinNoInit gate2{GPIO::D, 10};
};

} // namespace MetaModule
