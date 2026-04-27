#pragma once
#include "console/concurrent_buffer.hh"
#include "debug.hh"
#include "device_cdc/usb_serial_device.hh"
#include "device_video/usb_video_device.hh"
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "pr_dbg.hh"
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
	MetaModule::UsbVideoDevice video{&USBD_Device};
	bool video_mode = false;

#ifndef USE_RAMDISK_USB
	UsbDeviceManager(std::array<ConcurrentBuffer *, 3> console_buffers, bool video_enabled)
		: serial{&USBD_Device, console_buffers}
		, video_mode{video_enabled} {
	}
#endif

	void start() {
		if (video_mode) {
			pr_info("Starting video device\n");
			video.start();
		} else {
			pr_info("Starting serial device\n");
			serial.start();
		}
	}

	void stop() {
		if (video_mode)
			video.stop();
		else
			serial.stop();
	}

	void set_video_mode(bool enabled) {
		if (enabled == video_mode)
			return;
		// Soft stop: skip USBD_DeInit so HAL_PCD_DeInit/MspDeInit don't run.
		// hpcd->State stays READY, so the next start()'s HAL_PCD_Init skips
		// MspInit and avoids toggling USBO_CLK while VBUS is held by the host.
		// Global IRQ is disabled at the peripheral by USBD_Stop and re-enabled
		// by USBD_Start, so NVIC state can be left alone.
		if (video_mode)
			video.soft_stop();
		else
			serial.soft_stop();
		video_mode = enabled;
		start();
	}

	void process() {
		if (!video_mode)
			serial.process();
	}

	void process_disconnected() {
		if (!video_mode)
			// Still process serial because if USB is not connected, we forward console messages to UART
			serial.forward_to_uart();
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
