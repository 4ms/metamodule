#include "diskio.h" /* Declarations of disk functions */
#include "ff.h"
#include "ramdisk.h"
#include <cstring>

/* Definitions of physical drive number for each drive */
#define DEV_RAM 0 /* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC 1 /* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB 2 /* Example: Map USB MSD to physical drive 2 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

extern "C" DSTATUS disk_status(BYTE pdrv /* Physical drive number to identify the drive */
) {
	DSTATUS stat;
	int result;

	switch (pdrv) {
		case DEV_RAM:
			return 0;

		case DEV_MMC:
			// result = MMC_disk_status();
			return 0;

		case DEV_USB:
			// result = USB_disk_status();
			return 0;
	}
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv /* Physical drive number to identify the drive */
) {
	DSTATUS stat;
	int result;

	switch (pdrv) {
		case DEV_RAM:
			return 0;

		case DEV_MMC:
			// result = MMC_disk_initialize();
			return 0;

		case DEV_USB:
			// result = USB_disk_initialize();
			return 0;
	}
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(BYTE pdrv,	/* Physical drive number to identify the drive */
				  BYTE *buff,	/* Data buffer to store read data */
				  LBA_t sector, /* Start sector in LBA */
				  UINT count	/* Number of sectors to read */
) {
	DRESULT res;
	int result;

	switch (pdrv) {
		case DEV_RAM:
			std::memcpy(buff, &virtdrive[sector * RamDisk_BlockSize], count * RamDisk_BlockSize);
			return RES_OK;

		case DEV_MMC:
			// result = MMC_disk_read(buff, sector, count);
			return RES_OK;

		case DEV_USB:
			// result = USB_disk_read(buff, sector, count);
			return RES_OK;
	}

	return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(BYTE pdrv,		 /* Physical drive nmuber to identify the drive */
				   const BYTE *buff, /* Data to be written */
				   LBA_t sector,	 /* Start sector in LBA */
				   UINT count		 /* Number of sectors to write */
) {
	DRESULT res;
	int result;

	switch (pdrv) {
		case DEV_RAM:
			std::memcpy(&virtdrive[sector * RamDisk_BlockSize], buff, count * RamDisk_BlockSize);
			return RES_OK;

		case DEV_MMC:
			// result = MMC_disk_write(buff, sector, count);
			return RES_OK;

		case DEV_USB:
			// result = USB_disk_write(buff, sector, count);
			return RES_OK;
	}

	return RES_PARERR;
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
				   BYTE cmd,  /* Control code */
				   void *buff /* Buffer to send/receive control data */
) {
	DRESULT res;
	int result;

	switch (pdrv) {
		case DEV_RAM:
			switch (cmd) {
				case GET_SECTOR_SIZE: // Get R/W sector size (WORD)
					*(WORD *)buff = RamDisk_BlockSize;
					break;
				case GET_BLOCK_SIZE: // Get erase block size in unit of sector (DWORD)
					*(DWORD *)buff = 4;
					break;
				case GET_SECTOR_COUNT:
					*(DWORD *)buff = sizeof(virtdrive) / RamDisk_BlockSize;
					break;
				case CTRL_SYNC:
					break;
				case CTRL_TRIM:
					break;
			}
			return RES_OK;

		case DEV_MMC:
			return RES_OK;

		case DEV_USB:
			return RES_OK;
	}

	return RES_PARERR;
}
