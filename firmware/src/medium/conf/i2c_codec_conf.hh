#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;

constexpr uint32_t LEDUpdateHz = 100;

// I2C for main (internal) and aux (external/expander) codec, and internal and aux (ext/exp) GPIO Expander
const mdrivlib::I2CConfig i2c_codec_conf = {
	.I2Cx = I2C5,
	.SCL = {GPIO::A, 11, LL_GPIO_AF_4},
	.SDA = {GPIO::A, 12, LL_GPIO_AF_4},
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

// I2C for Aux header (not audio expander header)
const mdrivlib::I2CConfig aux_i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {GPIO::B, 10, LL_GPIO_AF_4},
	.SDA = {GPIO::B, 11, LL_GPIO_AF_4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x74,
		},
	.priority1 = 0,
	.priority2 = 1,
};

// I2C for usb-c chip
const mdrivlib::I2CConfig usb_i2c_conf = {
	.I2Cx = I2C6,
	.SCL = {GPIO::D, 1, mdrivlib::PinAF::AltFunc2},
	.SDA = {GPIO::D, 0, mdrivlib::PinAF::AltFunc2},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x74,
		},
	.priority1 = 2,
	.priority2 = 2,
};
