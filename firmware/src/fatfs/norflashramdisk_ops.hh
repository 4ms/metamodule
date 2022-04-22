#pragma once
#include "conf/ramdisk_conf.hh"
#include "disk_ops.hh"
#include "qspi_flash_driver.hh"
#include "ramdisk.hh"

class NorFlashRamDiskOps : public DiskOps {
public:
	static constexpr uint32_t SizeBytes = RamDiskSizeBytes;
	static constexpr uint32_t BlockSize = RamDiskBlockSize;
	enum class Status { NotInit, InUse, NotInUse, RequiresWriteBack };

	NorFlashRamDiskOps(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk);
	~NorFlashRamDiskOps();

	DSTATUS status() override;
	DSTATUS initialize() override;
	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override;
	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override;
	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override;

	bool unmount() override;
	void set_status(Status status);
	Status get_status();

private:
	mdrivlib::QSpiFlash flash;
	const uint32_t flash_offset;
	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk;
	Status _status = Status::NotInit;
};
