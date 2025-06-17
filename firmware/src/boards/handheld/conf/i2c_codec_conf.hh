#pragma once
#include "drivers/i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

// I2C for main (internal) and aux (external/expander) codec, and internal and aux (ext/exp) GPIO Expander
const mdrivlib::I2CConfig a7m4_shared_i2c_codec_conf = {
	.I2Cx = I2C5,
	.SCL = {GPIO::A, PinNum::_11, PinAF::AltFunc4},
	.SDA = {GPIO::A, PinNum::_12, PinAF::AltFunc4},
	.timing =
		{
			// 0x40 77 68 74 (89MHz)
			// I2C Periph Clock = 104MHz
			// tI2CCLK = 1/104MHz = 9.6ns
			// tPRESC = 4+1 * 9.6ns = 48ns

			// SDADEL = 7 * 48ns = 336ns (SDA edge -> SCL rising edge)
			// SCLDEL = 7 * 48ns = 336ns (SCL falling edge -> SDA edge)
			// SCLH = 0x68+1 * 48ns = 5us
			// SCLL = 0x74+1 * 48ns = 5.6us

			// 0x40 FF 90 90 (69MHz)
			// SDADEL = 16 * 48ns = 768ns (SDA edge -> SCL rising edge)
			// SCLDEL = 16 * 48ns = 768ns (SCL falling edge -> SDA edge)
			// SCLH = 0x90+1 * 48ns = 6.9us
			// SCLL = 0x90+1 * 48ns = 6.9us

			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0xFF,
			.SCLH = 0x90,
			.SCLL = 0x90,
		},
	.priority1 = 2,
	.priority2 = 1,
};
