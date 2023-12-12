#pragma once
#include "disk_ops.hh"
#include "usbh_def.h"
#include "usbh_msc.h"

class MSCOps : public DiskOps {
	USBH_HandleTypeDef &usbh;
	uint32_t scratch[FF_MAX_SS / 4];
	bool is_mounted_ = false;

public:
	enum class Status { NotInit, NotMounted, Mounted };
	Status _status = Status::NotInit;

	MSCOps(MSCOps &other) = delete;

	MSCOps(USBH_HandleTypeDef &usbh)
		: usbh{usbh} {
	}

	DSTATUS status() override {
		return (is_mounted_ && msc_isready()) ? 0 : STA_NODISK;
	}

	DSTATUS initialize() override {
		return (is_mounted_ && msc_isready()) ? 0 : STA_NODISK | STA_NOINIT;
	}

	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
		DRESULT res = RES_ERROR;
		MSC_LUNTypeDef info;
		USBH_StatusTypeDef status = USBH_OK;
		uint8_t lun = 0; //????

		if (((DWORD)dst & 3) || (((HCD_HandleTypeDef *)usbh.pData)->Init.dma_enable)) {
			while ((num_sectors--) && (status == USBH_OK)) {
				status = USBH_MSC_Read(&usbh, lun, sector_start + num_sectors, (uint8_t *)scratch, 1);

				if (status == USBH_OK) {
					memcpy(&dst[num_sectors * FF_MAX_SS], scratch, FF_MAX_SS);
				} else {
					break;
				}
			}
		} else {
			status = USBH_MSC_Read(&usbh, lun, sector_start, dst, num_sectors);
		}

		if (status == USBH_OK) {
			res = RES_OK;
		} else {
			USBH_MSC_GetLUNInfo(&usbh, lun, &info);

			switch (info.sense.asc) {
				case SCSI_ASC_LOGICAL_UNIT_NOT_READY:
				case SCSI_ASC_MEDIUM_NOT_PRESENT:
				case SCSI_ASC_NOT_READY_TO_READY_CHANGE:
					USBH_ErrLog("USB Disk is not ready!");
					res = RES_NOTRDY;
					break;

				default:
					res = RES_ERROR;
					break;
			}
		}

		return res;
	}

	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
		DRESULT res = RES_ERROR;
		MSC_LUNTypeDef info;
		USBH_StatusTypeDef status = USBH_OK;
		uint8_t lun = 0; //????

		if (((DWORD)src & 3) || (((HCD_HandleTypeDef *)usbh.pData)->Init.dma_enable)) {

			while (num_sectors--) {
				memcpy(scratch, &src[num_sectors * FF_MAX_SS], FF_MAX_SS);

				status = USBH_MSC_Write(&usbh, lun, sector_start + num_sectors, (BYTE *)scratch, 1);
				if (status == USBH_FAIL) {
					break;
				}
			}
		} else {
			status = USBH_MSC_Write(&usbh, lun, sector_start, (BYTE *)src, num_sectors);
		}

		if (status == USBH_OK) {
			res = RES_OK;
		} else {
			USBH_MSC_GetLUNInfo(&usbh, lun, &info);

			switch (info.sense.asc) {
				case SCSI_ASC_WRITE_PROTECTED:
					USBH_ErrLog("USB Disk is Write protected!");
					res = RES_WRPRT;
					break;

				case SCSI_ASC_LOGICAL_UNIT_NOT_READY:
				case SCSI_ASC_MEDIUM_NOT_PRESENT:
				case SCSI_ASC_NOT_READY_TO_READY_CHANGE:
					USBH_ErrLog("USB Disk is not ready!");
					res = RES_NOTRDY;
					break;

				default:
					res = RES_ERROR;
					break;
			}
		}

		return res;
	}

	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
		MSC_LUNTypeDef info;
		uint8_t lun = 0; //????

		switch (cmd) {
			case GET_SECTOR_SIZE: // Get R/W sector size (WORD)
				if (USBH_MSC_GetLUNInfo(&usbh, lun, &info) != USBH_OK)
					return RES_ERROR;
				*(DWORD *)buff = info.capacity.block_size;
				break;

			case GET_BLOCK_SIZE: // Get erase block size in unit of sector (DWORD)
				if (USBH_MSC_GetLUNInfo(&usbh, lun, &info) != USBH_OK)
					return RES_ERROR;
				*(DWORD *)buff = info.capacity.block_size / 512;
				break;

			case GET_SECTOR_COUNT:
				if (USBH_MSC_GetLUNInfo(&usbh, lun, &info) != USBH_OK)
					return RES_ERROR;
				*(DWORD *)buff = info.capacity.block_nbr;
				break;

			case MMC_GET_SDSTAT: {
				uint8_t mounted = msc_isready();
				if (mounted)
					is_mounted_ = true;
				*(uint8_t *)buff = mounted;
			} break;

			case CTRL_SYNC:
				break;
			case CTRL_TRIM:
				break;
			case CTRL_EJECT:
				is_mounted_ = false;
				break;

			default:
				return RES_PARERR;
		}
		return RES_OK;
	}

private:
	bool msc_isready() {
		if (usbh.pActiveClass)
			return USBH_MSC_IsReady(&usbh);
		else
			return false;
	}
};
