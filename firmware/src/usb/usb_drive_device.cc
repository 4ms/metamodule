#include "usb_drive_device.hh"
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "printf.h"
#include "usbd_desc.h"
#include "usbd_msc.h"


//TODO: Add SD Card as a second lun (or add each partition as a lun)

//TODO make a device manager that owns hpcd, like UsbHostManager
extern "C" PCD_HandleTypeDef hpcd;

using mdrivlib::HWSemaphore;
using mdrivlib::HWSemaphoreFlag;
using mdrivlib::InterruptControl;
using mdrivlib::InterruptManager;

//TODO: Add support for multiple usb interfaces (CDC/MIDI): "AddClass()" not RegisterClass
//Should also rename this class to UsbDeviceManager or something
void UsbDriveDevice::init_usb_device() {
}

void UsbDriveDevice::start() {
	// TODO: try for 3 seconds before failing
	if (HWSemaphore<MetaModule::RamDiskLock>::lock(3) == HWSemaphoreFlag::LockFailed) {
		printf_("Cannot get lock on RamDisk, aborting usb device start\n");
		return;
	}
	nordisk->set_status(RamDiskOps::Status::InUse);

	init_fops();
	auto init_ok = USBD_Init(&pdev, &MSC_Desc, 0);
	if (init_ok != USBD_OK) {
		printf_("USB Device failed to initialize!\r\n");
		printf_("Error code: %d", static_cast<int>(init_ok));
		return;
	}

	mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 0, 0, [] { HAL_PCD_IRQHandler(&hpcd); });
	USBD_RegisterClass(&pdev, USBD_MSC_CLASS);
	USBD_MSC_RegisterStorage(&pdev, &ops);
	USBD_Start(&pdev);
}

void UsbDriveDevice::stop() {
	nordisk->set_status(RamDiskOps::Status::Unmounted);
	InterruptControl::disable_irq(OTG_IRQn);
	USBD_Stop(&pdev);
	USBD_DeInit(&pdev);

	printf_("M4 is unlocking RamDisk Lock\n");
	HWSemaphore<MetaModule::RamDiskLock>::unlock(3);
	nordisk->set_status(RamDiskOps::Status::WritingBack);
}

/// Ops:

int8_t UsbDriveDevice::init(uint8_t lun) {
	if (lun == 0) {
		if (!nordisk)
			return USBD_FAIL;
		printf_("USB MSC connected to host\r\n");
		nordisk->set_status(RamDiskOps::Status::Mounted);
	}
	return USBD_OK;
}

int8_t UsbDriveDevice::eject(uint8_t lun) {
	if (lun == 0) {
		if (!nordisk)
			return USBD_FAIL;
		printf_("USB MSC device got Eject event from host\r\n");
		nordisk->set_status(RamDiskOps::Status::Unmounted);
	}
	return USBD_OK;
}

int8_t UsbDriveDevice::get_capacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) {
	if (lun == 0) {
		if (!nordisk)
			return USBD_FAIL;
		*block_num = nordisk->SizeBytes / nordisk->BlockSize;
		*block_size = nordisk->BlockSize;
	}
	return (USBD_OK);
}

int8_t UsbDriveDevice::is_ready(uint8_t lun) {
	if (!nordisk)
		return USBD_FAIL;
	return USBD_OK;
}

int8_t UsbDriveDevice::is_write_protected(uint8_t lun) {
	if (!nordisk)
		return USBD_FAIL;
	return USBD_OK;
}

int8_t UsbDriveDevice::read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun == 0) {
		if (!nordisk)
			return USBD_FAIL;
		return (nordisk->read(buf, blk_addr, blk_len) == RES_OK) ? USBD_OK : USBD_FAIL;
	}
	return USBD_OK;
}

int8_t UsbDriveDevice::write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) {
	if (lun == 0) {
		if (!nordisk)
			return USBD_FAIL;
		return (nordisk->write(buf, blk_addr, blk_len) == RES_OK) ? USBD_OK : USBD_FAIL;
	}
	return USBD_OK;
}

int8_t UsbDriveDevice::get_max_lun() {
	if (!nordisk)
		return USBD_FAIL;
	return 0; //1 unit
}

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

static InquiryData inquiry_data = {
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

void UsbDriveDevice::init_fops() {
	ops = {
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
}

UsbDriveDevice::UsbDriveDevice(RamDiskOps &nfs) {
	nordisk = &nfs;
	init_fops();
}
