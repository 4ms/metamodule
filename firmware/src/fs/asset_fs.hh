#pragma once
#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include "pr_dbg.hh"
#include <cstdint>
#include <vector>

namespace MetaModule
{

struct AssetFS {
	uint32_t flash_addr;
	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	struct image_header {
		uint32_t ih_magic;	 /* Image Header Magic Number */
		uint32_t ih_hcrc;	 /* Image Header CRC Checksum */
		uint32_t ih_time;	 /* Image Creation Timestamp */
		uint32_t ih_size;	 /* Image Data Size */
		uint32_t ih_load;	 /* Data	 Load  Address */
		uint32_t ih_ep;		 /* Entry Point Address */
		uint32_t ih_dcrc;	 /* Image Data CRC Checksum */
		uint8_t ih_os;		 /* Operating System */
		uint8_t ih_arch;	 /* CPU architecture */
		uint8_t ih_type;	 /* Image Type */
		uint8_t ih_comp;	 /* Compression Type */
		uint8_t ih_name[32]; /* Image Name */
	};

	AssetFS(uint32_t flash_address)
		: flash_addr{flash_address} {
	}

	std::vector<char> read_image() {
		std::vector<char> raw_image;
		image_header header;
		if (flash_.read(reinterpret_cast<uint8_t *>(&header), flash_addr, 64)) {

		} else
			pr_err("Unable to read header from flash at 0x%x\n", flash_addr);

		// TODO: read uimg, determine payload size
		// resize raw_image
		// read payload into raw_image
		return raw_image;
	}
};

} // namespace MetaModule
