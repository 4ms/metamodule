#pragma once
#include "disk_ops.hh"
#include "qspi_flash_driver.hh"
#include "ramdisk.hh"

class NorFlashRamDiskOps : public DiskOps {
public:
	static constexpr uint32_t RamDiskSizeBytes = 16 * 1024 * 1024;
	static constexpr uint32_t RamDiskBlockSize = 512;
	enum class Status { NotInit, InUse, NotInUse, RequiresWriteBack };

	NorFlashRamDiskOps(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk);
	~NorFlashRamDiskOps() override;

	DSTATUS get_status() override;
	DSTATUS initialize() override;
	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override;
	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override;
	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override;

	bool unmount() override;

private:
	mdrivlib::QSpiFlash flash;
	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk;
	Status _status = Status::NotInit;
};
