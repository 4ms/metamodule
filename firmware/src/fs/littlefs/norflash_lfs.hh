#pragma once
#include "drivers/callable.hh"
#include "ff.h"
#include "fs/dir_entry_kind.hh"
#include "fs/littlefs/norflash_ops.hh"
#include "fs/time_convert.hh"
#include "fs/volumes.hh"
#include "lib/littlefs/lfs.h"
#include "patch_file/patches_default.hh"
#include "pr_dbg.hh"
#include <string_view>

namespace MetaModule
{

template<size_t VolumeFlashAddr, size_t VolumeFlashSize>
class LfsFileIO {
	lfs_t lfs{};
	mdrivlib::QSpiFlash &_flash;

	using ThisNorFlashOps = NorFlashOps<VolumeFlashAddr, VolumeFlashSize>;

public:
	static constexpr uint32_t BlockSize = 4096;
	enum class Status { AlreadyFormatted, NewlyFormatted, FlashError, LFSError };

	const std::string_view _volname{"LFS Flash"};

	LfsFileIO(LfsFileIO &other) = delete;

	LfsFileIO(mdrivlib::QSpiFlash &flash)
		: _flash{flash} {
	}

	Status initialize() {
		if (!_flash.check_chip_id(0x180001, 0x00180001)) { //182001 or 186001 or 1840EF
			pr_err("ERROR: NOR Flash returned wrong id\n");
			return Status::FlashError;
		}

		const static lfs_config cfg = {
			.context = &_flash,
			.read = ThisNorFlashOps::read,
			.prog = ThisNorFlashOps::prog,
			.erase = ThisNorFlashOps::erase,
			.sync = ThisNorFlashOps::sync,

			.read_size = 16,
			.prog_size = 16,
			.block_size = BlockSize,
			.block_count = ThisNorFlashOps::Size / BlockSize,
			.block_cycles = 500,
			.cache_size = 1024,
			.lookahead_size = 64,
		};

		pr_trace("Configure lfs with %u blocks (%u/%u)\n", cfg.block_count, ThisNorFlashOps::Size, BlockSize);
		auto err = lfs_mount(&lfs, &cfg);
		if (err >= 0) {
			pr_info("LittleFS mounted OK\n");
			return Status::AlreadyFormatted;
		}

		pr_info("LittleFS not formatted\n");

		return Status::LFSError;
	}

	std::string_view volname() const {
		return _volname;
	}

	Volume vol_id() {
		return Volume::NorFlash;
	}

	bool is_mounted() {
		//TODO: check if fs is ok, maybe like this?
		//return lfs_stat(&lfs, "/", &info) >= 0;
		return true;
	}

