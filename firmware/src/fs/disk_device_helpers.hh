#pragma once
#include "dir_entry_kind.hh"
#include "disk_device.hh"
#include <cstdint>
#include <functional>
#include <string_view>

// TODO: make these non-virtual functions in DiskDevice?

using DirEntryAction =
	std::function<void(std::string_view filename, uint32_t timestamp, uint32_t filesize, DirEntryKind entry_type)>;

struct DiskHelper {

	uint32_t get_file_size(DiskDevice &dev, std::string_view path);

	bool foreach_dir_entry(DiskDevice &dev, std::string_view path, DirEntryAction &&action);
	bool foreach_dir_entry_recursive(std::string_view path, DirEntryAction &&action, unsigned max_depth);

	uint32_t read_file(std::string_view filename, std::span<char> data, uint32_t offset);

	uint32_t write_file(std::string_view filename, std::span<const char> data);
	uint32_t update_or_create_file(std::string_view filename, std::span<const char> data) {
		return write_file(filename, data);
	}
};
