#pragma once
#include "drivers/gpio_expander.hh"

namespace ListenClosely
{

using mdrivlib::GPIO_expander_conf;

constexpr mdrivlib::PinDef irq_pin{mdrivlib::GPIO::G, mdrivlib::PinNum::_9, mdrivlib::PinAF::AFNone};

// Note: Pins set to "Output" are unused on this module
constexpr GPIO_expander_conf gpio_expander_conf = {
	.addr = 0b010'0000,
	.config = GPIO_expander_conf::Config({
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Input,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

} // namespace ListenClosely
