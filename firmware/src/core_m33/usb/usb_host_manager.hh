#pragma once
#include "conf/usb_conf.hh"
#include "drivers/interrupt_control.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/usb3dr.hh"
#include "fat_file_io.hh"
#include "midi_host.hh"
#include "usb/usb_connection.hh"
#include "xhci_host.h"
#include <cstdio>

// MP2's version of MP1's src/usb/usb_host_manager.hh (found first in the M33's include path), so
// MP1's UsbManager runs unchanged. The USB3DR's host side is an xHCI controller, which ST's HAL
// doesn't support: lib/xhci (U-Boot's xHCI driver, by way of stm32mp2-baremetal) runs it.
//
// So far (host mode phase 1): it enumerates devices, including through hubs, prints them, and
// publishes the attached device's name and IDs (for the Info tab). No class drivers yet, so
// get_midi_host() and get_msc_fileio() are declared but not defined: code that uses the host's
// MIDI or USB drive fails to link rather than silently getting nothing.
//
// The controller is polled (lib/xhci doesn't use interrupts).

// UsbManager's interrupt handler names MP1's OTG host handle. The host is polled, so if the USB
// interrupt fires while we're the host, turn it off (UsbManager turns it back on when it starts
// the device).
struct HCD_HandleTypeDef {};
inline void HAL_HCD_IRQHandler(HCD_HandleTypeDef *) {
	mdrivlib::InterruptControl::disable_irq(MetaModule::UsbIRQn);
}

class UsbHostManager {
	mdrivlib::Pin src_enable;
	MetaModule::UsbDeviceState connected_device{};
	uint32_t device_info_seq = 0;
	bool running = false;
	bool have_device = false;
	uint32_t last_poll = 0;

	// Root ports are cheap to check, but each poll also asks every hub for its port status
	static constexpr uint32_t PollPeriodMs = 50;

public:
	static inline HCD_HandleTypeDef hhcd;

	UsbHostManager(mdrivlib::PinDef enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
	}

	void init() {
	}

	void start(bool source_vbus = true) {
		if (running)
			stop();

		init_controller();

		if (auto err = xhci_host_init(USB3DRD_BASE); err) {
			printf("USB host: xHCI init failed (%d)\n", err);
			mdrivlib::Usb3DR::deinit();
		} else
			running = true;

		if (source_vbus)
			src_enable.high();
	}

	void stop() {
		if (running) {
			xhci_host_shutdown();
			mdrivlib::Usb3DR::deinit();
			running = false;
		}
		clear_device();
	}

	void vbus_off() {
		src_enable.low();
		HAL_Delay(250);
	}

	void process() {
		if (!running)
			return;

		if (HAL_GetTick() - last_poll < PollPeriodMs)
			return;
		last_poll = HAL_GetTick();

		if (auto *dev = xhci_host_poll())
			device_enumerated(dev);

		if (have_device && !xhci_device_connected())
			clear_device();
	}

	bool is_device_attached() {
		return running && xhci_device_connected();
	}

	uint32_t read_port_status() {
		return 0;
	}

	void print_state_debug() {
	}

	MetaModule::UsbDeviceState const &get_connected_device() const {
		return connected_device;
	}

	uint32_t get_device_info_seq() const {
		return device_info_seq;
	}

	MidiHost &get_midi_host();
	FatFileIO &get_msc_fileio();

	bool is_midi_connected() {
		return false;
	}

	bool is_msc_connected() {
		return false;
	}

	bool is_msc_mounted() {
		return false;
	}

private:
	// The DWC3 core in host mode: the controller's clocks and PHY (Usb3DR), then a core reset and
	// the host role (ST's LL driver, which the device side also uses)
	void init_controller() {
		mdrivlib::Usb3DR::init(mdrivlib::Usb3DR::Role::Host);

		USB_DWC3_CfgTypeDef cfg{};
		cfg.phy_itface = USBPHY_UTMI;
		USB_CoreInit(USB3, cfg);
		USB_SetCurrentMode(USB3, USB_DWC3_HOST_MODE);

		// AHB bursts: INCR4 only, as in device mode (usbd_conf.cc)
		auto &gsbuscfg0 = *reinterpret_cast<volatile uint32_t *>(USB3DRD_BASE + 0xC100);
		gsbuscfg0 = (gsbuscfg0 & ~0xFFu) | (1u << 1);
	}

	void device_enumerated(usb_device *dev) {
		xhci_host_device_info info;
		xhci_host_get_device_info(dev, &info);

		printf("USB host: %04x:%04x %s %s (class %02x, %s speed%s)\n",
			   info.vid,
			   info.pid,
			   info.manufacturer,
			   info.product,
			   info.device_class,
			   info.speed == 1 ? "low" :
			   info.speed == 2 ? "full" :
			   info.speed == 3 ? "high" :
								 "super",
			   info.depth ? ", behind a hub" : "");

		// Show the device, not the hub it's behind
		if (xhci_device_is_hub(dev) && have_device)
			return;

		connected_device = {};
		connected_device.status.vid = info.vid;
		connected_device.status.pid = info.pid;
		connected_device.device_name.manufacturer.copy(info.manufacturer);
		connected_device.device_name.product.copy(info.product);
		have_device = true;
		device_info_seq++;
	}

	void clear_device() {
		if (!have_device)
			return;
		connected_device = {};
		have_device = false;
		device_info_seq++;
	}
};
