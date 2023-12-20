#pragma once
#include "drivers/qspi_flash_driver.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

class FlashLoader {
public:
	FlashLoader();
	bool check_flash_chip();
	bool write_sectors(uint32_t base_addr, std::span<uint8_t> buffer);
	bool write_sectors(uint32_t base_addr, std::span<char> buffer);

private:
	mdrivlib::QSpiFlash flash;
};

} // namespace MetaModule
