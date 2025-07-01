#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

// I2C for codec -- PC9 is shared with SDMMC!!!
const mdrivlib::I2CConfig a7m4_shared_i2c_conf = {
	.I2Cx = I2C3,
	.SCL = {GPIO::A, PinNum::_8, PinAF::AltFunc4},
	.SDA = {GPIO::C, PinNum::_9, PinAF::AltFunc4},
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

// Disabled
const mdrivlib::I2CConfig battery_guage_conf = {.I2Cx = nullptr};
