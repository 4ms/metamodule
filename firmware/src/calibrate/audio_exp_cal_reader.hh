#pragma once
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/eeprom_i2c_m24c.hh"
#include "drivers/hsem.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct AudioExpCalibrationReader {
	AudioExpCalibrationReader(mdrivlib::I2CPeriph &i2c, uint8_t device_addr)
		: codec_ext_memory{i2c, 0x50} {
	}

	bool read(uint8_t start_addr, std::span<uint8_t> data) {
		if (get_lock()) {
			auto ok = codec_ext_memory.read(data, start_addr);
			mdrivlib::HWSemaphore<SharedI2CLock>::unlock();
			Debug::Pin1::low();
			return ok;
		} else
			return false;
	}

	bool write(auto data, uint8_t start_addr = 0) {
		if (get_lock()) {
			auto ok = codec_ext_memory.write(data, start_addr);
			mdrivlib::HWSemaphore<SharedI2CLock>::unlock();
			Debug::Pin1::low();
			return ok;
		} else
			return false;
	}

	mdrivlib::M24C_EEPROM codec_ext_memory;

private:
	bool get_lock() {
		uint32_t timeout = 0x100000;
		while (--timeout) {
			if (mdrivlib::HWSemaphore<SharedI2CLock>::lock() == mdrivlib::HWSemaphoreFlag::LockedOk) {
				Debug::Pin1::high();
				return true;
			}
		}
		pr_err("Failed to get lock on I2C bus\n");
		return false;
	}
};

} // namespace MetaModule
