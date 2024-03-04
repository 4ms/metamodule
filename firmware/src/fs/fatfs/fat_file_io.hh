#pragma once
#include "disk_ops.hh"
#include "fs/dir_entry_kind.hh"
#include "fs/volumes.hh"
#include "pr_dbg.hh"
#include <cstdint>
#include <span>
#include <string>
#include <string_view>

// defined in fatfs/diskio.cc:
bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id);

class FatFileIO {
	using Volume = MetaModule::Volume;

	FATFS fs{};
	const Volume _vol;
	const char _fatvol[3];	//NOLINT
	const char _volname[8]; //NOLINT

public:
	struct __attribute__((packed)) FileInfo {
		uint32_t size;
		uint8_t year;
		uint8_t month;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
	};

	FatFileIO(DiskOps *diskops, Volume vol_id)
		: _vol{vol_id}
		, _fatvol{char(char(vol_id) + '0'), ':', '\0'}
		, _volname{'F', 'A', 'T', 'F', 'S', ':', char(char(vol_id) + '0'), '\0'} {
		if (!fatfs_register_disk(diskops, static_cast<unsigned>(_vol))) {
			pr_err("Failed to register FAT FS Disk %d\n", _vol);
		}
	}

	bool mount_disk() {
		// Try mounting previously mounted partition,
		// if that fails, try auto-detect, then each partition 1 - 8.

		uint8_t err = 0;

		// Don't try auto-scan twice in a row
		uint8_t first_part_num = (VolToPart[(unsigned)_vol].pt == 0) ? 1 : 0;

		for (uint8_t part_num = first_part_num; part_num <= 9; part_num++) {

			if (err = f_mount(&fs, _fatvol, 1); err == FR_OK) {
				pr_trace("Mounted partition %d on volume %d\n", VolToPart[(unsigned)_vol].pt, _vol);
				return true;
			}

			pr_trace("Tried and failed to mount vol %d, part %d. err:%d\n", _vol, VolToPart[(unsigned)_vol].pt, err);

			VolToPart[(unsigned)_vol].pt = part_num;
		}

		if (VolToPart[(unsigned)_vol].pt == 9) {
			VolToPart[(unsigned)_vol].pt = 0;
		}

		pr_err("Could not mount volume %d, tried auto scanning and manually loading partitions 1-8. last err: %d\n",
			   _vol,
			   err);
		return false;
	}

	bool unmount_disk() {
		auto disk_id = static_cast<uint8_t>(_vol);
		return (disk_ioctl(disk_id, CTRL_EJECT, nullptr) == RES_OK);
	}

	std::string_view volname() {
		return _volname;
	}

	Volume vol_id() {
		return _vol;
	}

	bool is_mounted() {
		auto disk_id = static_cast<uint8_t>(_vol);
		uint8_t mounted = 0;
		auto err = disk_ioctl(disk_id, MMC_GET_SDSTAT, &mounted);
		return (err == RES_OK) && mounted;
	}

	bool format_disk() {
		BYTE work[FF_MAX_SS * 2];
		auto res = f_mkfs(_fatvol, nullptr, work, sizeof(work));
		if (res != FR_OK)
			return false;

		res = f_mount(&fs, _fatvol, 1);
		if (res != FR_OK) {
			pr_err("Disk not formatted, err %d\n", res);
			return false;
		}
		pr_trace("Disk formatted\n");
		return true;
	}

	bool update_or_create_file(const std::string_view filename, const std::span<const char> data) {
		return write_file(filename, data);
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		FILINFO fno;

		if (!get_fat_filinfo(filename, fno)) {
			pr_err("Could not read file %s\n", filename.data());
			return;
		}

		fno.fdate = timestamp >> 16;
		fno.ftime = timestamp & 0xFFFF;

		if (f_utime(filename.data(), &fno) != FR_OK)
			pr_err("Could not update timestamp of %s\n", filename.data());
	}

	uint32_t get_file_timestamp(std::string_view filename) {
		FILINFO fno;
		if (!get_fat_filinfo(filename, fno))
			return 0;

		return rawtimestamp(fno);
	}

	uint32_t rawtimestamp(FILINFO &fno) {
		return ((uint32_t)fno.fdate << 16) | (uint32_t)fno.ftime;
	}

	FileInfo get_file_info(std::string_view filename) {
		FILINFO fno;
		if (!get_fat_filinfo(filename, fno))
			return {.size = 0};

		return FileInfo{
			.size = static_cast<uint32_t>(fno.fsize),
			.year = static_cast<uint8_t>(fno.fdate >> 9),			 //top 7 bits are year-1980 1980..2107
			.month = static_cast<uint8_t>((fno.fdate >> 5) & 0x0F),	 //middle 4 bits are month 1..12
			.day = static_cast<uint8_t>(fno.fdate & 0x1F),			 //bottom 5 bits are day 1..31
			.hour = static_cast<uint8_t>(fno.ftime >> 11),			 //top 5 bits are hour 0..23
			.minute = static_cast<uint8_t>((fno.ftime >> 5) & 0x3F), //middle 6 bits are minute 0..59
			.second = static_cast<uint8_t>((fno.ftime & 0x1F) * 2)	 //bottom 5 bits are seconds/2 0..29
		};
	}

