#pragma once
#include "ramdisk_ops.hh"
#include "usbd_core.h"
#include "usbd_msc.h"

// TODO: make this take any DiskOps *,
// need to make a more generic set_status(Status::Ejected) or something
// instead of Status::RequiresWriteBack
class UsbDriveDevice {

public:
	UsbDriveDevice(RamDiskOps &nfs);
	void start();
	static inline USBD_StorageTypeDef ops;

private:
	USBD_HandleTypeDef pdev;

	static inline RamDiskOps *nordisk = nullptr;
	static int8_t init(uint8_t lun);
	static int8_t eject(uint8_t lun);
	static int8_t get_capacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
	static int8_t read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
	static int8_t write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
	static int8_t get_max_lun();
	static int8_t is_ready(uint8_t lun);
	static int8_t is_write_protected(uint8_t lun);

	//SDMMC, lun 1:
	//TODO
};
