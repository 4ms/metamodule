#pragma once
#include "disk_ops.hh"
#include "printf.h"
#include "volumes.hh"
#include <cstdint>
#include <span>
#include <string_view>

// defined in fatfs/diskio.cc:
bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id);

namespace MetaModule
{

class FatFileIO {
	FATFS fs;
	DiskOps *ops;
	const Volume _vol;
	char _fatvol[3];
	char _volname[8];

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
		: ops{diskops}
		, _vol{vol_id}
		, _fatvol{char(char(_vol) + '0'), ':', '\0'}
		, _volname{'F', 'A', 'T', 'F', 'S', ':', char(char(_vol) + '0'), '\0'} {
		if (!fatfs_register_disk(ops, static_cast<unsigned>(_vol))) {
			printf_("Failed to register FAT FS Disk %d\n", _vol);
		}
		mount_disk();
	}

	bool mount_disk() {
		if (f_mount(&fs, _fatvol, 1) == FR_OK)
			return true;
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

	bool format_disk() {
		BYTE work[FF_MAX_SS * 2];
		auto res = f_mkfs(_fatvol, nullptr, work, sizeof(work));
		if (res != FR_OK)
			return false;

		res = f_mount(&fs, _fatvol, 1);
		if (res != FR_OK) {
			printf_("RamDisk not formatted, err %d\n", res);
			return false;
		}
		printf_("RamDisk formatted\n");
		return true;
	}

	bool update_or_create_file(const std::string_view filename, const std::span<const char> data) {
		return create_file(filename.data(), data.data(), data.size_bytes());
	}

	bool create_file(const char *filename, const char *const data, unsigned sz) {
		FIL fil;
		if (f_chdrive(_fatvol) != FR_OK)
			return false;

		if (f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
			return false;

		UINT bytes_written;
		auto res = f_write(&fil, data, sz, &bytes_written);
		if (res != FR_OK || bytes_written != sz)
			return false;

		f_close(&fil);
		return true;
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		f_chdrive(_fatvol);

		FILINFO fno;
		auto res = f_stat(filename.data(), &fno);
		if (res != FR_OK)
			printf_("Could not read file %s\n", filename.data());
		fno.fdate = timestamp >> 16;
		fno.ftime = timestamp & 0xFFFF;
		res = f_utime(filename.data(), &fno);
		if (res != FR_OK)
			printf_("Could not update timestamp of %s\n", filename.data());
	}

	uint32_t get_file_timestamp(std::string_view filename) {
		f_chdrive(_fatvol);

		FILINFO fno;
		if (f_stat(filename.data(), &fno) != FR_OK) {
			// printf_("Could not read file %s\n", filename.data());
			return 0;
		}
		return rawtimestamp(fno);
	}

	uint32_t rawtimestamp(FILINFO &fno) {
		return ((uint32_t)fno.fdate << 16) | (uint32_t)fno.ftime;
	}

	FileInfo get_file_info(std::string_view filename) {
		f_chdrive(_fatvol);

		FILINFO fno;
		auto res = f_stat(filename.data(), &fno);
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

	uint32_t read_file(const std::string_view filename, std::span<char> buffer) {
		FIL fil;
		UINT bytes_read;
		if (f_chdrive(_fatvol) != FR_OK)
			return 0;

		if (f_open(&fil, filename.data(), FA_OPEN_EXISTING | FA_READ) != FR_OK)
			return 0;

		if (f_read(&fil, buffer.data(), buffer.size_bytes(), &bytes_read) != FR_OK) {
			f_close(&fil);
			return 0;
		}

		f_close(&fil);
		return bytes_read;
	}

	bool delete_file(std::string_view filename) {
		FIL fil;

		f_chdrive(_fatvol);
		auto res = f_unlink(filename.data());
		if (res != FR_OK)
			return false;

		return true;
	}

	void debug_print_fileinfo(FileInfo info) {
		printf_("Sz: %zu, Tm: %04u/%02u/%02u, %02u:%02u:%02u\n",
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

		auto res = f_opendir(&dj, _fatvol);

		if (res != FR_OK)
			return false;

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
};

} // namespace MetaModule
