#pragma once

#include "drivers/i2c_config_struct.hh"

namespace MetaModule::Expander
{
// I2C for Aux header (not audio expander header)
const mdrivlib::I2CConfig i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {mdrivlib::GPIO::B, mdrivlib::PinNum::_10, mdrivlib::PinAF::AltFunc4},
	.SDA = {mdrivlib::GPIO::B, mdrivlib::PinNum::_11, mdrivlib::PinAF::AltFunc4},
	.timing =
		{
			// .PRESC = 0x00,
			// .SCLDEL_SDADEL = 0x71,
			// .SCLH = 0x40,
			// .SCLL = 0x80,
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

} // namespace MetaModule::Expander
