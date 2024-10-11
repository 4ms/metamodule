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

} // namespace MetaModule::ControlExpander
