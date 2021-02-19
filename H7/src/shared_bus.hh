#pragma once
#include "debug.hh"
#include "drivers/i2c.hh"
using namespace mdrivlib;

class SharedBus {
public:
	static inline I2CPeriph i2c;

	SharedBus(const I2CConfig &defs)
	{
		i2c.init(defs);
	}

	static void process_queue()
	{
		//
	}
};

