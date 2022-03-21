#include "norfs.hh"
#include "conf/qspi_flash_conf.hh"
#include "ff.h"
#include "printf.h"
#include <cstdint>
#include <cstring>

// Defined in diskio.cc
void register_norfs(NorFlashFS *nfs, uint8_t drive_num);

NorFlashFS::NorFlashFS(std::string_view v)
	: flash{qspi_patchflash_conf}
	, vol{v} {
	if (vol[0] < '0' || vol[0] > '3')
		register_norfs(this, vol[0] - '0');
	else 
		printf("Invalid volume number for NorFlashFS: %s", vol.data());
}

bool NorFlashFS::init() {
	uint32_t timeout = 100;
	uint32_t id = 0;

	do {
		HAL_Delay(1);
		flash.read_chip_id(&id);
		id &= 0x00FFFFFF;
		if (id == 0x186001)
			return true;
	} while (timeout--);
	// printf("read %d\r\n", id);
	return false;
}

bool NorFlashFS::startfs() {
	flash.read(ramdisk.virtdrive, 0, qspi_patchflash_conf.flash_size_bytes, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
	auto res = f_mount(&fs, vol.data(), 1);
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
			if (word != *(uint32_t *)(&ramdisk.virtdrive[ramptr])) {
				sector_modified = true;
				break;
			}
			ramptr += 4;
		}
		if (sector_modified) {
			//printf("Sector %d modified in RAM, writing to flash\r\n", sector_num);
			auto ok = flash.erase(SectorSize, sector_start, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Erase failed.\r\n");
				return;
			}
			ok = flash.write(&ramdisk.virtdrive[sector_start], sector_start, SectorSize);
			if (!ok) {
				printf("Write failed.\r\n");
				return;
			}
		} else {
			//	printf("Sector %d not modified.\r\n", sector_num);
		}
	}
}

bool NorFlashFS::make_fs() {
	BYTE work[FF_MAX_SS * 2];
	auto res = f_mkfs(vol.data(), nullptr, work, sizeof work);
	if (res != FR_OK)
		return false;

	res = f_mount(&fs, vol.data(), 1);
	if (res != FR_OK)
		return false;

	return res == FR_OK;
}

void NorFlashFS::read_bytes(uint8_t *data, uint32_t address, uint32_t bytes) {
	std::memcpy(data, &ramdisk.virtdrive[address], bytes);
}

void NorFlashFS::read_sectors(uint8_t *data, uint32_t sector, uint32_t sector_count) {
	read_bytes(data, sector * ramdisk.BlockSize, sector_count * ramdisk.BlockSize);
}

void NorFlashFS::write(const uint8_t *const data, uint32_t address, uint32_t bytes) {
}
void NorFlashFS::write_sectors(const uint8_t *const data, uint32_t sector, uint32_t sector_count) {
}

bool NorFlashFS::create_file(const char *filename, const std::span<const unsigned char> data) {
	return create_file(filename, data.data(), data.size_bytes());
}

bool NorFlashFS::create_file(const char *filename, const unsigned char *data, unsigned sz) {
	FIL fil;
	{
		TCHAR fn[FF_LFN_BUF];
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

static void u8_to_tchar(const char *u8, TCHAR *uint) {
	do {
		*uint++ = *u8++;
	} while (*u8 != '\0');
}
