#include "norfs.hh"
#include "conf/qspi_flash_conf.hh"
#include "ff.h"
#include "ramdisk.h"

NorFlashFS::NorFlashFS()
	: flash{qspi_patchflash_conf} {
}

void NorFlashFS::init() {
	uint32_t id;
	flash.read_chip_id(&id);
}

bool NorFlashFS::startfs() {
	flash.Read(virtdrive, 0, qspi_patchflash_conf.flash_size_bytes, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
	auto res = f_mount(fs, vol, 1);
	return res == FR_OK;
}

bool NorFlashFS::make_default_fs() {
	BYTE work[FF_MAX_SS * 2];
	auto res = f_mkfs(vol, nullptr, work, sizeof work);
	if (res != FR_OK)
		return false;

	res = f_mount(fs, vol, 1);
	if (res != FR_OK)
		return false;

	return res == FR_OK;
}

bool NorFlashFS::create_file(const char* filename, const unsigned char *data, unsigned sz) {
// bool NorFlashFS::create_file(const char* filename, const std::span<unsigned char> &data) {
	FIL fil;
	{
		TCHAR fn[FF_LFN_BUF];
		u8_to_tchar(filename, fn);
		auto res = f_open(&fil, fn, FA_CREATE_ALWAYS | FA_WRITE);
		if (res != FR_OK)
			return false;
	}
	{
		UINT bytes_written;
		auto res = f_write(&fil, data, sz, &bytes_written);
		if (res != FR_OK || bytes_written != sz)
			return false;
	}
	return true;
}
