#pragma once
#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include <cstdint>
#include <vector>

namespace MetaModule
{

struct AssetFS {
	uint32_t flash_addr;

	AssetFS(uint32_t flash_address)
		: flash_addr{flash_address} {
	}

	std::vector<char> read_image() {
		std::vector<char> raw_image;
		// TODO: read uimg, determine payload size
		// resize raw_image
		// read payload into raw_image
		return raw_image;
	}
};

} // namespace MetaModule
