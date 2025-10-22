#pragma once
#include "drivers/gpio_expander.hh"

namespace MetaModule::GPIOExpander
{
using mdrivlib::GPIO_expander_conf;

struct GpioBit {
	uint16_t chip_num;
	uint16_t pin_num;
};

constexpr inline auto buttons = std::array{
	GpioBit{0, 0},
};

// Given a button number, return which chip and bit it refers to
constexpr inline GpioBit find_button(unsigned button_id) {
	// buttons 0-7 => chip 0, pins 0-7
	// buttons 8-15 => chip 1, pins 0-7
	// buttons 16-23 => chip 2, pins 0-7
	// buttons 24-31 => chip 3, pins 0-7

	return {(uint16_t)(button_id / 8), (uint16_t)(button_id % 8)};
}

// Given a light number, return which chip and bit it refers to
constexpr inline GpioBit find_light(unsigned light_id) {
	// buttons 0-7 => chip 0, pins 8-15
	// buttons 8-15 => chip 1, pins 8-15
	// buttons 16-23 => chip 2, pins 8-15
	// buttons 24-31 => chip 3, pins 8-15

	return {(uint16_t)(light_id / 8), (uint16_t)((light_id % 8) + 8)};
}

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
constexpr uint8_t MaxAddresses = 8; // Number of addresses the chip supports

// Each of these represents a physical chip. Set the addresses used and whether each pin is input or output
// As just a guess, I set chips 1 2 and 3 to all inputs (buttons), and chips 4, 5, and 6 to outputs (LEDs)
constexpr GPIO_expander_conf gpio_chip_conf_1 = {
	.addr = 0b010'0000,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

constexpr GPIO_expander_conf gpio_chip_conf_2 = {
	.addr = 0b010'0001,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

constexpr GPIO_expander_conf gpio_chip_conf_3 = {
	.addr = 0b010'0010,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

constexpr GPIO_expander_conf gpio_chip_conf_4 = {
	.addr = 0b010'0011,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

constexpr GPIO_expander_conf gpio_chip_conf_5 = {
	.addr = 0b010'0100,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

constexpr GPIO_expander_conf gpio_chip_conf_6 = {
	.addr = 0b010'0101,
	.config = GPIO_expander_conf::Config({
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
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
		GPIO_expander_conf::Output,
	}),
};

} // namespace MetaModule::GPIOExpander
