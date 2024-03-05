#pragma once
#include "conf/ramdisk_conf.hh"
#include "disk_ops.hh"
#include "fs/ramdisk.hh"
#include "pr_dbg.hh"
#include <cstring>

class RamDiskOps : public DiskOps {
public:
	static constexpr uint32_t SizeBytes = RamDiskSizeBytes;
	static constexpr uint32_t BlockSize = RamDiskBlockSize;
	enum class Status { NotInit, InUse, NotInUse, Mounted, Unmounted, WritingBack };

	RamDiskOps(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk)
		: ramdisk{rmdisk} {
	}

	DSTATUS status() override {
		return 0;
		// return (_status == Status::NotInit) ? (STA_NOINIT | STA_NODISK) : 0;
	}

	Status get_status() {
		return _status;
	}

	void set_status(Status status) {
		_status = status;
	}

	// FatFS calls this :
	// - in f_mkfs(),
	// - and when it mouts the disk in f_mount(_,_,1)
	// - and the first time FatFS attempts a read/write/stat if the disk is not yet mounted
	DSTATUS initialize() override {
		_status = Status::Mounted;
		return 0;
	}

	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
		const uint32_t address = sector_start * RamDiskBlockSize;
		const uint32_t bytes = num_sectors * RamDiskBlockSize;
		if (address >= RamDiskSizeBytes || (address + bytes) > RamDiskSizeBytes) {
			pr_err("Attempt to read out of RamDisk bounds: 0x%x + 0x%x\n", address, bytes);
			return RES_ERROR;
		}

		std::memcpy(dst, &ramdisk.virtdrive[address], bytes);
		return RES_OK;
	}

	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
		const uint32_t address = sector_start * RamDiskBlockSize;
		const uint32_t bytes = num_sectors * RamDiskBlockSize;
		if (address >= RamDiskSizeBytes || (address + bytes) > RamDiskSizeBytes) {
			pr_err("Attempt to write out of RamDisk bounds: 0x%x + 0x%x\n", address, bytes);
			return RES_ERROR;
		}

		std::memcpy(&ramdisk.virtdrive[address], src, bytes);
		return RES_OK;
	}

	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
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
				break;

			case MMC_GET_SDSTAT:
				*(uint8_t *)buff = 1;
				break;

			default:
				return RES_PARERR;
		}
		return RES_OK;
	}

private:
	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk;
	Status _status = Status::NotInit;
};
