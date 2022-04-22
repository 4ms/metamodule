#include "norflashramdisk_ops.hh"
#include "conf/qspi_flash_conf.hh"
#include "printf.h"
#include <cstring>

static constexpr auto Foreground = mdrivlib::QSpiFlash::EXECUTE_FOREGROUND;

NorFlashRamDiskOps::NorFlashRamDiskOps(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk)
	: flash{qspi_patchflash_conf}
	, ramdisk{rmdisk}
	, flash_offset{qspi_patchflash_conf.flash_size_bytes - RamDiskSizeBytes} {
}

NorFlashRamDiskOps::~NorFlashRamDiskOps() = default;

DSTATUS NorFlashRamDiskOps::status() {
	//STA_NOINIT
	//STA_NODISK
	//STA_PROTECT
	return (_status == Status::NotInit) ? (STA_NOINIT | STA_NODISK) : 0;
}

NorFlashRamDiskOps::Status NorFlashRamDiskOps::get_status() {
	return _status;
}

void NorFlashRamDiskOps::set_status(Status status) {
	_status = status;
}

// Get the RamDisk ready for IO.
// Makes sure QSPI chip is responding, then loads the NorFlash contents into the RamDisk
//
// FatFS calls this in f_mkfs(), and when it mounts the disk (in f_mount(_,_,1) or the first time FatFS attempts a read/write/stat if the disk is not yet mounted)
DSTATUS NorFlashRamDiskOps::initialize() {
	printf("NorFlashRamDiskOps initialize\n");
	if (_status == Status::NotInit) {
		if (!flash.check_chip_id(0x182001, 0x00FFBFFF)) { //S25FL127S(p7):182001 or S25FL128L(p6):186001
			printf("ERROR: NOR Flash returned wrong id\n");
			return STA_NOINIT | STA_NODISK;
		}

		if (flash.read(ramdisk.virtdrive, flash_offset, RamDiskSizeBytes, Foreground)) {
			// if (flash.read(ramdisk.virtdrive, 0, qspi_patchflash_conf.flash_size_bytes, Foreground)) {
			set_status(Status::NotInUse);
			return 0;
		}
		printf("NorFlashRamDiskOps read failed\n");
		return STA_NOINIT;
	}
	printf("NorFlashRamDiskOps already init\n");
	return 0;
}

DRESULT NorFlashRamDiskOps::read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) {
	printf("reading at %d for %d sectors..\n", sector_start, num_sectors);
	const uint32_t address = sector_start * RamDiskBlockSize;
	const uint32_t bytes = num_sectors * RamDiskBlockSize;
	if (address >= RamDiskSizeBytes || (address + bytes) >= RamDiskSizeBytes)
		return RES_ERROR;

	std::memcpy(dst, &ramdisk.virtdrive[address], bytes);
	return RES_OK;
}

DRESULT NorFlashRamDiskOps::write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) {
	printf("writing at %d for %d sectors...\n", sector_start, num_sectors);
	const uint32_t address = sector_start * RamDiskBlockSize;
	const uint32_t bytes = num_sectors * RamDiskBlockSize;
	if (address >= RamDiskSizeBytes || (address + bytes) >= RamDiskSizeBytes)
		return RES_ERROR;

	std::memcpy(&ramdisk.virtdrive[address], src, bytes);
	return RES_OK;
}

DRESULT NorFlashRamDiskOps::ioctl(uint8_t cmd, uint8_t *buff) {
	switch (cmd) {
		case GET_SECTOR_SIZE: // Get R/W sector size (WORD)
			*(WORD *)buff = RamDiskBlockSize;
			break;
		case GET_BLOCK_SIZE: // Get erase block size in unit of sector (DWORD)
			*(DWORD *)buff = 8;
			break;
		case GET_SECTOR_COUNT:
			*(DWORD *)buff = RamDiskSizeBytes / RamDiskBlockSize;
			break;
		case CTRL_SYNC:
			break;
		case CTRL_TRIM:
			break;
		case CTRL_EJECT:
			return unmount() ? RES_OK : RES_ERROR;
			break;
	}
	return RES_OK;
}

bool NorFlashRamDiskOps::unmount() {
	// printf("NOR writeback disabled\r\n");
	// return true;

	constexpr uint32_t SectorSize = QSPI_SECTOR_SIZE;
	constexpr uint32_t NumSectors = RamDiskSizeBytes / SectorSize;
	uint32_t sector[SectorSize / 4];
	auto *sector_u8 = (uint8_t *)sector;

	for (uint32_t sector_num = 0; sector_num < NumSectors; sector_num++) {
		const uint32_t flash_start_addr = sector_num * SectorSize + flash_offset;
		const uint32_t ram_start_addr = sector_num * SectorSize;

		if (!flash.read(sector_u8, flash_start_addr, SectorSize, Foreground)) {
			printf("Error reading sector %d\r\n", sector_num);
			return false;
		}

		bool sector_modified = false;
		uint32_t cur_ram_addr = ram_start_addr;
		for (auto word : sector) {
			if (word != *(uint32_t *)(&ramdisk.virtdrive[cur_ram_addr])) {
				sector_modified = true;
				break;
			}
			cur_ram_addr += 4;
		}
		if (sector_modified) {
			printf("Sector %d modified in RAM, erasing...", sector_num);
			auto ok = flash.erase(SectorSize, flash_start_addr, Foreground);
			if (!ok) {
				printf("Erase failed.\r\n");
				return false;
			}
			printf("Writing...");
			ok = flash.write(&ramdisk.virtdrive[ram_start_addr], flash_start_addr, SectorSize);
			if (!ok) {
				printf("Write failed.\r\n");
				return false;
			}
			printf("Done\r\n");
		} else {
			//	printf("Sector %d not modified.\r\n", sector_num);
		}
	}
	printf("Done writing back to flash\r\n");
	set_status(Status::NotInit);
	return true;
}
