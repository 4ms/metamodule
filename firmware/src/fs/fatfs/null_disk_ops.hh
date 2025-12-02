#include "disk_ops.hh"

struct NullDiskOps : DiskOps {
	NullDiskOps() = default;
	~NullDiskOps() = default;

	DSTATUS status() override {
		return STA_NODISK;
	}
	DSTATUS initialize() override {
		return STA_NODISK;
	}
	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
		return RES_NOTRDY;
	}
	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
		return RES_NOTRDY;
	}
	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
		return RES_NOTRDY;
	}
};
