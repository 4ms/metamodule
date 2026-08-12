#include "usb_drive_device.hh"
#include "device_composite/add_class.hh"
#include "pr_dbg.hh"
#include "conf/devdrive_conf.hh"
#include "usbd_conf.h"
#include <cstring>

namespace MetaModule
{

namespace
{
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

InquiryData inquiry_data = {
	.a = 0,
	.b = 0x80, // removable medium: the host offers an Eject, which is how the
			   // install workflow is triggered
	.c = 0x02,
	.d = 0x02,
	.len = sizeof(InquiryData) - 5,
	.manuf = {'4', 'm', 's', ' ', ' ', ' ', ' ', ' '},
	.product = {'D', 'e', 'v', ' ', 'D', 'r', 'i', 'v', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	.version = {'0', '.', '0', '1'},
};
} // namespace

USBD_StorageTypeDef UsbDriveDevice::ops = {
	init,
	get_capacity,
	is_ready,
	is_write_protected,
	read,
	write,
	get_max_lun,
	reinterpret_cast<int8_t *>(&inquiry_data),
	eject,
};

UsbDriveDevice::UsbDriveDevice(DevDriveBlock &block) {
	_block = &block;
}

void UsbDriveDevice::register_class(USBD_HandleTypeDef *pdev) {
	auto ok = UsbComposite::add_class(pdev, USBD_MSC_CLASS, CLASS_TYPE_MSC, CMPSIT_MSC_EpAdd, [pdev] {
		USBD_MSC_RegisterStorage(pdev, &ops);
	});

	if (ok)
		pr_info("Registered USB developer drive\n");
}

// Note: a drive that reports itself ready after an eject gets remounted by the
// host within seconds, which would defeat the eject-to-install flow. So every
// command below checks `present`, which the A7 restores once it has finished
// scanning the drive.

int8_t UsbDriveDevice::init(uint8_t lun) {
	if (lun != 0 || !_block)
		return USBD_FAIL;

	pr_info("USB dev drive: host connected\n");
	return USBD_OK;
}

int8_t UsbDriveDevice::eject(uint8_t lun) {
	if (lun != 0 || !_block)
		return USBD_FAIL;

	pr_info("USB dev drive: host ejected\n");

	// Stop reporting a medium, and tell the A7 to take the drive back. It
	// restores `present` when it has finished scanning.
	_block->present.store(0, std::memory_order_relaxed);
	_block->ejected.store(1, std::memory_order_release);
	return USBD_OK;
}

int8_t UsbDriveDevice::is_ready(uint8_t lun) {
	(void)lun;
	return (_block && _block->is_present()) ? USBD_OK : USBD_FAIL;
}

int8_t UsbDriveDevice::is_write_protected(uint8_t lun) {
	(void)lun;
	return USBD_OK;
}

int8_t UsbDriveDevice::get_capacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) {
	if (lun != 0 || !_block || !_block->is_present())
		return USBD_FAIL;

	auto mem = _block->memory();
	if (mem.empty())
		return USBD_FAIL;

	*block_num = mem.size() / DevDriveBlockSize;
	*block_size = DevDriveBlockSize;
	return USBD_OK;
}

int8_t UsbDriveDevice::read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun != 0 || !_block || !_block->is_present())
		return USBD_FAIL;

	auto mem = _block->memory();
	const uint32_t offset = blk_addr * DevDriveBlockSize;
	const uint32_t bytes = blk_len * DevDriveBlockSize;
	if (mem.empty() || offset + bytes > mem.size())
		return USBD_FAIL;

	std::memcpy(buf, mem.data() + offset, bytes);
	return USBD_OK;
}

int8_t UsbDriveDevice::write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun != 0 || !_block || !_block->is_present())
		return USBD_FAIL;

	auto mem = _block->memory();
	const uint32_t offset = blk_addr * DevDriveBlockSize;
	const uint32_t bytes = blk_len * DevDriveBlockSize;
	if (mem.empty() || offset + bytes > mem.size())
		return USBD_FAIL;

	std::memcpy(mem.data() + offset, buf, bytes);
	_block->host_wrote.store(1, std::memory_order_relaxed);
	return USBD_OK;
}

int8_t UsbDriveDevice::get_max_lun() {
	return 0; // one unit
}

} // namespace MetaModule
