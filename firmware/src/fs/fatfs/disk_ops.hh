#pragma once
#include "diskio.h"
#include <cstdint>

struct DiskOps {
	DiskOps() = default;

	//virtual ~DiskOps() = 0;
	virtual DSTATUS status() = 0;
	virtual DSTATUS initialize() = 0;
	virtual DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) = 0;
	virtual DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) = 0;
	virtual DRESULT ioctl(uint8_t cmd, uint8_t *buff) = 0;
};
