#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;

constexpr uint32_t LEDUpdateHz = 100;

const mdrivlib::I2CConfig i2c_conf_m4 = {

	.I2Cx = I2C3,
	.SCL = {GPIO::A, 8, GPIO_AF4_I2C3},
	.SDA = {GPIO::C, 9, GPIO_AF4_I2C3},
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
