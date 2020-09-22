#pragma once
#include "defs/bus_defs.hh"

class SharedBus {
public:
	static inline I2CPeriph i2c;

	SharedBus()
	{
		Pin sda{
			SharedI2C::SDA_port,
			SharedI2C::SDA_pin,
			PinMode::Alt,
			SharedI2C::GPIO_AF,
			PinPull::Up,
			PinPolarity::Normal,
			PinSpeed::High,
			PinOType::OpenDrain};
		Pin scl{
			SharedI2C::SCL_port,
			SharedI2C::SCL_pin,
			PinMode::Alt,
			SharedI2C::GPIO_AF,
			PinPull::Up,
			PinPolarity::Normal,
			PinSpeed::High,
			PinOType::OpenDrain};

		i2c.init(SharedI2C::I2Cx, SharedI2C::I2C_TIMING);
	}
};

