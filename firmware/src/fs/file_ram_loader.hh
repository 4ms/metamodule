#pragma once
#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct FileRamLoader {

	bool load_to_ram(FatFileIO *fileio, std::string_view filename, std::span<char> buffer) {
		if (!fileio || buffer.size() == 0) {
			pr_err("Invalid volume or destination buffer. Cannot load to RAM\n");
			return false;
		}

		auto actual_size = fileio->get_file_info(filename).size;

		if (actual_size == 0) {
			pr_err("File %.*s is not found\n", (int)filename.size(), filename.data());
			return false;
		}

		if (actual_size != buffer.size()) {
			pr_err("File size %u does not match buffer size %zu\n", actual_size, buffer.size());
			return false;
		}

		auto bytes_read = fileio->read_file(filename, buffer);

		if (bytes_read < actual_size) {
			pr_err("Failed to read %u bytes. Only read %u\n", actual_size, bytes_read);
			return false;
		}

		return true;
	}
};

} // namespace MetaModule
