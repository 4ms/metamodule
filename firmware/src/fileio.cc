#include "fileio.hh"
#include "ff.h"
#include "printf.h"

//defined in diskio.cc, but we don't have access to modify diskio.h
bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id);

namespace MetaModule::FileIO
{

namespace
{
FATFS fs;
}

bool register_disk(DiskOps *ops, Disk disk) {
	if (disk == Disk::NORFlash) {
		if (!fatfs_register_disk(ops, 0)) {
			printf("Failed to register NOR Flash RamDisk ops\r\n");
			return false;
		}
	} else {
		printf("Cannot register: unknown disk\r\n");
		return false;
	}
	return true;
}

bool mount_disk(Disk disk) {
	char vol[3];
	vol_string(disk, vol);
	if (f_mount(&fs, vol, 1))
		return true;
	return false;
}

bool unmount_disk(Disk disk) {
	auto disk_id = static_cast<uint8_t>(disk);
	return (disk_ioctl(disk_id, CTRL_EJECT, nullptr) == RES_OK);
}

void vol_string(Disk disk, char vol[3]) {
	auto disk_id = static_cast<uint8_t>(disk);
	char disk_char = disk_id + '0';
	vol[0] = disk_char;
	vol[1] = ':';
	vol[2] = '\0';
}

bool format_disk(Disk disk) {
	char vol[3];
	vol_string(disk, vol);

	BYTE work[FF_MAX_SS * 2];
	auto res = f_mkfs(vol, nullptr, work, sizeof(work));
	if (res != FR_OK)
		return false;

	res = f_mount(&fs, vol, 1);
	return res == FR_OK;
}

bool create_file(const char *filename, const std::span<const unsigned char> data) {
	return create_file(filename, data.data(), data.size_bytes());
}

bool create_file(const char *filename, const unsigned char *data, unsigned sz) {
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

uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes) {
	FIL fil;
	FILINFO fileinfo;
	uint32_t bytes_to_read;
	UINT bytes_read;
	{
		auto res = f_stat(filename.data(), &fileinfo);
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
	f_close(&fil);

	return bytes_read;
}

static void u8_to_tchar(const char *u8, TCHAR *uint) {
	do {
		*uint++ = *u8++;
	} while (*u8 != '\0');
}

} // namespace MetaModule::FileIO
