#pragma once
#include "defs/bus_defs.hh"

// Todo: Rename file drivers/i2c_config_struct.hh
// Model it after SaiDef
class CodecBus {
public:
	static inline I2CPeriph i2c;

	CodecBus()
	{
		Pin sda{CodecI2C::SDA_port, CodecI2C::SDA_pin,	 PinMode::Alt,	 CodecI2C::GPIO_AF,
				PinPull::Up,		PinPolarity::Normal, PinSpeed::High, PinOType::OpenDrain};
		Pin scl{CodecI2C::SCL_port, CodecI2C::SCL_pin,	 PinMode::Alt,	 CodecI2C::GPIO_AF,
				PinPull::Up,		PinPolarity::Normal, PinSpeed::High, PinOType::OpenDrain};

		i2c.init(CodecI2C::I2Cx, CodecI2C::I2C_TIMING);
	}
};

class LEDDriverBus {
public:
	static inline I2CPeriph i2c;

	LEDDriverBus()
	{
		Pin sda{LEDDriverI2C::SDA_port, LEDDriverI2C::SDA_pin, PinMode::Alt,
				LEDDriverI2C::GPIO_AF,	PinPull::Up,		   PinPolarity::Normal,
				PinSpeed::High,			PinOType::OpenDrain};
		Pin scl{LEDDriverI2C::SCL_port, LEDDriverI2C::SCL_pin, PinMode::Alt,
				LEDDriverI2C::GPIO_AF,	PinPull::Up,		   PinPolarity::Normal,
				PinSpeed::High,			PinOType::OpenDrain};

		i2c.init(LEDDriverI2C::I2Cx, LEDDriverI2C::I2C_TIMING);
	}
};
