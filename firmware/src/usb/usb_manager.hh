#pragma once
#include "conf/fusb30x_conf.hh"
#include "console/concurrent_buffer.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/fusb302.hh"
#include "drivers/pin_change.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "usb/device_cdc/usb_serial_device.hh"
#include "usb/usb_device_manager.hh"
#include "usb/usb_host_manager.hh"
#include "usb/usb_role_mode.hh"

namespace MetaModule
{

extern "C" PCD_HandleTypeDef hpcd;

class UsbManager {
	UsbHostManager usb_host{Usb5VSrcEnablePin};
	UsbDeviceManager usb_device;

	mdrivlib::I2CPeriph usbi2c{usb_i2c_conf};
	FUSB302::Device usbctl{usbi2c, FUSBDevAddr};
	FUSB302::Device::ConnectedState state = FUSB302::Device::ConnectedState::None;
	FUSBIntPin fusb_int_pin;
	bool found_fusb = false;
	uint32_t last_device_link_check = 0;
	UsbRoleMode role_mode = UsbRoleMode::Auto;

	// Debug: timer for dumping registers
	// uint32_t tm;

	// Known issues:
	// Self-powered MIDI keyboards operating in Host + Power Sink mode (e.g. OXI One "Host No Power" mode),
	// will fail to connect. The MetaModule only connects to Device+Sink (whether or not power is actually
	// being sunk/used) and Host+Source (e.g. a computer).

public:
	UsbManager(std::array<ConcurrentBuffer *, 3> console_buffers)
		: usb_device{console_buffers, UsbDeviceMode::Cdc}
		, fusb_int_pin{mdrivlib::PinPull::Up, mdrivlib::PinSpeed::Low, mdrivlib::PinOType::OpenDrain} {
		found_fusb = usbctl.init(); //NOLINT
	}

	void start() {
		if (found_fusb)
			pr_dbg("FUSB302 ID Read 0x%x\n", usbctl.get_chip_id());
		else
			pr_err("Can't communicate with FUSB302\n");

		// tm = HAL_GetTick();
		pr_dbg("Starting USB role polling\n");
		start_polling_for_role();

		usb_device.start();
		usb_host.init();

		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		mdrivlib::InterruptControl::set_irq_priority(OTG_IRQn, 3, 0);
		mdrivlib::InterruptManager::register_isr(OTG_IRQn, [this] {
			using enum FUSB302::Device::ConnectedState;

			if (state == AsDevice) {
				HAL_PCD_IRQHandler(&hpcd);
			} else if (state == AsHost) {
				HAL_HCD_IRQHandler(&UsbHostManager::hhcd);
			}
		});
	}

	void handle_fusb_int() {
		usbctl.handle_interrupt();

		if (auto newstate = usbctl.get_state(); newstate != state) {
			using enum FUSB302::Device::ConnectedState;

			if (newstate == AsDevice) {
				pr_info("Connected as a device\n");
				state = newstate;
				// start() before enabling IRQ: clears pending host-mode GINTSTS events
				usb_device.start();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

			} else if (newstate == AsHost) {
				pr_info("Starting host\n");
				state = newstate;
				usb_host.start();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

			} else if (newstate == None) {
				if (state == AsHost) {
					pr_info("Stopping host\n");
					state = None;
					usb_host.vbus_off();
					mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
					usb_host.stop();
				}

				if (state == AsDevice) {
					pr_info("Stopping device\n");
					state = None;
					mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
					usb_device.stop();
				}

				//printf_("Disconnected, resuming polling\n");
				start_polling_for_role();
			}
			state = newstate;
		}
	}

	void process() {
		// INT_N is a level interrupt: the FUSB302 holds it asserted while any
		// unmasked event is pending, releasing it only when handle_interrupt()
		// reads the Interrupt registers.
		if (fusb_int_pin.read()) {
			handle_fusb_int();
		}

		// Backstop for unplug events the FUSB302 never raises an interrupt
		// for (observed with OXI One Host+Power after a SRC mis-settle, and
		// VBUSOK has been seen not to fire on VBUS decay): while attached as
		// a device, poll the link status at a low rate and run the normal
		// interrupt handling if it shows the link down.
		if (state == FUSB302::Device::ConnectedState::AsDevice) {
			if (HAL_GetTick() - last_device_link_check > 250) {
				last_device_link_check = HAL_GetTick();
				auto status0 = usbctl.read<FUSB302::Status0>();
				if (status0.VBusOK == 0 || status0.BCLevel == 0)
					handle_fusb_int();
			}
		}

		if (state == FUSB302::Device::ConnectedState::AsHost) {
			usb_host.process();
		}

		if (state == FUSB302::Device::ConnectedState::AsDevice) {
			usb_device.process();
		} else { // None or AsHost:
				 // usb_device.process_disconnected();
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

	void set_device_mode(UsbDeviceMode mode) {
		if (mode == UsbDeviceMode::Video)
			UsbVideoDevice::set_framebuffer(SharedMemoryS::ptrs.uvc_framebuffer);

		if (state == FUSB302::Device::ConnectedState::AsHost) {
			// Don't start a device class while we're acting as a host, just
			// store the desired mode for later.
			usb_device.set_mode_pending(mode);
		} else {
			usb_device.set_mode(mode);
		}
	}

	// Apply the USB-C data-role policy pushed from the A7. Auto = DRP toggle;
	// ForceHost = SRC-only toggle; ForceDevice = SNK-only toggle.
	void set_role_mode(UsbRoleMode mode) {
		if (mode == role_mode)
			return;
		role_mode = mode;

		using enum FUSB302::Device::ConnectedState;
		// Re-poll in the new role only if we're not in an active connection.
		// If currently attached (AsHost/AsDevice), the new role takes effect on
		// the next disconnect (handle_fusb_int's None path re-polls). Don't tear
		// down a live connection out from under the OTG core.
		if (state == None || state == TogglePolling)
			start_polling_for_role();
	}

	MidiHost &get_midi_host() {
		return usb_host.get_midi_host();
	}

	UsbMidiDevice &get_midi_device() {
		return usb_device.midi;
	}

	FatFileIO &get_msc_fileio() {
		return usb_host.get_msc_fileio();
	}

	bool is_drive_detected() {
		if (state == FUSB302::Device::ConnectedState::AsHost) {
			return usb_host.is_msc_connected();
		} else
			return false;
	}

	bool is_drive_mounted() {
		if (state == FUSB302::Device::ConnectedState::AsHost) {
			return usb_host.is_msc_mounted();
		} else
			return false;
	}

private:
	// Start (or restart) the FUSB302 toggle polling for the current role policy.
	void start_polling_for_role() {
		switch (role_mode) {
			case UsbRoleMode::ForceHost:
				pr_info("USB: forcing host role (SRC polling)\n");
				usbctl.start_src_polling();
				break;
			case UsbRoleMode::ForceDevice:
				pr_info("USB: forcing device role (SNK polling)\n");
				usbctl.start_snk_polling();
				break;
			case UsbRoleMode::Auto:
			default:
				pr_dbg("USB: auto host/device role (DRP polling)\n");
				usbctl.start_drp_polling();
				break;
		}
	}
};
} // namespace MetaModule
