#pragma once
#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct FirmwareRamLoader {

	bool load_to_ram(FatFileIO *fileio, std::string_view filename, std::span<char> buffer) {
		if (!fileio || buffer.size() == 0)
			return false;

		auto actual_size = fileio->get_file_info(filename).size;

		if (actual_size == 0)
			return false;

		if (actual_size != buffer.size())
			return false;

		auto bytes_read = fileio->read_file(filename, buffer);

		if (bytes_read < actual_size)
			return false;

		return true;
	}
};

} // namespace MetaModule
