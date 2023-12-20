#pragma once
#include "flash_loader/flash_loader.hh"
#include "fw_update/update_file.hh"
#include "ld.h"
#include "uimg_header.hh"
#include <memory>

namespace MetaModule
{

class FirmwareFlashLoader {
public:
	enum class Error { None, Failed };

	bool verify(std::span<char> filedata, StaticString<32> md5_chars, UpdateType type) {
		if (type != UpdateType::App) {
			pr_err("Only app images can be flashed to internal flash\n");
			return false;
		}

		file = filedata;
		file_size = file.size();

		if (file_size > VIRTDRIVE_SZ) {
			pr_err("image is too large %zu > %zu\n", file_size, VIRTDRIVE_SZ);
			return false;
		}
		if (file_size < sizeof(BootImageDef::ImageHeader)) {
			pr_err("image too small to be uimg\n");
			return false;
		}

		//TODO: check md5
		uint32_t md5[4];
		for (auto i = 0u; i < 4; i++) {
			auto s = std::string{std::string_view{md5_chars}.substr(8 * i, 8)};
			md5[i] = std::strtoul(s.c_str(), nullptr, 16);
		}
		pr_dbg("MD5 is %s (%08x %08x %08x %08x)\n", md5_chars.c_str(), md5[0], md5[1], md5[2], md5[3]);

		auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(file.data());
		// BootImageDef::debug_print_raw_header(*uimg_header);

		if (uimg_header->ih_magic != BootImageDef::IH_MAGIC_BE) {
			pr_err("image magic is wrong %zu != %zu\n", uimg_header->ih_magic, BootImageDef::IH_MAGIC_BE);
			return false;
		}

		if ((BootImageDef::be_to_le(uimg_header->ih_size)) > (file_size + 64)) {
			pr_err("Header says image size is %zu, which is larger than the file size (%zu)\n",
				   BootImageDef::be_to_le(uimg_header->ih_size),
				   file_size);
			return false;
		}

		return true;
	}

	bool start() {

		flash = std::make_unique<FlashLoader>();

		if (!flash || !flash->check_flash_chip())
			return false;

		bytes_remaining = file_size;

		cur_read_block = file.subspan(0, flash_sector_size);

		return true;
	}

	std::pair<int, Error> load_next_block() {
		if (bytes_remaining > 0) {

			if (!flash->write_sectors(cur_flash_addr, cur_read_block)) {
				return {bytes_remaining, Error::Failed};
			}

			cur_flash_addr += flash_sector_size;
			bytes_remaining -= flash_sector_size;
			cur_read_block =
				cur_read_block.subspan(flash_sector_size, std::min<int>(flash_sector_size, bytes_remaining));
		}

		return {bytes_remaining, Error::None};
	}

private:
	constexpr static uint32_t flash_base_addr = 0x80000;
	constexpr static uint32_t flash_sector_size = 4096;

	std::unique_ptr<FlashLoader> flash;

	size_t file_size = 0;
	int bytes_remaining = 0;
	uint32_t cur_flash_addr = flash_base_addr;
	std::span<char> file;
	std::span<char> cur_read_block;
};

} // namespace MetaModule
