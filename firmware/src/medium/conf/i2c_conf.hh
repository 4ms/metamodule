#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;

// Runs at 400kHz on MP1-M4: 0x00601173
// Runs at 100kHz on MP1-M4: 0x10707DBC
const mdrivlib::I2CConfig i2c_conf_controls = {
	.I2Cx = I2C2,
	.SCL = {GPIO::F, 1, LL_GPIO_AF_4},
	.SDA = {GPIO::H, 5, LL_GPIO_AF_4},
	.timing =
		{
			.PRESC = 0x10,
			.SCLDEL_SDADEL = 0x70,
			.SCLH = 0x7D,
			.SCLL = 0xBC,

		},
	.priority1 = 0,
	.priority2 = 1,
};
