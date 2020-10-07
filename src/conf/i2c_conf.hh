#pragma once
#include "i2c_config_struct.hh"

const I2CConfig i2c_conf = {
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 8, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
	.timing =
		{
			.PRESC = 8 * 2, // tPREC = 216MHz / 8 = 27MHz
			.SCLDEL_SDADEL = 0b00010001,
			.SCLH = 17, // 27MHz / (17+17) = 794kHz
			.SCLL = 17,
		},
};

