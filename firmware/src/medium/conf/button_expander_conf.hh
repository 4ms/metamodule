#pragma once
#include "drivers/gpio_expander.hh"

namespace MetaModule::ButtonExpander
{

// I2C for Aux header (not audio expander header)
const mdrivlib::I2CConfig i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {mdrivlib::GPIO::B, mdrivlib::PinNum::_10, mdrivlib::PinAF::AltFunc4},
	.SDA = {mdrivlib::GPIO::B, mdrivlib::PinNum::_11, mdrivlib::PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x10,
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x74,
		},
	.priority1 = 2,
	.priority2 = 1,
};

constexpr mdrivlib::GPIO_expander_conf gpio_chip_conf = {
	.addr = 0b010'0000, // base address. Actaully address(es) will be detected at runtime
	.config = mdrivlib::GPIO_expander_conf::Config({
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
	}),
};

inline uint32_t order_buttons(uint32_t raw_reading) {

	// bits 4-7 map directly to bits 4-7:
	uint32_t buttons = raw_reading & 0x00F0;

	// bits 8-11 flip and map to bits 0-3: (8->3, 9->2, 10->1, 11->0)
	// RBIT: sends bit 11 to 20; bit 10 to 21; bit 9 to 22; bit 8 to 23
	buttons |= (__RBIT(raw_reading) >> 20) & 0x000F;

	return buttons;
}

} // namespace MetaModule::ButtonExpander
