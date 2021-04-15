#pragma once
#include "drivers/i2c.hh"

using namespace mdrivlib;
namespace MetaModule
{

// Singleton class
class SharedBus {
public:
	static inline I2CPeriph i2c;
	SharedBus(const I2CConfig &i2c_conf_)
	{
		i2c.init(i2c_conf_);
	}
};
} // namespace MetaModule
