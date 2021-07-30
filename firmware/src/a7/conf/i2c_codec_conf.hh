#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;

constexpr uint32_t LEDUpdateHz = 100;

// Runs at 417kHz on A7:
const mdrivlib::I2CConfig i2c_conf_codec = {
	.I2Cx = I2C1,
	.SCL = {GPIO::H, 11, 5},
	.SDA = {GPIO::H, 12, 5},
	.timing = //0x40505874. was 00901945
	{
		.PRESC = 0x40,
		.SCLDEL_SDADEL = 0x50,
		.SCLH = 0x58,
		.SCLL = 0x74,
	},
	.priority1 = 0,
	.priority2 = 1,
};

