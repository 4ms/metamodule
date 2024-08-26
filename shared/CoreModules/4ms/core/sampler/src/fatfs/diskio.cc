#include "diskio.h" /* Declarations of disk functions */
#include "disk_ops.hh"
#include "drivers/stm32xx.h"
#include "ff.h"
#include <array>


constexpr unsigned MaxNumDisks = 4;

namespace
{
std::array<DiskOps *, MaxNumDisks> _diskops{nullptr, nullptr, nullptr, nullptr};
}

extern "C" uint32_t get_fattime() { return HAL_GetTick(); }

// Register a set of disk operations with the FatFS filesystem.
// Returns false if failed: disk_id is already taken or out of range.
bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id) {
	if (disk_id >= MaxNumDisks)
		return false;
	if (_diskops[disk_id] != nullptr)
		return false;
	if (!ops)
		return false;

	_diskops[disk_id] = ops;
	return true;
}

extern "C" DSTATUS disk_status(BYTE pdrv) {
	if (pdrv >= MaxNumDisks || !_diskops[pdrv])
		return STA_NOINIT;

	return _diskops[pdrv]->status();
}

extern "C" DSTATUS disk_initialize(BYTE pdrv) {
	if (pdrv >= MaxNumDisks || !_diskops[pdrv])
		return STA_NOINIT;

	return _diskops[pdrv]->initialize();
}

extern "C" DRESULT disk_read(BYTE pdrv,	   /* Physical drive number to identify the drive */
							 BYTE *buff,   /* Data buffer to store read data */
							 LBA_t sector, /* Start sector in LBA */
							 UINT count	   /* Number of sectors to read */
) {
	if (pdrv >= MaxNumDisks || !_diskops[pdrv])
		return RES_PARERR;

	return _diskops[pdrv]->read(buff, sector, count);
}

#if FF_FS_READONLY == 0

extern "C" DRESULT disk_write(BYTE pdrv,		/* Physical drive nmuber to identify the drive */
							  const BYTE *buff, /* Data to be written */
							  LBA_t sector,		/* Start sector in LBA */
							  UINT count		/* Number of sectors to write */
) {
	if (pdrv >= MaxNumDisks || !_diskops[pdrv])
		return RES_PARERR;

	return _diskops[pdrv]->write(buff, sector, count);
}

#endif

extern "C" DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
							  BYTE cmd,	 /* Control code */
							  void *buff /* Buffer to send/receive control data */
) {
	if (pdrv >= MaxNumDisks || !_diskops[pdrv])
		return RES_PARERR;

	return _diskops[pdrv]->ioctl(cmd, (uint8_t *)buff);
}
