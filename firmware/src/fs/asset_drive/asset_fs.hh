#pragma once
#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include "ld.h"
#include "pr_dbg.hh"
#include "uimg_header.hh"
#include <cstdint>
#include <cstring>
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
		if (auto image = read_ram_image(); image.size())
			return image;

		Uimg::image_header header;

		if (!flash_.read(reinterpret_cast<uint8_t *>(&header), flash_addr, sizeof header)) {
			pr_err("Unable to read header from flash at 0x%x\n", flash_addr);
			return {};
		}

		auto magic = Uimg::be32_to_cpu(header.ih_magic);
		if (magic != Uimg::IH_MAGIC) {
			pr_err("No valid uimg header found in flash at 0x%x. Magic found = %x\n", flash_addr, magic);
			return {};
		}

		auto tar_image_size = Uimg::be32_to_cpu(header.ih_size);
		if (tar_image_size > (4 * 1024 * 1024 - 64)) {
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

private:
	// Development shortcut (make jprog-assets, make flash-t32-assets): the debugger loads
	// assets.uimg into RAM in the FW buffer, and writes its address to TAMP->BKP8R.
	// The register is cleared here, so only this boot uses the RAM image: after a reset or
	// power cycle the assets are read from flash again.
	static std::vector<char> read_ram_image() {
		constexpr uint32_t RamImageAddrReg = 0x5C00A120; // TAMP->BKP8R
		auto *addr_reg = reinterpret_cast<volatile uint32_t *>(RamImageAddrReg);

		uint32_t addr = *addr_reg;
		if (addr == 0)
			return {};

		// mp1-boot leaves the backup domain unlocked when booting from DDR; assert DBP again to be safe
		*reinterpret_cast<volatile uint32_t *>(0x50001000) |= (1u << 8); // PWR_CR1.DBP
		*addr_reg = 0;

		// FW buffer is non-cacheable, so we see exactly what the debugger wrote
		const uint32_t buf_start = FWBUFFER;
		const uint32_t buf_end = FWBUFFER + FWBUFFER_SZ;
		if (addr < buf_start || addr >= buf_end - sizeof(Uimg::image_header)) {
			pr_err("Assets image address in RAM (0x%x) is not in the FW buffer\n", addr);
			return {};
		}

		Uimg::image_header header;
		memcpy(&header, reinterpret_cast<void const *>(addr), sizeof header);

		auto magic = Uimg::be32_to_cpu(header.ih_magic);
		if (magic != Uimg::IH_MAGIC) {
			pr_err("No valid uimg header found in RAM at 0x%x. Magic found = %x\n", addr, magic);
			return {};
		}

		auto tar_addr = addr + sizeof header;
		auto tar_image_size = Uimg::be32_to_cpu(header.ih_size);
		if (tar_image_size > (4 * 1024 * 1024 - 64) || tar_image_size > buf_end - tar_addr) {
			pr_err("Tar in RAM is invalid size: %zu\n", tar_image_size);
			return {};
		}

		std::vector<char> raw_image(tar_image_size);
		memcpy(raw_image.data(), reinterpret_cast<void const *>(tar_addr), tar_image_size);

		pr_info("Using assets loaded into RAM by the debugger at 0x%x: %zu bytes\n", addr, tar_image_size);

		return raw_image;
	}
};

} // namespace MetaModule
