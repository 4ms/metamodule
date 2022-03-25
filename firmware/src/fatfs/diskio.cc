#include "diskio.h" /* Declarations of disk functions */
#include "ff.h"
#include "norfs.hh"
#include <cstring>

// default values
uint32_t DriveRamDisk = 0;
uint32_t DriveSDCard = 1;
uint32_t DriveUSB = 2;

static NorFlashFS *norfs = nullptr;
void register_norfs(NorFlashFS *nfs, uint8_t drive_num) {
	norfs = nfs;
	DriveRamDisk = drive_num;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

extern "C" DSTATUS disk_status(BYTE pdrv) {
	if (pdrv == DriveRamDisk) {
		return 0;
	}

	else if (pdrv == DriveSDCard)
	{
		return 0;
	}

	else if (pdrv == DriveUSB)
	{
		return 0;
	}

	else
		return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv) {
	if (pdrv == DriveRamDisk) {
		return 0;
	}

	else if (pdrv == DriveSDCard)
	{
		return 0;
	}

	else if (pdrv == DriveUSB)
	{
		return 0;
	}

	else
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
	if (pdrv == DriveRamDisk) {
		if (!norfs)
			return RES_NOTRDY;
		norfs->read_sectors(buff, sector, count);
		return RES_OK;
	}

	else if (pdrv == DriveSDCard)
	{
		return RES_OK;
	}

	else if (pdrv == DriveUSB)
	{
		return RES_OK;
	}

	else
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
	if (pdrv == DriveRamDisk) {
		if (!norfs)
			return RES_NOTRDY;
		norfs->write_sectors(buff, sector, count);
		return RES_OK;
	}

	else if (pdrv == DriveSDCard)
	{
		return RES_OK;
	}

	else if (pdrv == DriveUSB)
	{
		return RES_OK;
	}

	else
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
	if (pdrv == DriveRamDisk) {
		switch (cmd) {
			case GET_SECTOR_SIZE: // Get R/W sector size (WORD)
				*(WORD *)buff = norfs->RamDiskBlockSize;
				break;
			case GET_BLOCK_SIZE: // Get erase block size in unit of sector (DWORD)
				*(DWORD *)buff = 8;
				break;
			case GET_SECTOR_COUNT:
				*(DWORD *)buff = norfs->RamDiskSizeBytes / norfs->RamDiskBlockSize;
				break;
			case CTRL_SYNC:
				break;
			case CTRL_TRIM:
				break;
		}
		return RES_OK;
	}

	else if (pdrv == DriveSDCard)
	{
		return RES_OK;
	}

	else if (pdrv == DriveUSB)
	{
		return RES_OK;
	}

	else
		return RES_PARERR;
}
