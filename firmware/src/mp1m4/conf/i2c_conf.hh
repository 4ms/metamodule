#pragma once
#include "drivers/i2c_config_struct.hh"

constexpr uint32_t LEDUpdateHz = 100;

// Runs at 417kHz on A7:
// At 520kHz on MP1-M4
const I2CConfig i2c_conf_controls = {
	.I2Cx = I2C1,
	.SCL = {GPIO::H, 11, 5},
	.SDA = {GPIO::H, 12, 5},
	.timing =
		{
			// MP1 M4: 400kHz:
			.PRESC = 0x00,
			.SCLDEL_SDADEL = 0x60,
			.SCLH = 0x11,
			.SCLL = 0x73,

		},
	.priority1 = 0,
	.priority2 = 1,
};
