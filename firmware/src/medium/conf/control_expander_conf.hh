#pragma once
#include "drivers/gpio_expander.hh"

namespace MetaModule::ControlExpander
{

// I2C for Aux header (not audio expander header)
const mdrivlib::I2CConfig i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {mdrivlib::GPIO::B, mdrivlib::PinNum::_10, mdrivlib::PinAF::AltFunc4},
	.SDA = {mdrivlib::GPIO::B, mdrivlib::PinNum::_11, mdrivlib::PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x74,
		},
	.priority1 = 2,
	.priority2 = 1,
};

constexpr mdrivlib::GPIO_expander_conf gpio_chip_conf = {
	.addr = 0b010'0000, // base address. Actual address(es) will be detected at runtime
	.config = mdrivlib::GPIO_expander_conf::Config({
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Input,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
		mdrivlib::GPIO_expander_conf::Output,
	}),
};

static constexpr unsigned NumTotalButtons = sizeof(uint32_t) * 8; //because state is stored in uint32_t
static constexpr unsigned NumButtonsPerExpander = 8;			  //as defined by hardware
static constexpr unsigned MaxExpanders = 32 / NumButtonsPerExpander;

// Given a bitmask where each bit represents an output pin's state,
// calculate the data packet to send to the GPIO chip to achieve these states.
inline uint32_t calc_output_data(uint8_t bitmask) {
	//Input: 0000 0000 0000 0000 0000 0000 8765 4321 =>
	//Output:    0000 0000 0000 0000 1234 8765 0000 0000

	//         0000 0000 0000 0000 1234 0000 0000 0000
	uint32_t bottom = __RBIT(bitmask & 0x0F) >> 16;

	//         0000 0000 0000 0000 0000 0000 8765 4321 =>
	//         0000 0000 0000 0000 0000 0000 8765 0000 (after & 0xF0)
	//         0000 0000 0000 0000 0000 8765 0000 0000 (after << 4)
	uint32_t top = (bitmask & 0xF0) << 4;

	return (top | bottom);
}

} // namespace MetaModule::ControlExpander
