#pragma once
#include "conf/panel_conf.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNoInit;

const mdrivlib::TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 20000, // must be just a hair faster than 48kHz
	.priority1 = 2,		// same group as global Semaphore unlock, so that
	.priority2 = 3,
};

struct MMControlPins {
	static constexpr PinNoInit rotA{GPIO::A, 15};
	static constexpr PinNoInit rotB{GPIO::C, 7};
	static constexpr PinNoInit rotS{GPIO::B, 14};

	static constexpr PinNoInit but0{GPIO::I, 2};

	static constexpr PinNoInit gate_in_1{GPIO::I, 3};
	static constexpr PinNoInit gate_in_2{GPIO::H, 9};
};

struct MultiGPIOReader {
	//
};

} // namespace MetaModule
