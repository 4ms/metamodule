#pragma once
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

// 10_000_000ns = 100Hz
constexpr uint32_t led_update_freq_Hz = 100;
constexpr uint32_t led_update_period_ns = 1000000000UL / led_update_freq_Hz;

// Todo: this isn't being used right now...?
const mdrivlib::TimekeeperConfig led_update_animation_task_conf = {
	.TIMx = TIM7,
	.period_ns = led_update_period_ns,
	.priority1 = 3,
	.priority2 = 3,
};

const uint32_t kNumLedDriverChips = 1;
