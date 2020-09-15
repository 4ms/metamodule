#pragma once
#include "defs/bus_defs.hh"

class Buses {
public:
	static inline I2CPeriph shared_i2c;

	Buses()
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

		shared_i2c.init(SharedI2C::I2Cx, SharedI2C::I2C_TIMING);
	}
};

