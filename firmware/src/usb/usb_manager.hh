#pragma once
#include "conf/fusb30x_conf.hh"
#include "debug.hh"
#include "drivers/fusb302.hh"
#include "drivers/pin_change.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "usb/device_cdc/usb_serial_device.hh"
#include "usb/usb_device_manager.hh"
#include "usb/usb_host_manager.hh"

namespace MetaModule
{

class UsbManager {
	UsbHostManager usb_host{Usb5VSrcEnablePin};
	UsbDeviceManager usb_device;

	mdrivlib::I2CPeriph usbi2c{usb_i2c_conf};
	FUSB302::Device usbctl{usbi2c, FUSBDevAddr};
	FUSB302::Device::ConnectedState state = FUSB302::Device::ConnectedState::None;
	FUSBIntPin fusb_int_pin;
	bool int_asserted = false;
	bool found_fusb = false;

	// Debug: timer for dumping registers
	// uint32_t tm;

public:
	UsbManager(RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk)
		: fusb_int_pin{mdrivlib::PinPull::Up, mdrivlib::PinSpeed::Low, mdrivlib::PinOType::OpenDrain} {
		usb_device.start();
		usb_host.init();
		found_fusb = usbctl.init(); //NOLINT
	}

	void start() {
		if (found_fusb)
			pr_dbg("FUSB302 ID Read 0x%x\n", usbctl.get_chip_id());
		else
			pr_err("Can't communicate with FUSB302\n");

		// tm = HAL_GetTick();
		pr_dbg("Starting DRP polling\n");
		usbctl.start_drp_polling();
	}

	void handle_fusb_int() {
		usbctl.handle_interrupt();

		if (auto newstate = usbctl.get_state(); newstate != state) {
			using enum FUSB302::Device::ConnectedState;

			if (newstate == AsDevice) {
				pr_info("Connected as a device\n");
				usb_device.start();

			} else if (newstate == AsHost) {
				pr_info("Starting host\n");
				usb_host.start();

			} else if (newstate == None) {
				if (state == AsHost) {
					state = None; //so that we don't do Host::Process()
					usb_host.stop();
				}

				if (state == AsDevice) {
					usb_device.stop();
				}

				//printf_("Disconnected, resuming DRP polling\n");
				usbctl.start_drp_polling();
			}
			state = newstate;
		}
	}

	void process() {
		if (fusb_int_pin.read()) {
			if (!int_asserted) {
				int_asserted = true;
				handle_fusb_int();
			}
		} else {
			if (int_asserted) {
				int_asserted = false;
			}
		}

		if (state == FUSB302::Device::ConnectedState::AsHost) {
			usb_host.process();
		}

		//DEBUG: toggle Pin0 when we're DRD polling
		// if ((HAL_GetTick() - tm) > 400) {
		// 	tm = HAL_GetTick();
		// 	auto stat0 = usbctl.read<FUSB302::Status0>();
		// if (stat0.BCLevel == 3) {
		// 	if (stat0.Comp)
		// 		Debug::Pin0::high();
		// 	else
		// 		Debug::Pin0::low();
		// }
		// }
	}

	MidiHost &get_midi_host() {
		return usb_host.get_midi_host();
	}

	FatFileIO &get_msc_fileio() {
		return usb_host.get_msc_fileio();
	}
};
} // namespace MetaModule