	Status reformat() {
		const static lfs_config cfg = {
			.context = &_flash,
			.read = ThisNorFlashOps::read,
			.prog = ThisNorFlashOps::prog,
			.erase = ThisNorFlashOps::erase,
			.sync = ThisNorFlashOps::sync,

			.read_size = 16,
			.prog_size = 16,
			.block_size = BlockSize,
			.block_count = ThisNorFlashOps::Size / BlockSize,
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

	uint32_t write_file(const std::string_view filename, const std::span<const char> data, int flags) {
		TimeFile file;

		auto err = time_file_open(&file, filename.data(), LFS_O_CREAT | LFS_O_WRONLY | flags);
		if (err < 0) {
			pr_err("LFS: Open failed with err %d\n", err);
			return 0;
		}

		file.timestamp = get_fattime();

		pr_trace("LFS: write file %s, timestamp 0x%x, size %u\n", filename.data(), file.timestamp, data.size());

		if (err = lfs_file_write(&lfs, &file.file, data.data(), data.size_bytes()); err < 0) {
			pr_err("LFS: Write failed with err %d\n", err);
			return 0;
		}

		if (err = lfs_file_close(&lfs, &file.file); err < 0) {
			pr_err("LFS: Closing failed with err %d\n", err);
			return 0;
		}

		return data.size_bytes();
	}

	// Write
	uint32_t write_file(const std::string_view filename, std::span<const char> buffer) {
		return write_file(filename, buffer, LFS_O_TRUNC);
	}

	uint32_t append_file(const std::string_view filename, std::span<const char> buffer) {
		return write_file(filename, buffer, LFS_O_APPEND);
	}

	uint32_t update_or_create_file(const std::string_view filename, const std::span<const char> data) {
		return write_file(filename, data, LFS_O_TRUNC);
	}

	bool delete_file(const std::string_view filename) {
		auto err = lfs_remove(&lfs, filename.data());
		return (err >= 0);
	}

	uint32_t get_file_size(std::string_view filename) {
		lfs_info info;
		auto err = lfs_stat(&lfs, filename.data(), &info);
		if (err < 0)
			return 0;
		else
			return info.size;
	}

	// Reads into buffer, returns the bytes actually read
	uint32_t read_file(const std::string_view filename, std::span<char> buffer, std::size_t offset = 0) {
		TimeFile tfile;
		auto &file = tfile.file;

		auto err = time_file_open(&tfile, filename.data(), LFS_O_RDONLY);
		if (err < 0)
			return 0;

		auto seek_err = lfs_file_seek(&lfs, &file, offset, LFS_SEEK_SET);
		if (seek_err < 0)
			return 0;

		auto bytes_read = time_file_read(&tfile, buffer.data(), buffer.size_bytes());
		if (bytes_read <= 0)
			return 0;

		lfs_file_close(&lfs, &file);
		return bytes_read;
	}

	// Performs an action(filename, timestamp) on each file in LittleFS root dir ending with the extension
	// TODO: Add parameter for dir to search
	bool foreach_file_with_ext(const std::string_view extension, auto action) {
		lfs_dir_t dir;
		if (lfs_dir_open(&lfs, &dir, "/") < 0)
			return false;

		lfs_dir_rewind(&lfs, &dir);

		lfs_info info{};
		while (int err = lfs_dir_read(&lfs, &dir, &info) != 0) {
			if (err < 0)
				return false;

			if (std::string_view{info.name}.ends_with(extension)) {
				auto timestamp = get_file_timestamp(info.name);
				if (timestamp)
					action(info.name, timestamp, info.size);
			}
		}

		lfs_dir_close(&lfs, &dir);

		return true;
	}

	// TODO: Add parameter for dir to search
	bool foreach_dir_entry(std::string_view path, auto action) {
		lfs_dir_t dir;
		if (lfs_dir_open(&lfs, &dir, "/") < 0)
			return false;

		lfs_dir_rewind(&lfs, &dir);

		lfs_info info{};
		while (int err = lfs_dir_read(&lfs, &dir, &info) != 0) {
			if (err < 0)
				return false;

			auto entry_type = info.type == LFS_TYPE_DIR ? DirEntryKind::Dir : DirEntryKind::File;

			auto timestamp = get_file_timestamp(info.name);
			if (timestamp)
				action(info.name, timestamp, info.size, entry_type);
		}

		lfs_dir_close(&lfs, &dir);

		return true;
	}

	////// Time Attribute:

	enum { ATTR_TIMESTAMP = 0x74 };

	struct TimeFile {
		lfs_file_t file{};
		uint32_t timestamp{};
		lfs_attr attrs[1]{};
		lfs_file_config cfg{.attrs = attrs, .attr_count = 1};
	};

	uint32_t get_file_timestamp(std::string_view filename) {
		uint32_t ts{};
		auto res = lfs_getattr(&lfs, filename.data(), ATTR_TIMESTAMP, &ts, sizeof(TimeFile::timestamp));
		if (res < 0)
			return 0;
		return ts;
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		lfs_setattr(&lfs, filename.data(), ATTR_TIMESTAMP, &timestamp, sizeof(TimeFile::timestamp));
	}

	int time_file_open(TimeFile *tfile, const char *path, int flags) {
		// set up description of timestamp attribute
		tfile->attrs[0].type = ATTR_TIMESTAMP;
		tfile->attrs[0].buffer = &tfile->timestamp;
		tfile->attrs[0].size = sizeof(TimeFile::timestamp);

		// attributes will be automatically populated during open call
		return lfs_file_opencfg(&lfs, &tfile->file, path, flags, &tfile->cfg);
	}

	int time_file_write(TimeFile *file, const void *buffer, size_t size) {
		file->timestamp = get_fattime();
		return lfs_file_write(&lfs, &file->file, buffer, size);
	}

	int time_file_read(TimeFile *file, void *buffer, size_t size) {
		return lfs_file_read(&lfs, &file->file, buffer, size);
	}
};
} // namespace MetaModule
