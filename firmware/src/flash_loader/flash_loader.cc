#include "flash_loader.hh"
#include "conf/qspi_flash_conf.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

FlashLoader::FlashLoader()
	: flash{qspi_patchflash_conf} {
}

bool FlashLoader::check_flash_chip() {
	return flash.check_chip_id(0x180001, 0x00180001); //182001 or 186001 or 1840EF
}

bool FlashLoader::write_sectors(uint32_t base_addr, std::span<uint8_t> buffer) {
	//round up to smallest 4kB blocks that contains image
	unsigned bytes_to_erase = (buffer.size() + 4095) & ~4095;

	uint32_t addr = base_addr;

	while (bytes_to_erase) {
		pr_trace("Erasing sector at 0x%x\n", (unsigned)addr);
		flash.erase(mdrivlib::QSpiFlash::SECTOR, addr);
		addr += 4096;
		bytes_to_erase -= 4096;
	}

	pr_dbg("Writing 0x%x B to %x\n", buffer.size(), base_addr);
	if (!flash.write(buffer.data(), base_addr, buffer.size())) {
		pr_err("ERROR: Flash failed to write\n");
		return false;
	}

	return true;
}

bool FlashLoader::write_sectors(uint32_t base_addr, std::span<char> buffer) {
	auto buff_u8 = std::span<uint8_t>{reinterpret_cast<uint8_t *>(buffer.data()), buffer.size()};
	return write_sectors(base_addr, buff_u8);
}

} // namespace MetaModule
