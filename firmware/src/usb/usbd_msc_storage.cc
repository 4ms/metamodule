
#include "usbd_msc_storage.h"
#include "norfs.hh"
#include <cstring>

static NorFlashFS *norfs = nullptr;
void usbd_msc_register_norfs(NorFlashFS *nfs) {
	norfs = nfs;
}

//TODO: Add SD Card as a second lun (or add each partition as a lun)

struct InquiryData {
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint32_t len;
	char manuf[8];
	char product[16];
	char version[4];
};

InquiryData RamDisk_Inquirydata = {
	.a = 0,
	.b = 0x80,
	.c = 0x02,
	.d = 0x02,
	.len = sizeof(InquiryData) - 5,
 	.manuf = {'4', 'm', 's', ' ', ' ', ' ', ' ', ' '},
 	.product = {'M', 'e', 't', 'a', 'M', 'o', 'd', 'u', 'l', 'e', ' ', ' ', ' ', ' ', ' ', ' '},
 	.version = {'0', '.', '0', '1'},
	// .manuf = "4ms",
	// .product = "MetaModule",
	// .version = {'0', '.', '0', '1'},
};

static int8_t RamDisk_Init(uint8_t lun) {
	if (lun == 0) {
		norfs->set_status(NorFlashFS::Status::InUse);
	}
	return USBD_OK;
}

static int8_t RamDisk_Eject(uint8_t lun) {
	if (lun == 0) {
		norfs->set_status(NorFlashFS::Status::NotInUse);
		norfs->stopfs();
	}
	return USBD_OK;
}

static int8_t RamDisk_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) {
	if (lun == 0) {
		*block_num = norfs->RamDiskSizeBytes / norfs->RamDiskBlockSize;
		*block_size = norfs->RamDiskBlockSize;
	}
	return (USBD_OK);
}

static int8_t RamDisk_IsReady(uint8_t lun) {
	return USBD_OK;
}

static int8_t RamDisk_IsWriteProtected(uint8_t lun) {
	return USBD_OK;
}

static int8_t RamDisk_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun == 0) {
		norfs->read_sectors(buf, blk_addr, blk_len);
	}
	return USBD_OK;
}

static int8_t RamDisk_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun == 0) {
		norfs->write_sectors(buf, blk_addr, blk_len);
	}
	return USBD_OK;
}

static int8_t RamDisk_GetMaxLun() {
	return 0; //1 unit
}

USBD_StorageTypeDef USBD_MSC_fops = {
	RamDisk_Init,
	RamDisk_GetCapacity,
	RamDisk_IsReady,
	RamDisk_IsWriteProtected,
	RamDisk_Read,
	RamDisk_Write,
	RamDisk_GetMaxLun,
	reinterpret_cast<int8_t*>(&RamDisk_Inquirydata),
	RamDisk_Eject,
};