	bool get_fat_filinfo(std::string_view filename, FILINFO &fno) {
		f_chdrive(_fatvol);

		auto res = f_stat(filename.data(), &fno);
		if (res != FR_OK) {
			if (!mount_disk())
				return false;

			if (f_stat(filename.data(), &fno))
				return false;
		}
		return true;
	}

	uint32_t read_file(const std::string_view filename, std::span<char> buffer, std::size_t offset = 0) {
		FIL fil;
		UINT bytes_read = 0;

		f_chdrive(_fatvol);

		if (f_open(&fil, filename.data(), FA_OPEN_EXISTING | FA_READ) != FR_OK) {
			if (!mount_disk())
				return 0;

			if (f_open(&fil, filename.data(), FA_OPEN_EXISTING | FA_READ) != FR_OK)
				return 0;
		}

		if (f_lseek(&fil, offset) != FR_OK) {
			f_close(&fil);
			return 0;
		}

		if (f_read(&fil, buffer.data(), buffer.size_bytes(), &bytes_read) != FR_OK) {
			f_close(&fil);
			return 0;
		}

		f_close(&fil);
		return bytes_read;
	}

	uint32_t write_file(const std::string_view filename, std::span<const char> buffer) {
		FIL fil;
		UINT bytes_written = 0;

		f_chdrive(_fatvol);

		if (f_open(&fil, filename.data(), FA_WRITE | FA_CREATE_ALWAYS) != FR_OK) {
			if (!mount_disk())
				return 0;

			if (f_open(&fil, filename.data(), FA_WRITE | FA_CREATE_ALWAYS) != FR_OK)
				return 0;
		}

		auto res = f_write(&fil, buffer.data(), buffer.size_bytes(), &bytes_written);

		f_close(&fil);

		if (res != FR_OK)
			return 0;

		return bytes_written;
	}

	bool delete_file(std::string_view filename) {
		f_chdrive(_fatvol);
		auto res = f_unlink(filename.data());
		if (res != FR_OK)
			return false;

		return true;
	}

	void debug_print_fileinfo(FileInfo info) {
		pr_dbg("Sz: %lu, Tm: %04u/%02u/%02u, %02u:%02u:%02u\n",
			   info.size,
			   info.year + 1980,
			   info.month,
			   info.day,
			   info.hour,
			   info.minute,
			   info.second);
	}

	// Returns false if dir cannot be opened
	bool foreach_file_with_ext(const std::string_view extension, auto action) {
		DIR dj;
		FILINFO fno;

		if (f_opendir(&dj, _fatvol) != FR_OK) {
			if (!mount_disk())
				return false;
			if (f_opendir(&dj, _fatvol) != FR_OK)
				return false;
		}

		while (f_readdir(&dj, &fno) == FR_OK) {
			if (fno.fname[0] == '\0')
				break;
			if (std::string_view{fno.fname}.ends_with(extension)) {
				uint32_t timestamp = rawtimestamp(fno);
				action(fno.fname, timestamp, fno.fsize);
			}
		}
		return true;
	}

	// Returns false if dir cannot be opened
	bool foreach_dir_entry(const std::string_view path, auto action) {
		DIR dj;
		FILINFO fno;

		f_chdrive(_fatvol);

		auto full_path = std::string(path);
		pr_trace("FatFS: scanning dir %s\n", full_path.c_str());

		if (f_opendir(&dj, full_path.c_str()) != FR_OK) {
			if (!mount_disk())
				return false;
			if (f_opendir(&dj, full_path.c_str()) != FR_OK)
				return false;
		}

		while (f_readdir(&dj, &fno) == FR_OK) {
			if (fno.fname[0] == '\0')
				break;
			auto entry_type = (fno.fattrib & AM_DIR) ? DirEntryKind::Dir : DirEntryKind::File;
			uint32_t timestamp = rawtimestamp(fno);

			pr_trace("Found dir entry %s type %d\n", fno.fname, entry_type);

			// std::string file_path = full_path + std::string(fno.fname);
			action(fno.fname, timestamp, fno.fsize, entry_type);
		}
		return true;
	}

	void print_dir(std::string_view path, unsigned max_depth, unsigned cur_depth = 0) {
		pr_dbg("%s/\n", path.data());
		cur_depth++;

		if (cur_depth == max_depth)
			return;

		foreach_dir_entry(path,
						  [=, this](std::string_view filename, uint32_t filesize, uint32_t tmstmp, DirEntryKind kind) {
							  for (auto i = 0u; i < cur_depth; i++)
								  pr_dbg("  ");

							  if (kind == DirEntryKind::File)
								  pr_dbg("%.*s\t%u\t%x\n", filename.size(), filename.data(), filesize, tmstmp);

							  else if (kind == DirEntryKind::Dir) {
								  std::string dirpath = std::string(path) + std::string("/") + std::string(filename);
								  print_dir(dirpath, max_depth, cur_depth);
							  }
						  });
	}
};
