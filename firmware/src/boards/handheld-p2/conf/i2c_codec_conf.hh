#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

const mdrivlib::I2CConfig a7m4_shared_i2c_conf = {
	.I2Cx = I2C6,
	.SCL = {GPIO::A, PinNum::_11, PinAF::AltFunc2},
	.SDA = {GPIO::A, PinNum::_12, PinAF::AltFunc2},
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
