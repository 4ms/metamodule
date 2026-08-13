#pragma once
#include "usb/dev_drive_block.hh"
#include "usbd_core.h"
#include "usbd_msc.h"

namespace MetaModule
{

// MSC interface for the developer-mode drive
//
class UsbDriveDevice {
public:
	explicit UsbDriveDevice(DevDriveBlock &block);

	// Add the class to the composite device being built
	void register_class(USBD_HandleTypeDef *pdev);

	static USBD_StorageTypeDef ops;

private:
	static int8_t init(uint8_t lun);
	static int8_t get_capacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
	static int8_t is_ready(uint8_t lun);
	static int8_t is_write_protected(uint8_t lun);
	static int8_t read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
	static int8_t write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
	static int8_t get_max_lun();
	static int8_t eject(uint8_t lun);
	static int8_t medium_changed(uint8_t lun);

	static inline DevDriveBlock *_block = nullptr;

	// Tracks `present` so the transition back to present can be reported to the
	// host once, as a medium change
	static inline bool _was_present = false;
};

} // namespace MetaModule
