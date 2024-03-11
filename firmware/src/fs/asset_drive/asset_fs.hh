#pragma once
#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include "pr_dbg.hh"
#include "uimg_header.hh"
#include <cstdint>
#include <vector>

namespace MetaModule
{

struct AssetFS {
	uint32_t flash_addr;
	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};

	AssetFS(uint32_t flash_address)
		: flash_addr{flash_address} {
	}

	std::vector<char> read_image() {
		Uimg::image_header header;

		if (!flash_.read(reinterpret_cast<uint8_t *>(&header), flash_addr, 64)) {
			pr_err("Unable to read header from flash at 0x%x\n", flash_addr);
			return {};
		}

		if (Uimg::be2le(header.ih_magic) != Uimg::IH_MAGIC) {
			pr_err("No valid uimg header found in flash at 0x%x. Magic found = %x\n",
				   flash_addr,
				   Uimg::be2le(header.ih_magic));
			return {};
		}

		auto tar_image_size = Uimg::be2le(header.ih_size);
		if (tar_image_size <= 4 * 1024 * 1024) {
			pr_err("Tar is invalid size: %zu\n", tar_image_size);
			return {};
		}

		std::vector<char> raw_image(tar_image_size);
		if (!flash_.read((uint8_t *)raw_image.data(), flash_addr + sizeof(header), tar_image_size)) {
			pr_err(
				"Failed to read tar image from flash @ %x + %u bytes\n", flash_addr + sizeof(header), tar_image_size);
			return {};
		}

		pr_info("Read tar image: %zu bytes\n", tar_image_size);

		return raw_image;
	}
};

} // namespace MetaModule
