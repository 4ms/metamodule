#pragma once
#include "callable.hh"
#include "ff.h"
#include "lib/littlefs/lfs.h"
#include "norflash_ops.hh"
#include "patches_default.hh"
#include "printf.h"
#include "time_convert.hh"
#include <string_view>

class LittleNorFS {
	lfs_t lfs;
	mdrivlib::QSpiFlash &_flash;

public:
	static constexpr uint32_t BlockSize = 4096;
	static constexpr uint32_t MaxFileSize = 32768;
	enum class Status { AlreadyFormatted, NewlyFormatted, FlashError, LFSError };
	std::array<char, MaxFileSize> _data;

	LittleNorFS(mdrivlib::QSpiFlash &flash)
		: _flash{flash} {
	}

	Status initialize() {
		if (!_flash.check_chip_id(0x180001, 0x00180001)) { //182001 or 186001 or 1840EF
			printf_("ERROR: NOR Flash returned wrong id\n");
			return Status::FlashError;
		}

		const static lfs_config cfg = {
			.context = &_flash,
			.read = NorFlashOps::read,
			.prog = NorFlashOps::prog,
			.erase = NorFlashOps::erase,
			.sync = NorFlashOps::sync,

			.read_size = 16,
			.prog_size = 16,
			.block_size = BlockSize,
			.block_count = (_flash.get_chip_size_bytes() - NorFlashOps::FlashOffset) / BlockSize,
			.block_cycles = 500,
			.cache_size = 1024,
			.lookahead_size = 64,
		};

		auto err = lfs_mount(&lfs, &cfg);
		if (err >= 0)
			return Status::AlreadyFormatted;

		// No FS on disk, format and re-mount
		if (lfs_format(&lfs, &cfg) < 0)
			return Status::LFSError;
		if (lfs_mount(&lfs, &cfg) < 0)
			return Status::LFSError;

		return Status::NewlyFormatted;
	}

	Status reformat() {
		const static lfs_config cfg = {
			.context = &_flash,
			.read = NorFlashOps::read,
			.prog = NorFlashOps::prog,
			.erase = NorFlashOps::erase,
			.sync = NorFlashOps::sync,

			.read_size = 16,
			.prog_size = 16,
			.block_size = BlockSize,
			.block_count = (_flash.get_chip_size_bytes() - NorFlashOps::FlashOffset) / BlockSize,
			.block_cycles = 500,
			.cache_size = 1024,
			.lookahead_size = 64,
		};
		if (lfs_format(&lfs, &cfg) < 0)
			return Status::LFSError;
		if (lfs_mount(&lfs, &cfg) < 0)
			return Status::LFSError;

		return Status::NewlyFormatted;
	}

	bool
	update_or_create_file(const std::string_view filename, const std::span<const char> data, uint32_t timestamp = 0) {
		TimeFile file;

		auto err = time_file_open(&file, filename.data(), LFS_O_CREAT | LFS_O_WRONLY);
		if (err < 0) {
			printf_("Open failed with err %d\n", err);
			return false;
		}

		file.timestamp = timestamp ? timestamp : get_fattime();

		printf_("Littlefs: updating or creating file %s, timestamp 0x%x\n", filename.data(), file.timestamp);
		if (int err = lfs_file_write(&lfs, &file.file, data.data(), data.size_bytes()); err < 0) {
			printf_("Write failed with err %d\n", err);
			return false;
		}

		lfs_file_close(&lfs, &file.file);

		return true;
	}

	bool delete_file(const std::string_view filename) {
		auto err = lfs_remove(&lfs, filename.data());
		return (err >= 0);
	}

	using FileAction =
		std::function<void(const std::string_view filename, uint32_t timestamp, const std::span<char> data)>;

	// Performs an action(filename, timestamp, file_data) on each file in LittleFS ending with the extension
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

				//action(info.name);

				TimeFile file;
				if (time_file_open(&file, info.name, LFS_O_RDONLY) < 0) {
					printf_("Warning: Can't open file %s\n", info.name);
					continue;
				}

				auto bytes_read = lfs_file_read(&lfs, &file.file, &_data, _data.size());
				if (bytes_read <= 0)
					continue;
				if (info.size > _data.size()) {
					printf_(
						"Warning: File %s is %d bytes, exceeds max %d. Skipping\n", info.name, info.size, _data.size());
					continue;
				}
				lfs_file_close(&lfs, &file.file);

				action(info.name, file.timestamp, {_data.data(), info.size});
			}
		}

		lfs_dir_close(&lfs, &dir);

		return true;
	}

	enum { ATTR_TIMESTAMP = 0x74 };

	struct TimeFile {
		lfs_file_t file;
		uint32_t timestamp;
		lfs_attr attrs[1];
		lfs_file_config cfg{.attrs = attrs, .attr_count = 1};
	};

	uint32_t get_file_timestamp(std::string_view filename) {
		uint32_t ts;
		auto res = lfs_getattr(&lfs, filename.data(), ATTR_TIMESTAMP, &ts, sizeof(TimeFile::timestamp));
		if (res < 0)
			return 0;
		return ts;
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		auto res = lfs_setattr(&lfs, filename.data(), ATTR_TIMESTAMP, &timestamp, sizeof(TimeFile::timestamp));
	}

	int time_file_open(TimeFile *tfile, const char *path, int flags) {
		// set up description of timestamp attribute
		tfile->attrs[0].type = ATTR_TIMESTAMP;
		tfile->attrs[0].buffer = &tfile->timestamp;
		tfile->attrs[0].size = sizeof(TimeFile::timestamp);

		// attributes will be automatically populated during open call
		return lfs_file_opencfg(&lfs, &tfile->file, path, flags, &tfile->cfg);
	}

	// int time_file_write(TimeFile *tfile, const void *buffer, size_t size) {
	// 	tfile->timestamp = get_fattime(); //make_timestamp(2018, 9, 19, 7, 30, 45);
	// 	return lfs_file_write(&lfs, &tfile->file, buffer, size);
	// }
};
