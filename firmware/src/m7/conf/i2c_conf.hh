#pragma once
#include "drivers/i2c_config_struct.hh"

constexpr uint32_t LEDUpdateHz = 100;

const I2CConfig i2c_conf_m7 = {
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 6, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
	.timing =
		{
			.PRESC = 0x00,
			.SCLDEL_SDADEL = 0x90,
			.SCLH = 0x19,
			.SCLL = 0x45,
		},
	.priority1 = 0,
	.priority2 = 1,
};
