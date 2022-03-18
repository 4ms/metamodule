#include "norfs.hh"
#include "conf/qspi_flash_conf.hh"
#include "ff.h"
#include "printf.h"
#include "ramdisk.h"
#include <cstdint>

NorFlashFS::NorFlashFS()
	: flash{qspi_patchflash_conf} {
}

void NorFlashFS::init() {
	uint32_t id;
	flash.read_chip_id(&id);
}

bool NorFlashFS::startfs() {
	flash.read(virtdrive, 0, qspi_patchflash_conf.flash_size_bytes, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
	auto res = f_mount(&fs, vol, 1);
	return res == FR_OK;
}

void NorFlashFS::stopfs() {
	constexpr uint32_t SectorSize = 4096;
	constexpr uint32_t NumSectors = qspi_patchflash_conf.flash_size_bytes / SectorSize;
	uint32_t sector[SectorSize / 4];
	auto *sector8 = (uint8_t *)sector;

	for (uint32_t sector_num = 0; sector_num < NumSectors; sector_num++) {
		uint32_t sector_start = sector_num * SectorSize;
		uint32_t ramptr = sector_start;

		flash.read(sector8, sector_num, SectorSize, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);

		bool sector_modified = false;
		for (auto word : sector) {
			if (word != *(uint32_t *)(&virtdrive[ramptr])) {
				sector_modified = true;
				break;
			}
			ramptr += 4;
		}
		if (sector_modified) {
			printf("Sector %d modified in RAM, writing to flash\r\n", sector_num);
			auto ok = flash.erase(SectorSize, sector_start, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Erase failed.\r\n");
				return;
			}
			ok = flash.write(&virtdrive[sector_start], sector_start, SectorSize);
			if (!ok) {
				printf("Write failed.\r\n");
				return;
			}
		} else {
			printf("Sector %d not modified.\r\n", sector_num);
		}
	}
}

bool NorFlashFS::make_fs() {
	BYTE work[FF_MAX_SS * 2];
	auto res = f_mkfs(vol, nullptr, work, sizeof work);
	if (res != FR_OK)
		return false;

	res = f_mount(&fs, vol, 1);
	if (res != FR_OK)
		return false;

	return res == FR_OK;
}

bool NorFlashFS::create_file(const char *filename, const std::span<const unsigned char> data) {
	return create_file(filename, data.data(), data.size_bytes());
}

bool NorFlashFS::create_file(const char *filename, const unsigned char *data, unsigned sz) {
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
	{
		auto res = f_close(&fil);
		if (res != FR_OK)
			return false;
	}

	return true;
}
