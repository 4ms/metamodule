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
} // namespace MetaModule
