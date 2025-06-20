#pragma once
#include "drivers/i2c.hh"

namespace MetaModule
{

class BatteryGuage {
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	BatteryGuage(mdrivlib::I2CConfig const &config, uint8_t I2C_address)
		: i2c{config}
		, address{I2C_address} {
		i2c.enable_IT(config.priority1, config.priority2);
	}

	void init() {
		dump_registers();
	}

	void update() {
		if (!i2c.is_ready())
			return;
	}

	void dump_registers() {
		HAL_Delay(100);
		uint8_t val[3];

		val[0] = 0x00;
		val[1] = 0x01;
		val[2] = 0x00;

		auto err = i2c.mem_write(address, 0x04, I2C_MEMADD_SIZE_8BIT, val, 2);
		if (err != I2CPeriph::Error::I2C_NO_ERR)
			printf("Write ERR %d\n", err);
		err = i2c.read(address, val, 2);
		if (err == I2CPeriph::Error::I2C_NO_ERR)
			printf("Device ID: %02x %02x\n", val[0], val[1]);
		else
			printf("Read ERR %d\n", err);

		err = i2c.mem_read(address, 0x04, I2C_MEMADD_SIZE_8BIT, val, 2);
		if (err == I2CPeriph::Error::I2C_NO_ERR)
			printf("mV = %02x %02x\t", val[0], val[1]);
		else
			printf("ERR %d\n", err);
	}

private:
	I2CPeriph i2c{};
	uint8_t address{0x55};
};

} // namespace MetaModule
