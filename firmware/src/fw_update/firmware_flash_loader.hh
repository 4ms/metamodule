#pragma once
#include "flash_loader/flash_loader.hh"
#include "ld.h"
#include "uimg_header.hh"
#include <memory>

namespace MetaModule
{

class FirmwareFlashLoader {
public:
	FirmwareFlashLoader() {
		//Overwrite buffer with 0's in some key places
		//So we fail unless a valid file is loaded
		auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(ram_buffer);
		uimg_header->ih_magic = 0;
		uimg_header->ih_size = 0;
	}
	uint8_t *buffer() {
		return ram_buffer;
	}

	bool verify_image(size_t filesize) {
		image_size = filesize;

		if (image_size > VIRTDRIVE_SZ) {
			pr_err("image is too large %zu > %zu\n", image_size, VIRTDRIVE_SZ);
			return false;
		}

		auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(ram_buffer);
		BootImageDef::debug_print_raw_header(*uimg_header);

		if (uimg_header->ih_magic != BootImageDef::IH_MAGIC_BE) {
			pr_err("image magic is wrong %zu != %zu\n", uimg_header->ih_magic, BootImageDef::IH_MAGIC_BE);
			return false;
		}

		if ((BootImageDef::be_to_le(uimg_header->ih_size)) > (image_size + 64)) {
			pr_err("header says image size %zu is larger than the file we loaded %zu\n",
				   BootImageDef::be_to_le(uimg_header->ih_size),
				   image_size);
			return false;
		}

		return true;
	}

	bool start() {
		flash = std::make_unique<FlashLoader>();

		if (!flash || !flash->check_flash_chip())
			return false;

		bytes_remaining = image_size;
		cur_read_block = std::span<uint8_t>{ram_buffer, flash_sector_size};

		return true;
	}

	enum class Error { None, Failed };

	std::pair<int, Error> load_next_block() {
		if (!flash->write_sectors(cur_flash_addr, cur_read_block)) {
			return {bytes_remaining, Error::Failed};
		}

		cur_flash_addr += flash_sector_size;
		bytes_remaining -= flash_sector_size;
		cur_read_block = cur_read_block.subspan(flash_sector_size, std::min<int>(flash_sector_size, bytes_remaining));

		return {bytes_remaining, Error::None};
	}

private:
	constexpr static uint32_t flash_base_addr = 0x80000;
	constexpr static uint32_t flash_sector_size = 4096;

	uint8_t *ram_buffer = reinterpret_cast<uint8_t *>(_VIRTDRIVE);

	std::unique_ptr<FlashLoader> flash;

	size_t image_size = 0;
	int bytes_remaining = 0;
	uint32_t cur_flash_addr = flash_base_addr;
	std::span<uint8_t> cur_read_block;
};

} // namespace MetaModule
