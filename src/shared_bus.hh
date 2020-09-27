#pragma once
#include "i2c.hh"
#include "i2c_conf.hh"
#include "pin.hh"

class SharedBus {
public:
	static inline I2CPeriph i2c;

	SharedBus(const I2CConfig &defs)
	{
		Pin sda{defs.SDA.gpio,
				defs.SDA.pin,
				PinMode::Alt,
				defs.SDA.af,
				PinPull::Up,
				PinPolarity::Normal,
				PinSpeed::High,
				PinOType::OpenDrain};
		Pin scl{defs.SCL.gpio,
				defs.SCL.pin,
				PinMode::Alt,
				defs.SCL.af,
				PinPull::Up,
				PinPolarity::Normal,
				PinSpeed::High,
				PinOType::OpenDrain};

		i2c.init(defs.I2Cx, defs.timing);
	}
};

