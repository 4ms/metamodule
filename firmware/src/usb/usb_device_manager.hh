#pragma once
#include "console/concurrent_buffer.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "device_cdc/usb_serial_device.hh"
#include "device_composite/usbd_composite_builder.h"
#include "device_msc/usb_drive_device.hh"
#include "device_video/usb_video_device.hh"
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include "usb_device_mode.hh"
#include "usb_midi_device.hh"

extern "C" PCD_HandleTypeDef hpcd;
extern "C" USBD_DescriptorsTypeDef CMPSIT_Desc;
extern "C" USBD_DescriptorsTypeDef UVC_Desc;

// Owns the USB device: which classes it carries, and its lifecycle.
//
// Each UsbDeviceMode is a distinct USB device with its own descriptors and
// product id, so switching modes re-enumerates. MidiConsole is a composite of
// CDC + USB-MIDI. Video is UVC alone.
struct UsbDeviceManager {
	using UsbDeviceMode = MetaModule::UsbDeviceMode;

	USBD_HandleTypeDef USBD_Device{};

	UsbSerialDevice serial;
	MetaModule::UsbVideoDevice video{&USBD_Device};
	MetaModule::UsbMidiDevice midi{&USBD_Device};
	MetaModule::UsbDriveDevice drive{*MetaModule::SharedMemoryS::ptrs.dev_drive_msgs};
	UsbDeviceMode mode = UsbDeviceMode::MidiConsole;
	uint32_t last_reenumerate_count_ = 0;

	UsbDeviceManager(std::array<ConcurrentBuffer *, 3> console_buffers,
					 UsbDeviceMode initial_mode = UsbDeviceMode::MidiConsole)
		: serial{&USBD_Device, console_buffers}
		, mode{initial_mode} {
	}

	__attribute__((noinline)) void start() {
		// Selects the config descriptor USBD_CMPSIT serves, and the FIFO split
		// USBD_LL_Init programs; must precede USBD_Init.
		USBD_CMPSIT_SelectProfile(mode == UsbDeviceMode::Video ? UsbCompositeProfile_Video :
																 UsbCompositeProfile_MidiConsole);

		auto *descriptors = (mode == UsbDeviceMode::Video) ? &UVC_Desc : &CMPSIT_Desc;

		if (auto err = USBD_Init(&USBD_Device, descriptors, 0); err != USBD_OK) {
			pr_err("USB device failed to initialize! Error %d\n", static_cast<int>(err));
			return;
		}

		if (mode == UsbDeviceMode::Video) {
			pr_info("Starting USB video device\n");
			video.register_class();
		} else {
			// The drive is only offered when the A7 has one ready. Sampled here,
			// so switching developer mode on or off re-enumerates.
			auto *dev_drive = MetaModule::SharedMemoryS::ptrs.dev_drive_msgs;
			bool with_drive = dev_drive && dev_drive->is_served();
			USBD_CMPSIT_SetDriveEnabled(with_drive);

			pr_info("Starting USB MIDI + console device%s\n", with_drive ? " + developer drive" : "");
			serial.register_class();
			midi.register_class();

			if (with_drive)
				drive.register_class(&USBD_Device);
		}

		// Every slot below NumClasses must be filled: the device core walks
		// pClass[0..NumClasses) when a host asks for a string descriptor, and
		// dereferences it without a NULL check. An empty slot means a class was
		// registered at the wrong index (see UsbComposite::add_class), and shows
		// up as a hard fault inside the OTG interrupt on the first enumeration.
		for (uint32_t i = 0; i < USBD_Device.NumClasses; i++) {
			if (USBD_Device.pClass[i] == nullptr)
				pr_err("USB: class slot %u of %u was not filled\n", (unsigned)i, (unsigned)USBD_Device.NumClasses);
		}

		USBD_Start(&USBD_Device);
	}

	__attribute__((noinline)) void stop() {
		pr_info("Stopping USB device\n");
		serial.on_stopped();
		USBD_Stop(&USBD_Device);
		USBD_DeInit(&USBD_Device);
	}

	__attribute__((noinline)) void soft_stop() {
		pr_info("Stopping USB device\n");
		serial.on_stopped();
		USBD_Stop(&USBD_Device);
	}

	void set_mode(UsbDeviceMode new_mode) {
		if (new_mode == mode)
			return;

		soft_stop();
		mode = new_mode;
		start();
	}

	// Record the desired mode without touching the peripheral (used while the
	// OTG core is busy as a host -- see UsbManager::set_device_mode).
	void set_mode_pending(UsbDeviceMode new_mode) {
		mode = new_mode;
	}

	// True if a host has enumerated us (SetConfiguration received), including
	// if the bus was subsequently suspended. Class-agnostic.
	bool is_configured() {
		return USBD_Device.dev_state == USBD_STATE_CONFIGURED ||
			   (USBD_Device.dev_state == USBD_STATE_SUSPENDED && USBD_Device.dev_old_state == USBD_STATE_CONFIGURED);
	}

	// Drop off the bus and come back, so the host enumerates us again.
	__attribute__((noinline)) void reenumerate() {
		pr_info("Re-enumerating USB device\n");

		soft_stop();

		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);

		// Adjust if needed: needs to be long enough for
		// the host to see the disconnect and then re-connect
		HAL_Delay(200);

		mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

		start();
	}

	void process() {
		// The aux core asks for this after installing from a drive the host
		// ejected
		if (auto *block = MetaModule::SharedMemoryS::ptrs.dev_drive_msgs) {
			auto count = block->reenumerate_count.load(std::memory_order_acquire);
			if (count != last_reenumerate_count_) {
				last_reenumerate_count_ = count;
				reenumerate();
				return;
			}
		}

		if (mode == UsbDeviceMode::MidiConsole) {
			serial.process();
			midi.process(); // idle-kick drain of any app-queued TX
		}
	}
};
