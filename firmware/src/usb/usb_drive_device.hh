#pragma once

#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "norflashramdisk_ops.hh"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include <functional>

class UsbDriveDevice {

public:
	UsbDriveDevice(NorFlashRamDiskOps &nfs);
	void start();
	static inline USBD_StorageTypeDef ops;

private:
	USBD_HandleTypeDef pdev;

	static inline NorFlashRamDiskOps *nordisk = nullptr;
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
