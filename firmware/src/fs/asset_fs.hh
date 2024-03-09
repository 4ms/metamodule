#pragma once
#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include <cstdint>
#include <vector>

namespace MetaModule
{

struct AssetFS {

	std::vector<char> raw_image;

	AssetFS(uint32_t flash_address) {
		// Read uimg header from flash_address
		// If valid, extract the size
		// Read that many bytes past the header into raw_image.data()
		printf("hardware\n");
	}

	void release() {
		raw_image.clear();
		raw_image.shrink_to_fit();
	}
};

} // namespace MetaModule
