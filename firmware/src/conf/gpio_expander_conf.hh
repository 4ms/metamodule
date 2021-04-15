#pragma once
#include "drivers/gpio_expander.hh"

using namespace mdrivlib;

const GPIO_expander_conf gpio_expander_conf = {
	.addr = 0b0100000, // un-shifted address = 0x20 unshifted, 0x40/1 shifted
	.int_pin = {GPIO::D, 11, PinMode::Input},
	.IRQn = EXTI15_10_IRQn,
	.config = GPIO_expander_conf::AllInputs(),
};
