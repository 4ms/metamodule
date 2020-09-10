#pragma once
#include "i2c.hh"
#include "pin.hh"

struct SharedI2C {
	static inline auto I2Cx = I2C1;
	const static inline auto GPIO = GPIO::B;
	const static inline uint8_t SCL_PIN = 8;
	const static inline uint8_t SDA_PIN = 7;
	const static inline auto GPIO_AF = GPIO_AF4_I2C1;
	const static inline i2cPeriph::i2cTimingReg I2C_TIMING = {
		.PRESC = 8 * 2, //tPREC = 216MHz / 8 = 27MHz
		.SCLDEL_SDADEL = 0b00010001,
		.SCLH = 17, //27MHz / (17+17) = 794kHz
		.SCLL = 17 
	};
};

