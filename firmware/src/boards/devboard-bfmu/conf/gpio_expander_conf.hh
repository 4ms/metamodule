#pragma once
#include "drivers/gpio_expander.hh"

namespace Mousai::ButtonLedExpander
{

using mdrivlib::GPIO_expander_conf;

// I2C TCA9555 Expanders
const mdrivlib::I2CConfig i2c_conf = {
	.I2Cx = I2C1,
	.SCL = {mdrivlib::GPIO::B, mdrivlib::PinNum::_8, mdrivlib::PinAF::AltFunc4},
	.SDA = {mdrivlib::GPIO::B, mdrivlib::PinNum::_7, mdrivlib::PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0x40,
			.SCLH = 0x0A,
			.SCLL = 0x1D,
		},
	.priority1 = 2,
	.priority2 = 1,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::_8,
};

constexpr mdrivlib::PinDef irq_pin{mdrivlib::GPIO::B, mdrivlib::PinNum::_2, mdrivlib::PinAF::AFNone};

constexpr uint8_t MaxAddresses = 8; // Number of addresses the chip supports

// Each of these represents a physical chip. Set the addresses used and whether each pin is input or output
// As just a guess, I set chips 1 2 and 3 to all inputs (buttons), and chips 4, 5, and 6 to outputs (LEDs)
constexpr GPIO_expander_conf gpio_chip_conf_1 = {
	.addr = 0b010'0000,
	.config = GPIO_expander_conf::AllInputs(),
};

constexpr GPIO_expander_conf gpio_chip_conf_2 = {
	.addr = 0b010'0001,
	.config = GPIO_expander_conf::AllInputs(),
};

constexpr GPIO_expander_conf gpio_chip_conf_3 = {
	.addr = 0b010'0010,
	.config = GPIO_expander_conf::AllInputs(),
};

constexpr GPIO_expander_conf gpio_chip_conf_4 = {
	.addr = 0b010'0011,
	.config = GPIO_expander_conf::AllOutputs(),
};

constexpr GPIO_expander_conf gpio_chip_conf_5 = {
	.addr = 0b010'0100,
	.config = GPIO_expander_conf::AllOutputs(),
};

constexpr GPIO_expander_conf gpio_chip_conf_6 = {
	.addr = 0b010'0101,
	.config = GPIO_expander_conf::AllOutputs(),
};

} // namespace Mousai::ButtonLedExpander
