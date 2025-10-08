#pragma once
#include "console/concurrent_buffer.hh"
#include "device_cdc/usb_serial_device.hh"
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "stm32mp1xx.h"

#ifdef USE_RAMDISK_USB
#include "device_msc/usb_drive_device.hh"
#endif

extern "C" PCD_HandleTypeDef hpcd;

//TODO: Add support for multiple usb interfaces (CDC/MIDI): "AddClass()" not RegisterClass
// Will need to modify USBD_HandleTypeDef such that pClass and pConfDesc are arrays (and maybe more fields?)

struct UsbDeviceManager {
	USBD_HandleTypeDef USBD_Device{};
	UsbSerialDevice serial;

#if !defined(USE_RAMDISK_USB)
	UsbDeviceManager(std::array<ConcurrentBuffer *, 3> console_buffers)
		: serial{&USBD_Device, console_buffers} {
	}
#endif

	void start() {
		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 0, 0, [] { HAL_PCD_IRQHandler(&hpcd); });
		serial.start();
		// drive.start(); // cant use this until we support multiple device classes
	}

	void stop() {
		serial.stop();
		// drive.stop();
	}

	void process() {
		serial.process();
	}

	void process_disconnected() {
#if !defined(A7_OWNS_SDCARD)
		// Still process serial because we if USB is not connected, we forward console messages to UART
		serial.forward_to_uart();
#endif
	}

#ifdef USE_RAMDISK_USB
	RamDiskOps ramdiskops;
	UsbDriveDevice drive;

	UsbDeviceManager(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk)
		: ramdiskops{rmdisk}
		, drive{ramdiskops} {
	}
#endif
};
