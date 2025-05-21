#pragma once
#include "conf/fusb30x_conf.hh"
#include "console/concurrent_buffer.hh"
#include "debug.hh"
#include "drivers/fusb302.hh"
#include "drivers/pin_change.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "usb/device_cdc/usb_serial_device.hh"
#include "usb/usb_device_manager.hh"
#include "usb/usb_host_manager.hh"
#include <functional>

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
	UsbManager(std::array<ConcurrentBuffer *, 3> console_buffers)
		: usb_device{console_buffers}
		, fusb_int_pin{mdrivlib::PinPull::Up, mdrivlib::PinSpeed::Low, mdrivlib::PinOType::OpenDrain} {
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

		if (state == FUSB302::Device::ConnectedState::AsDevice) {
			usb_device.process();
		} else {
			usb_device.process_disconnected();
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
	
	// Send a custom command to the serial port
	bool send_serial_command(const std::vector<uint8_t>& command) {
		return usb_device.get_serial_device().send_command(command);
	}
	
	// Get firmware version from connected device with simplified callback
	bool get_firmware_version(std::function<void(bool success)> callback) {
		return usb_device.get_serial_device().get_firmware_version(callback);
	}
	
	// Start config update command
	bool start_config_update(std::function<void(bool success)> callback) {
		return usb_device.get_serial_device().start_config_update(callback);
	}
	
	// End config update command
	bool end_config_update(std::function<void(bool success)> callback) {
		return usb_device.get_serial_device().end_config_update(callback);
	}
	
	// Set knob control configuration
	bool set_knob_control_config(uint8_t setup_index, uint8_t control_index, uint8_t control_mode,
	                            uint8_t control_channel, uint8_t control_param, uint16_t nrpn_address,
	                            uint16_t min_value, uint16_t max_value, const std::string& control_name,
	                            uint8_t color_scheme, uint8_t haptic_mode, uint8_t indent_pos1, uint8_t indent_pos2,
	                            uint8_t haptic_steps, const std::vector<std::string>& step_names,
	                            std::function<void(bool success)> callback) {
		return usb_device.get_serial_device().set_knob_control_config(
			setup_index, control_index, control_mode, control_channel, control_param, nrpn_address,
			min_value, max_value, control_name, color_scheme, haptic_mode, indent_pos1, indent_pos2,
			haptic_steps, step_names, callback);
	}
	
	// Get access to the serial device for more advanced operations
	UsbSerialDevice& get_serial_device() {
		return usb_device.get_serial_device();
	}
};
} // namespace MetaModule
