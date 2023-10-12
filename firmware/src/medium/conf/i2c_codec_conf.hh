#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

// I2C for main (internal) and aux (external/expander) codec, and internal and aux (ext/exp) GPIO Expander
const mdrivlib::I2CConfig a7m4_shared_i2c_codec_conf = {
	.I2Cx = I2C5,
	.SCL = {GPIO::A, PinNum::_11, PinAF::AltFunc4},
	.SDA = {GPIO::A, PinNum::_12, PinAF::AltFunc4},
	.timing = //0x40505874. was 00901945
	{
		.PRESC = 0x40,
		.SCLDEL_SDADEL = 0x50,
		.SCLH = 0x58,
		.SCLL = 0x74,
	},
	.priority1 = 2,
	.priority2 = 1,
};

// I2C for Aux header (not audio expander header)
const mdrivlib::I2CConfig aux_i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {GPIO::B, PinNum::_10, PinAF::AltFunc4},
	.SDA = {GPIO::B, PinNum::_11, PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x74,
		},
	.priority1 = 1,
	.priority2 = 2,
};
