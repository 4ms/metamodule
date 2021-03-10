#pragma once
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 20833, // 48kHz
	.priority1 = 0,
	.priority2 = 3,
};
