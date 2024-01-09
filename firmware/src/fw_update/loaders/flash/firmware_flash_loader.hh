#pragma once

#include "fw_update/update_file.hh"
#include "flash_loader/flash_loader.hh"
#include <memory>
#include <span>
#include "../abstract_loader.hh"

namespace MetaModule
{

class FirmwareFlashLoader : public FileLoaderBase{
public:
	FirmwareFlashLoader(std::span<char> filedata);

	bool verify(StaticString<32> md5_chars);

	bool start();

	std::pair<std::size_t, Error> load_next_block();

private:
	constexpr static uint32_t flash_base_addr = 0x80000;
	constexpr static uint32_t flash_sector_size = 4096;

	std::unique_ptr<FlashLoader> flash;

	std::size_t bytes_completed = 0;
	uint32_t cur_flash_addr = flash_base_addr;
	std::span<char> file;
	std::span<char> cur_read_block;
};

} // namespace MetaModule
