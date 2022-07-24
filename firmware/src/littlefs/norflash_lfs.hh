#pragma once
#include "callable.hh"
#include "lib/littlefs/lfs.h"
#include "norflash_ops.hh"
#include "patches_default.hh"
#include <string_view>

class LittleNorFS {
	lfs_t lfs;
	mdrivlib::QSpiFlash &_flash;

public:
	static constexpr uint32_t BlockSize = 4096;
	enum class Status { AlreadyFormatted, NewlyFormatted, FlashError, LFSError };

	LittleNorFS(mdrivlib::QSpiFlash &flash)
		: _flash{flash} {
	}

	Status initialize() {
		const struct lfs_config cfg = {
			.context = &_flash,
			.read = NorFlashOps::read,
			.prog = NorFlashOps::prog,
			.erase = NorFlashOps::erase,
			.sync = NorFlashOps::sync,

			.read_size = 16,
			.prog_size = 16,
			.block_size = BlockSize,
			.block_count = 128,
			.block_cycles = 500,
			.cache_size = 16,
			.lookahead_size = 16,
		};

		if (!_flash.check_chip_id(0x180001, 0x00180001)) { //182001 or 186001 or 1840EF
			printf("ERROR: NOR Flash returned wrong id\n");
			return Status::FlashError;
		}

		auto err = lfs_mount(&lfs, &cfg);
		if (err >= 0)
			return Status::AlreadyFormatted; // first mount successful, FS already exists

		// No FS on disk, format and re-mount
		if (lfs_format(&lfs, &cfg) < 0)
			return Status::LFSError;
		if (lfs_mount(&lfs, &cfg) < 0)
			return Status::LFSError;

		return Status::NewlyFormatted;
	}

	bool create_file(const std::string_view filename, const std::span<const char> data) {
		lfs_file_t file;
		if (lfs_file_open(&lfs, &file, filename.data(), LFS_O_CREAT | LFS_O_WRONLY) < 0)
			return false;

		if (lfs_file_write(&lfs, &file, data.data(), data.size_bytes()) < 0)
			return false;

		lfs_file_close(&lfs, &file);

		return true;
	}

	// bool read_file(const std::string_view filename, std::span<char> data) {

	// 	lfs_info info;
	// 	if (lfs_stat(&lfs, filename.data(), &info) < 0)
	// 		return false;

	// 	lfs_file_t file;
	// 	if (lfs_file_open(&lfs, &file, filename.data(), LFS_O_RDONLY) < 0)
	// 		return false;

	// 	if (lfs_file_read(&lfs, &file, data.data(), data.size_bytes()) < 0)
	// 		return false;

	// 	lfs_file_close(&lfs, &file);

	// 	return true;
	// }

	using FileAction = std::function<void(const std::string_view filename, const std::span<const char> data)>;

	// Performs an action(file_name, file_data) on each file in LittleFS ending with the extension
	bool foreach_file_with_ext(const std::string_view extension, FileAction action) {
		lfs_dir_t dir;

		if (lfs_dir_open(&lfs, &dir, "/") < 0)
			return false;

		lfs_dir_rewind(&lfs, &dir);

		lfs_info info;
		while (int err = lfs_dir_read(&lfs, &dir, &info) != 0) {
			if (err < 0)
				return false;

			if (std::string_view{info.name}.ends_with(extension)) {
				lfs_file_t file;
				if (lfs_file_open(&lfs, &file, info.name, LFS_O_RDONLY) < 0) {
					printf("Warning: Can't open file %s\n", info.name);
					continue;
				}

				std::array<char, 4096> _data;
				auto bytes_read = lfs_file_read(&lfs, &file, &_data, _data.size());
				if (bytes_read <= 0)
					continue;
				if (info.size > _data.size()) {
					printf("Warning: File %s is %d bytes, exceeds max %d\n", info.name, info.size, _data.size());
					continue;
				}

				lfs_file_close(&lfs, &file);

				action(info.name, _data);
			}
		}

		lfs_dir_close(&lfs, &dir);

		return true; //if there's any error
	}
};
