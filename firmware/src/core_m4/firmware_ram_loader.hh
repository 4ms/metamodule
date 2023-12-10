#pragma once
#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct FirmwareRamLoader {

	bool load_to_ram(FatFileIO *fileio, std::string_view filename, uint32_t filesize, uint32_t ram_address) {
		if (!fileio || filesize == 0)
			return false;

		auto dest = reinterpret_cast<char *>(ram_address);
		auto buffer = std::span<char>(dest, filesize);

		auto actual_size = fileio->get_file_info(filename).size;
		if (actual_size != filesize)
			return false;

		auto bytes_read = fileio->read_file(filename, buffer);
		if (bytes_read != filesize)
			return false;

		return true;
	}
};

} // namespace MetaModule
