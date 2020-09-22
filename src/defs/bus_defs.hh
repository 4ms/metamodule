#pragma once
#include "i2c.hh"
#include "pin.hh"

struct SharedI2C {
	static inline auto I2Cx = I2C1;
	const static inline auto SCL_port = GPIO::B;
	const static inline uint8_t SCL_pin = 8;
	const static inline auto SDA_port = GPIO::B;
	const static inline uint8_t SDA_pin = 7;
	const static inline auto GPIO_AF = GPIO_AF4_I2C1;
	const static inline I2CPeriph::i2cTimingReg I2C_TIMING = {
		.PRESC = 8 * 2, //tPREC = 216MHz / 8 = 27MHz
		.SCLDEL_SDADEL = 0b00010001,
		.SCLH = 17, //27MHz / (17+17) = 794kHz
		.SCLL = 17};
};

