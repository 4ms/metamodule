#pragma once
#include "console/concurrent_buffer.hh"
#include "debug.hh"
#include "device_cdc/usb_serial_device.hh"
#include "device_video/usb_video_device.hh"
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include "usb_device_mode.hh"
#include "usb_midi_device.hh"

#ifdef USE_RAMDISK_USB
#include "device_msc/usb_drive_device.hh"
#endif

extern "C" PCD_HandleTypeDef hpcd;

//TODO: Add support for multiple usb interfaces (CDC/MIDI): "AddClass()" not RegisterClass
// Will need to modify USBD_HandleTypeDef such that pClass and pConfDesc are arrays (and maybe more fields?)

struct UsbDeviceManager {
	using UsbDeviceMode = MetaModule::UsbDeviceMode;

	USBD_HandleTypeDef USBD_Device{};

	UsbSerialDevice serial;
	MetaModule::UsbVideoDevice video{&USBD_Device};
	MetaModule::UsbMidiDevice midi{&USBD_Device};
	UsbDeviceMode mode = UsbDeviceMode::Cdc;

#ifndef USE_RAMDISK_USB
	UsbDeviceManager(std::array<ConcurrentBuffer *, 3> console_buffers,
					 UsbDeviceMode initial_mode = UsbDeviceMode::Cdc)
		: serial{&USBD_Device, console_buffers}
		, mode{initial_mode} {
	}
#endif

	void start() {
		switch (mode) {
			case UsbDeviceMode::Video:
				pr_info("Starting video device\n");
				video.start();
				break;
			case UsbDeviceMode::Midi:
				pr_info("Starting MIDI device\n");
				midi.start();
				break;
			case UsbDeviceMode::Cdc:
			default:
				pr_info("Starting serial device\n");
				serial.start();
				break;
		}
	}

	void stop() {
		switch (mode) {
			case UsbDeviceMode::Video:
				video.stop();
				break;
			case UsbDeviceMode::Midi:
				midi.stop();
				break;
			case UsbDeviceMode::Cdc:
			default:
				serial.stop();
				break;
		}
	}

	void set_mode(UsbDeviceMode new_mode) {
		if (new_mode == mode)
			return;
		// Soft stop: skip USBD_DeInit so HAL_PCD_DeInit/MspDeInit don't run.
		// hpcd->State stays READY, so the next start()'s HAL_PCD_Init skips
		// MspInit and avoids toggling USBO_CLK while VBUS is held by the host.
		// Global IRQ is disabled at the peripheral by USBD_Stop and re-enabled
		// by USBD_Start, so NVIC state can be left alone.
		switch (mode) {
			case UsbDeviceMode::Video:
				video.soft_stop();
				break;
			case UsbDeviceMode::Midi:
				midi.soft_stop();
				break;
			case UsbDeviceMode::Cdc:
			default:
				serial.soft_stop();
				break;
		}
		mode = new_mode;
		start();
	}

	// Record the desired mode without touching the peripheral (used while the
	// OTG core is busy as a host -- see UsbManager::set_device_mode).
	void set_mode_pending(UsbDeviceMode new_mode) {
		mode = new_mode;
	}

	void process() {
		if (mode == UsbDeviceMode::Cdc)
			serial.process();
		else if (mode == UsbDeviceMode::Midi)
			midi.process(); // idle-kick drain of any app-queued TX
	}

	void process_disconnected() {
		if (mode == UsbDeviceMode::Cdc)
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
