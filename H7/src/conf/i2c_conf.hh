#pragma once
#include "drivers/i2c_config_struct.hh"

const I2CConfig i2c_conf = {
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 6, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
	.timing =
		{
			// 0x60 -> 400kHz: 120MHz / (6+2) = 15MHz I2CperiphClock
			// 0x20 -> 800kHz: 120MHz / (2+2) = 30MHz I2CperiphClock
			// I2C clock = I2CPeriphClock / (SCLDEL + SDADEL + SCLH+1 + SCLL+1)
			// 30MHz / (1 + 1 + 17+1 + 17+1) = 789kHz
			.PRESC = 0x20,
			.SCLDEL_SDADEL = 0b00010001,
			.SCLH = 17,
			.SCLL = 17,
		},
};

