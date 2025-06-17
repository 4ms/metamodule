#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

// I2C for internal GPIO Expander
const mdrivlib::I2CConfig a7m4_shared_i2c_conf = {
	.I2Cx = I2C5,
	.SCL = {GPIO::A, PinNum::_11, PinAF::AltFunc4},
	.SDA = {GPIO::A, PinNum::_12, PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0xFF,
			.SCLH = 0x90,
			.SCLL = 0x90,
		},
	.priority1 = 2,
	.priority2 = 1,
};

// I2C for internal codec
const mdrivlib::I2CConfig battery_guage_conf = {
	.I2Cx = I2C2,
	.SCL = {GPIO::B, PinNum::_10, PinAF::AltFunc4},
	.SDA = {GPIO::B, PinNum::_11, PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0xFF,
			.SCLH = 0x90,
			.SCLL = 0x90,
		},
	.priority1 = 2,
	.priority2 = 1,
};
