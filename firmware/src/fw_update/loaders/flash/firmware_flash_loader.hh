#pragma once

#include "../abstract_loader.hh"
#include "flash_loader/flash_loader.hh"
#include <memory>

namespace MetaModule
{

class FirmwareFlashLoader : public FileWorkerBase{
public:
	FirmwareFlashLoader(std::span<char> filedata, std::size_t address);

	Error start() override;

	std::pair<std::size_t, Error> process() override;

private:
	const std::size_t BaseAddress;
	constexpr static uint32_t flash_sector_size = 4096;

	std::unique_ptr<FlashLoader> flash;

	std::size_t bytes_completed = 0;
	uint32_t cur_flash_addr;
	std::span<char> file;
	std::span<char> cur_read_block;
};

} // namespace MetaModule
