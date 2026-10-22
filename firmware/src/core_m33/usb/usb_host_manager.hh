#pragma once
#include "conf/usb_conf.hh"
#include "drivers/interrupt_control.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/usb3dr.hh"
#include "usb/hcd_xhci.hh" // before msc_host.hh (MSCOps names HCD_HandleTypeDef)
#include "midi_host.hh"
#include "midi_jack_parse.hh"
#include "msc_host.hh"
#include "usb/usb_connection.hh"
#include "usb_host_helper.hh"
#include "xhci_host.h"
#include <cstdio>

// MP2's version of MP1's src/usb/usb_host_manager.hh (found first in the M33's include path), so
// MP1's UsbManager runs unchanged. The USB3DR's host side is an xHCI controller, which ST's HAL
// doesn't support: lib/xhci (U-Boot's xHCI driver, by way of stm32mp2-baremetal) runs it.
//
// lib/xhci enumerates the devices, including through hubs. MP1's class drivers (MIDI and USB drive)
// run on ST's USB host library, as on MP1, with one library handle each: when lib/xhci enumerates
// a device a class driver supports, the driver's handle attaches to it (see usbh_conf.cc). So a
// MIDI device and a USB drive can both be connected through a hub.
//
// The controller is polled (lib/xhci doesn't use interrupts).

// UsbManager's interrupt handler names MP1's OTG host handle. The host is polled, so if the USB
// interrupt fires while we're the host, turn it off (UsbManager turns it back on when it starts
// the device).
inline void HAL_HCD_IRQHandler(HCD_HandleTypeDef *) {
	mdrivlib::InterruptControl::disable_irq(MetaModule::UsbIRQn);
}

class UsbHostManager {
	mdrivlib::Pin src_enable;

	struct Port {
		USBH_HandleTypeDef usbh{};
		HCD_HandleTypeDef hcd{};
		bool class_active = false;
	};
	Port midi_port;
	Port msc_port;
	MidiHost midi_host{midi_port.usbh};
	MSCHost msc_host{msc_port.usbh, MetaModule::Volume::USB};

	bool running = false;
	uint32_t last_poll = 0;

	// The device shown in the Info tab: the last one a class driver started on
	Port *shown_port = nullptr;
	MetaModule::UsbDeviceState connected_device{};
	uint32_t device_info_seq = 0;

	// Root ports are cheap to check, but each poll also asks every hub for its port status
	static constexpr uint32_t PollPeriodMs = 50;

	// For the C callbacks
	static inline UsbHostManager *instance;

public:
	static inline HCD_HandleTypeDef hhcd; // for UsbManager's interrupt handler

	UsbHostManager(mdrivlib::PinDef enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
		instance = this;
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
		} else {
			xhci_host_set_disconnect_callback(device_removed);
			start_usbh(midi_port);
			midi_host.init();
			start_usbh(msc_port);
			msc_host.init();
			running = true;
		}

