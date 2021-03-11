#pragma once
#include "drivers/i2c_config_struct.hh"

constexpr uint32_t LEDUpdateHz = 100;

const I2CConfig i2c_conf = {
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 6, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
	.timing =
		{
			// I2C clock = I2CPeriphClock / (SCLDEL + SDADEL + SCLH+1 + SCLL+1)
			// I2CPeriphClock = ClockSource / (PRESC>>4 + 2)

			// SCL Period = tSCL = tSYNC1 + tSYNC2 + ( (SCLH+1 + SCLL+1) * (PRESC>>4 + 1) * tClockSource) )
			// tSYNC1 = (SDADEL * (PRESC>>4 + 1) + 1) * tClockSource
			// tSYNC2 = (SCLDEL * (PRESC>>4 + 1) + 1) * tClockSource

			// stable with M7:
			// SCL Freq = 1/tSCL = fClockSource / (PRESC>>4 + 1) / (SCLL + SCLH + 2) .... - some more for tSNC1
			// 0x60 -> 400kHz: 120MHz / (6+2) = 15MHz I2CperiphClock
			// 15MHz / (1 + 1 + 17+1 + 17+1) = 394kHz
			// .PRESC = 0xF0,
			// .SCLDEL_SDADEL = 0b00110011,
			// .SCLH = 28, // 17,
			// .SCLL = 28, // 17,

			.PRESC = 0x10,
			.SCLDEL_SDADEL = 0b00110011,
			.SCLH = 28, // 17,
			.SCLL = 28, // 17,

			// 0x20 -> 800kHz: 120MHz / (2+2) = 30MHz I2CperiphClock
			// 30MHz / (1 + 1 + 17+1 + 17+1) = 789kHz

			// with 98.3MHz clock source, these give 101.5kHz
			// .PRESC = 0xF0,
			// .SCLDEL_SDADEL = 0b00110011,
			// .SCLH = 28, // 17,
			// .SCLL = 28, // 17,

			// 64MHz ClockSource ===> 100kHz
			// .PRESC = 0xA0,
			// .SCLDEL_SDADEL = 0b00010000,
			// .SCLH = 0x16,
			// .SCLL = 0x21,
		},
	.priority1 = 0,
	.priority2 = 1,
};

