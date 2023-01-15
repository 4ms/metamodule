#pragma once
#include "disk_ops.hh"
#include "printf.h"
#include <cstdint>
#include <span>
#include <string_view>

namespace MetaModule
{

enum class DiskID { RamDisk = 0, SDCard = 1 };

template<typename Ops, DiskID disk>
class FatFileIO {
	FATFS fs;
	Ops ops;
	char vol[3];

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

	FatFileIO() {
		if (!fatfs_register_disk(ops, 0)) {
			printf_("Failed to register FAT FS Disk %d\n", disk);
		}
		vol_string(vol);
	}

	FatFileIO(auto ops_params)
		: ops{ops_params} {
		if (!fatfs_register_disk(ops, 0)) {
			printf_("Failed to register FAT FS Disk %d\n", disk);
		}
	}

	bool mount_disk() {
		if (f_mount(&fs, vol, 1) == FR_OK)
			return true;
		return false;
	}

	bool unmount_disk() {
		auto disk_id = static_cast<uint8_t>(disk);
		return (disk_ioctl(disk_id, CTRL_EJECT, nullptr) == RES_OK);
	}

	void vol_string(char vol[3]) {
		auto disk_id = static_cast<uint8_t>(disk);
		char disk_char = disk_id + '0';
		vol[0] = disk_char;
		vol[1] = ':';
		vol[2] = '\0';
	}

	bool format_disk() {
		BYTE work[FF_MAX_SS * 2];
		auto res = f_mkfs(vol, nullptr, work, sizeof(work));
		if (res != FR_OK)
			return false;

		res = f_mount(&fs, vol, 1);
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

	bool create_file(const char *filename, const std::span<const char> data) {
		return create_file(filename, data.data(), data.size_bytes());
	}

	bool create_file(const char *filename, const char *data, unsigned sz) {
		FIL fil;
		{
			// TCHAR fn[FF_LFN_BUF];
			// u8_to_tchar(filename, fn);
			auto res = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);
			if (res != FR_OK)
				return false;
		}
		{
			UINT bytes_written;
			auto res = f_write(&fil, data, sz, &bytes_written);
			if (res != FR_OK || bytes_written != sz)
				return false;
		}
		{
			auto res = f_close(&fil);
			if (res != FR_OK)
				return false;
		}

		return true;
	}

	void set_file_rawtimestamp(std::string_view filename, uint32_t timestamp) {
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

	uint32_t get_file_rawtimestamp(std::string_view filename) {
		FILINFO fno;
		if (f_stat(filename.data(), &fno) != FR_OK) {
			printf_("Could not read file %s\n", filename.data());
			return 0;
		}
		return ((uint32_t)fno.fdate << 16) | (uint32_t)fno.ftime;
	}

	FileInfo get_file_info(std::string_view filename) {
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

	uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes) {
		FIL fil;
		FILINFO fileinfo;
		uint32_t bytes_to_read;
		UINT bytes_read;
		{
			auto res = f_stat(filename.data(), &fileinfo);
			auto &fno = fileinfo;
			bytes_to_read = std::min((uint32_t)fileinfo.fsize, max_bytes);
			if (res != FR_OK)
				return 0;
		}
		{
			auto res = f_open(&fil, filename.data(), FA_OPEN_EXISTING | FA_READ);
			if (res != FR_OK)
				return 0;
		}
		{
			auto res = f_read(&fil, data, bytes_to_read, &bytes_read);
			if (res != FR_OK)
				return 0;
		}
		if (bytes_to_read != bytes_read)
			printf_("Warning: Supposed to read %d, actually read %d\n", bytes_to_read, bytes_read);
		f_close(&fil);

		return bytes_read;
	}

	bool delete_file(const char *filename) {
		FIL fil;
		auto res = f_unlink(filename);
		if (res != FR_OK)
			return false;

		return true;
	}

	static void u8_to_tchar(const char *u8, TCHAR *uint) {
		do {
			*uint++ = *u8++;
		} while (*u8 != '\0');
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

	template<typename Action>
	// requires(Action a, const char *chr) {a(chr);}
	void for_each_file_regex(std::string_view regex, Action action) {
		DIR dj;
		FILINFO fileinfo;
		auto res = f_findfirst(&dj, &fileinfo, "", regex.data());
		while (res == FR_OK && fileinfo.fname[0]) {
			action(fileinfo.fname);
			res = f_findnext(&dj, &fileinfo);
		}
	}

	template<typename Action>
	void for_each_file_with_ext(const std::string_view extension, Action action) {
		DIR dj;
		FILINFO fno;
		auto res = f_opendir(&dj, vol);
		//rewind dir?
		if (res != FR_OK)
			return;
		while (res == FR_OK && fno.fname[0]) {
		}

		do {
			res = f_readdir(&dj, &fno);
			if (res == FR_OK && std::string_view{fno.fname}.ends_with(extension)) {
				action(fno.fname, fno.ftime);
			}
		} while (res == FR_OK && fno.fname[0]);
	}
};

} // namespace MetaModule
