#pragma once
#include "drivers/i2c_config_struct.hh"

const I2CConfig i2c_conf = {
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 6, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
	.timing =
		{
			.PRESC = 18 * 2, // tPREC = 480MHz / 18 = 26.7MHz
			.SCLDEL_SDADEL = 0b00010001,
			.SCLH = 17, // 26.7MHz / (17+17) = 784kHz
			.SCLL = 17,
		},
};

