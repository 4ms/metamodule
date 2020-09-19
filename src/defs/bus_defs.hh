#pragma once
#include "i2c.hh"
#include "pin.hh"

struct CodecI2C {
	static inline auto I2Cx = I2C2;
	const static inline auto SCL_port = GPIO::B;
	const static inline uint8_t SCL_pin = 10;
	const static inline auto SDA_port = GPIO::B;
	const static inline uint8_t SDA_pin = 11;
	const static inline auto GPIO_AF = GPIO_AF4_I2C2;
	const static inline I2CPeriph::i2cTimingReg I2C_TIMING = {
		.PRESC = 16 * 2, // tPREC = 216MHz / 16 = 13.5MHz
		.SCLDEL_SDADEL = 0b01000100,
		.SCLH = 0x57, // 13.5MHz / (87+87)  = 77kHz
		.SCLL = 0x57};
};

struct LEDDriverI2C {
	static inline auto I2Cx = I2C1;
	const static inline auto SCL_port = GPIO::B;
	const static inline uint8_t SCL_pin = 8;
	const static inline auto SDA_port = GPIO::B;
	const static inline uint8_t SDA_pin = 9;
	const static inline auto GPIO_AF = GPIO_AF4_I2C1;
	const static inline I2CPeriph::i2cTimingReg I2C_TIMING = {.PRESC = (1 << 4), // 27MHz
															  .SCLDEL_SDADEL = 0b00010001,
															  .SCLH = 17,
															  .SCLL = 17};
};

