#pragma once
#include "bus_defs.hh"

class Buses {
public:
	static inline i2cPeriph i2c;

	Buses() {
		Pin sda {
			SharedI2C::GPIO,
			SharedI2C::SDA_PIN,
			PinMode::Alt,
			SharedI2C::GPIO_AF,
			PinPull::Up,
			PinPolarity::Normal,
			PinSpeed::High,
			PinOType::OpenDrain
		};
		Pin scl {
			SharedI2C::GPIO,
			SharedI2C::SCL_PIN,
			PinMode::Alt,
			SharedI2C::GPIO_AF,
			PinPull::Up,
			PinPolarity::Normal,
			PinSpeed::High,
			PinOType::OpenDrain
		};

		i2c.init( SharedI2C::I2Cx, SharedI2C::I2C_TIMING );
	}
};

