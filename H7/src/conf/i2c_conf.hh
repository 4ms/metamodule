#pragma once
#include "drivers/i2c_config_struct.hh"
#include "local_board_rev.hh"

constexpr uint32_t LEDUpdateHz = 100;

const I2CConfig i2c_conf_m4 = {

#ifdef USING_DUAL_I2C_BUS_ON_HACKED_PCB
	.I2Cx = I2C3,
	.SCL = {GPIO::A, 8, GPIO_AF4_I2C3},
	.SDA = {GPIO::C, 9, GPIO_AF4_I2C3},
#else
	.I2Cx = I2C1,
	.SCL = {GPIO::B, 6, GPIO_AF4_I2C1},
	.SDA = {GPIO::B, 7, GPIO_AF4_I2C1},
#endif

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

// I2C clock = I2CPeriphClock / (SCLDEL + SDADEL + SCLH+1 + SCLL+1)
// I2CPeriphClock = ClockSource / (PRESC>>4 + 2)

// SCL Period = tSCL = tSYNC1 + tSYNC2 + ( (SCLH+1 + SCLL+1) * (PRESC>>4 + 1) * tClockSource) )
// tSYNC1 = (SDADEL * (PRESC>>4 + 1) + 1) * tClockSource
// tSYNC2 = (SCLDEL * (PRESC>>4 + 1) + 1) * tClockSource

// stable with M7:
// SCL Freq = 1/tSCL = fClockSource / (PRESC>>4 + 1) / (SCLL + SCLH + 2) .... - some more for tSNC1
// 0x60 -> 400kHz: 120MHz / (6+2) = 15MHz I2CperiphClock
// 15MHz / (1 + 1 + 17+1 + 17+1) = 394kHz
// .PRESC = 0x10,
// .SCLDEL_SDADEL = 0b00110011,
// .SCLH = 28,
// .SCLL = 28,