		if (source_vbus)
			src_enable.high();
	}

	void stop() {
		if (running) {
			stop_usbh(midi_port);
			stop_usbh(msc_port);
			xhci_host_shutdown();
			mdrivlib::Usb3DR::deinit();
			running = false;
		}
		show_device(nullptr);
	}

	void vbus_off() {
		src_enable.low();
		HAL_Delay(250);
	}

	// UsbManager calls this while it holds the I2C bus (for the FUSB302). The host doesn't use the
	// bus, and enumerating a device takes a while, so the main loop calls run() instead.
	void process() {
	}

	// Call from the main loop, without holding the I2C bus
	static void run() {
		if (instance)
			instance->run_host();
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

	MidiHost &get_midi_host() {
		return midi_host;
	}

	bool is_midi_connected() {
		return midi_host.is_connected();
	}

	FatFileIO &get_msc_fileio() {
		return msc_host.get_fileio();
	}

	bool is_msc_connected() {
		return msc_port.class_active;
	}

	bool is_msc_mounted() {
		return msc_host.is_mounted();
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

	void start_usbh(Port &port) {
		port.hcd.dev = nullptr;
		port.class_active = false;
		port.usbh.pData = &port.hcd;
		USBH_Init(&port.usbh, usbh_state_change, 0);
		USBH_Start(&port.usbh);
	}

	// Like MP1's UsbHostManager::stop(): if a class is still active, tell it its device is gone
	void stop_usbh(Port &port) {
		if (port.class_active)
			usbh_state_change(&port.usbh, HOST_USER_DISCONNECTION);
		port.hcd.dev = nullptr;
		USBH_Stop(&port.usbh);
		USBH_DeInit(&port.usbh);
	}

	void run_host() {
		if (!running)
			return;

		xhci_host_process_events();

		if (HAL_GetTick() - last_poll >= PollPeriodMs) {
			last_poll = HAL_GetTick();
			if (auto *dev = xhci_host_poll())
				device_enumerated(dev);
		}

		for (auto *port : {&midi_port, &msc_port}) {
			USBH_LL_SetTimer(&port->usbh, HAL_GetTick());
			USBH_Process(&port->usbh);
		}
		midi_host.process();
	}

	// Attach the device to the handle of the first class driver that supports it
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

		if (xhci_device_is_hub(dev))
			return;

		Port *port = nullptr;
		if (xhci_host_find_interface(dev, AudioClassCode, MidiStreamingSubClass) >= 0)
			port = &midi_port;
		else if (xhci_host_find_interface(dev, USB_MSC_CLASS, MSC_TRANSPARENT) >= 0)
			port = &msc_port;

		if (!port) {
			printf("USB host: no driver for this device\n");
			return;
		}
		if (port->hcd.dev) {
			printf("USB host: a device of this kind is already connected\n");
			return;
		}

		port->hcd.dev = dev;
		USBH_LL_Connect(&port->usbh);
	}

	// lib/xhci: a device is gone (from xhci_host_poll())
	static void device_removed(usb_device *dev) {
		for (auto *port : {&instance->midi_port, &instance->msc_port}) {
			if (port->hcd.dev == dev) {
				port->hcd.dev = nullptr;
				USBH_LL_Disconnect(&port->usbh);
			}
		}
	}

	Port *port_of(USBH_HandleTypeDef *phost) {
		return phost == &midi_port.usbh ? &midi_port : &msc_port;
	}

	// Same as MP1's UsbHostManager::usbh_state_change_callback(), for either handle
	static void usbh_state_change(USBH_HandleTypeDef *phost, uint8_t id) {
		auto &self = *instance;
		auto &port = *self.port_of(phost);
		USBHostHelper host{phost};

		switch (id) {
			case HOST_USER_CLASS_ACTIVE: {
				port.class_active = true;
				pr_trace("Class active: %.8s\n", host.get_active_class_name());

				if (&port == &self.midi_port) {
					self.midi_host.connect();
					if (auto *mshandle = host.get_class_handle<MidiStreamingHandle>())
						USBH_MIDI_Receive(phost, mshandle->rx_buffer, MidiStreamingBufferSize);
				} else {
					self.msc_host.connect();
				}
				self.show_device(&port);
			} break;

			case HOST_USER_DISCONNECTION: {
				if (!port.class_active)
					break;
				port.class_active = false;

				if (&port == &self.midi_port)
					self.midi_host.disconnect();
				else
					self.msc_host.disconnect();

				if (self.shown_port == &port) {
					auto *other = (&port == &self.midi_port) ? &self.msc_port : &self.midi_port;
					self.show_device(other->class_active ? other : nullptr);
				}
			} break;

			case HOST_USER_UNRECOVERED_ERROR:
				pr_err("USB Host Manager Error\n");
				break;
		}
	}

	// Publish the port's device for the Info tab (nullptr: none)
	void show_device(Port *port) {
		if (!port && !shown_port)
			return;

		shown_port = port;
		connected_device = {};

		if (port) {
			auto &device = port->usbh.device;
			connected_device.status.vid = device.DevDesc.idVendor;
			connected_device.status.pid = device.DevDesc.idProduct;
			connected_device.device_name.manufacturer.copy((const char *)device.Manufacturer);
			connected_device.device_name.product.copy((const char *)device.Product);

			// For a MIDI device, the jacks were collected during the class requests
			if (port == &midi_port) {
				USBHostHelper host{&port->usbh};
				if (auto *ms = host.get_class_handle<MidiStreamingHandle>())
					copy_midi_jacks(ms->jacks, connected_device);
			}
		}
		device_info_seq++;
	}
};
