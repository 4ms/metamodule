
#include "usbd_msc_storage.h"
#include "ramdisk.h"
#include <cstring>

static int8_t RamDisk_Init(uint8_t lun);
static int8_t RamDisk_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t RamDisk_IsReady(uint8_t lun);
static int8_t RamDisk_IsWriteProtected(uint8_t lun);
static int8_t RamDisk_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t RamDisk_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t RamDisk_GetMaxLun();
static int8_t RamDisk_Eject(uint8_t lun);

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
	.len = STANDARD_INQUIRY_DATA_LEN - 5,
	.manuf = "4ms    ",
	.product = "MetaModule     ",
	.version = {'0', '.', '0', '1'},
};

// static uint8_t RamDisk_Inquirydata[] = /* 36 */
// 	{
// 		// clang-format off
// 		/* LUN 0 */
// 		0x00, 0x80, 0x02, 0x02,
// 		(STANDARD_INQUIRY_DATA_LEN - 5), 0x00, 0x00, 0x00,
// 		'4', 'm', 's', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
// 		'M', 'e', 't', 'a', 'M', 'o', 'd', 'u', /* Product      : 16 Bytes */
// 		'l', 'e', ' ', ' ', ' ', ' ', ' ', ' ',
// 		'0', '.', '0', '1', 					 /* Version      : 4 Bytes */
// 		// clang-format on
// };

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

static int8_t RamDisk_Init(uint8_t lun) {
	RamDisk_SetStatus(Connected);
	return USBD_OK;
}

static int8_t RamDisk_Eject(uint8_t lun) {
	RamDisk_SetStatus(Disconnected);
	return USBD_OK;
}

static int8_t RamDisk_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) {
	*block_num = RamDisk_NumBlocks;
	*block_size = RamDisk_BlockSize;
	return (USBD_OK);
}

static int8_t RamDisk_IsReady(uint8_t lun) {
	return USBD_OK;
}

static int8_t RamDisk_IsWriteProtected(uint8_t lun) {
	return USBD_OK;
}

static int8_t RamDisk_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	std::memcpy(buf, &virtdrive[blk_addr * RamDisk_BlockSize], blk_len * RamDisk_BlockSize);
	// for (uint16_t i = 0; i < (blk_len * RamDisk_BlockSize); i++)
	// 	buf[i] = virtdrive[blk_addr * RamDisk_BlockSize + i];
	return USBD_OK;
}

static int8_t RamDisk_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	std::memcpy(&virtdrive[blk_addr * RamDisk_BlockSize], buf, blk_len * RamDisk_BlockSize);
	// for (uint16_t i = 0; i < (blk_len * RamDisk_BlockSize); i++)
	// 	virtdrive[blk_addr * RamDisk_BlockSize + i] = buf[i];
	return USBD_OK;
}

static int8_t RamDisk_GetMaxLun() {
	return 0; //1 unit
}
