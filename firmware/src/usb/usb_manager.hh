#pragma once
#include "conf/fusb30x_conf.hh"
#include "console/concurrent_buffer.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/fusb302.hh"
#include "drivers/pin_change.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "usb/device_cdc/usb_serial_device.hh"
#include "usb/usb_connection.hh"
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

	// Force-device idle device-detection probe. In ForceDevice the port presents
	// Rd and is blind to a downstream device (a USB drive plugged in here does
	// nothing), which is confusing. While idle in that role we periodically flip
	// the FUSB302 to a brief Rp measurement to sense such a device, then surface
	// it (get_connection -> DeviceModePeripheralIgnored) so the GUI can prompt
	// the user to switch the USB Mode to Auto or Host. See usbctl.probe_snk_for_device().
	bool device_detected_in_device_mode = false;
	uint32_t last_device_probe = 0;
	static constexpr uint32_t DeviceProbeIntervalMs = 1000;

	// Data-role fallback for non-compliant self-powered devices (e.g. OXI One
	// "Device Self Powered") that present Rp and source VBUS -- the Type-C
	// signature of a host -- while expecting to be the USB *data* device.
	// CC-wise we stay an attached sink (the FUSB302 state remains AsDevice,
	// so its sink detach detection still applies); only the OTG core's data
	// role is swapped. See update_role_fallback().
	bool host_fallback = false; // OTG core is running HCD while FUSB state is AsDevice
	bool role_settled = false;	// enumeration succeeded in some role; stop swapping
	uint32_t role_phase_tm = 0; // when the current PCD/HCD trial phase began
	static constexpr uint32_t RolePhaseTimeoutMs = 2000;

	// Debug: timer for dumping registers
	// uint32_t tm;

	// Known issues:
	// Self-powered MIDI keyboards operating in Host + Power Sink mode (e.g. OXI One "Host No Power" mode),
	// will fail to connect. The MetaModule only connects to Device+Sink (whether or not power is actually
	// being sunk/used) and Host+Source (e.g. a computer).

public:
	UsbManager(std::array<ConcurrentBuffer *, 3> console_buffers)
		: usb_device{console_buffers, UsbDeviceMode::Midi}
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
			Debug::Pin2::high();

			if (state == AsDevice) {
				if (host_fallback)
					HAL_HCD_IRQHandler(&UsbHostManager::hhcd);
				else
					HAL_PCD_IRQHandler(&hpcd);
			} else if (state == AsHost) {
				HAL_HCD_IRQHandler(&UsbHostManager::hhcd);
			}
			Debug::Pin2::low();
		});
	}

	void handle_fusb_int() {
		usbctl.handle_interrupt();

		if (auto newstate = usbctl.get_state(); newstate != state) {
			using enum FUSB302::Device::ConnectedState;

			// Any real attachment supersedes the idle force-device probe result.
			device_detected_in_device_mode = false;

			if (newstate == AsDevice) {
				pr_info("Connected as a device\n");
				state = newstate;
				host_fallback = false;
				role_settled = false;
				role_phase_tm = HAL_GetTick();
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
					// The OTG core may be running HCD via the data-role fallback
					if (host_fallback) {
						usb_host.stop();
						host_fallback = false;
					} else {
						usb_device.stop();
					}
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
			if (host_fallback)
				usb_host.process();
			else
				usb_device.process();

			update_role_fallback();
		} else { // None or AsHost:
				 // usb_device.process_disconnected();
		}

		// While forced to the device role and idle (no host attached), the port
		// presents Rd and cannot see a downstream device. Periodically flip to a
		// brief Rp measurement to sense one (e.g. a USB drive the user plugged in
		// expecting it to work). Only when truly idle: state == None means no host
		// is attached, so the probe never disturbs a live device connection.
		if (role_mode == UsbRoleMode::ForceDevice && state == FUSB302::Device::ConnectedState::None) {
			if (HAL_GetTick() - last_device_probe > DeviceProbeIntervalMs) {
				last_device_probe = HAL_GetTick();
				bool detected = usbctl.probe_snk_for_device();
				if (detected != device_detected_in_device_mode) {
					device_detected_in_device_mode = detected;
					pr_info("USB: downstream device %s while forced to device role\n",
							detected ? "detected" : "removed");
				}
			}
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

		if (state == FUSB302::Device::ConnectedState::AsHost || host_fallback) {
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

		// The "device ignored" hint only applies while forced to device role and
		// idle; a mode change re-evaluates from scratch (the idle probe re-runs
		// if the new mode is still ForceDevice).
		device_detected_in_device_mode = false;

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
		if (state == FUSB302::Device::ConnectedState::AsHost || host_fallback) {
			return usb_host.is_msc_connected();
		} else
			return false;
	}

	bool is_drive_mounted() {
		if (state == FUSB302::Device::ConnectedState::AsHost || host_fallback) {
			return usb_host.is_msc_mounted();
		} else
			return false;
	}

	// Fold the current data role + active class into a single status for the GUI
	// (status line + connect notifications). host_fallback means the OTG core is
	// running HCD (acting as a host) even though the FUSB302 state is AsDevice.
	UsbConnection get_connection() {
		using enum FUSB302::Device::ConnectedState;
		const bool as_host = (state == AsHost) || host_fallback;
		const bool as_device = (state == AsDevice) && !host_fallback;

		if (as_host) {
			if (usb_host.is_msc_connected())
				return UsbConnection::HostUsbDrive;
			if (usb_host.get_midi_host().is_connected())
				return UsbConnection::HostMidiDevice;
			return UsbConnection::HostSearching;
		}

		if (as_device) {
			if (usb_device.is_configured()) {
				switch (usb_device.mode) {
					case UsbDeviceMode::Midi:
						return UsbConnection::DeviceMidiHost;
					case UsbDeviceMode::Video:
						return UsbConnection::DeviceVideoHost;
					case UsbDeviceMode::Cdc:
						return UsbConnection::DeviceConsoleHost;
				}
			}
			return UsbConnection::DeviceWaiting;
		}

		// Idle in a force-device role, but the idle probe sensed a downstream
		// device we can't use in this role -- surface it so the GUI can prompt a
		// USB Mode change. (Set only when role_mode == ForceDevice && state == None.)
		if (device_detected_in_device_mode)
			return UsbConnection::DeviceModePeripheralIgnored;

		return UsbConnection::None;
	}

	// Full connection status: the connection enum plus, in host mode, the
	// attached device's descriptor details (vid/pid/manufacturer/product/jacks).
	// In device mode there is no peripheral descriptor, so details stay empty.
	UsbConnectionStatus get_status() {
		using enum FUSB302::Device::ConnectedState;
		const bool as_host = (state == AsHost) || host_fallback;

		UsbConnectionStatus status = as_host ? usb_host.get_connected_device() : UsbConnectionStatus{};
		status.connection = get_connection();
		return status;
	}

	// Monotonic counter that changes whenever the attached device's details are
	// (re)captured or cleared. Pair it with get_connection() to decide when to
	// republish (handles MSC, whose enum flips before its details are ready).
	uint32_t get_device_info_seq() {
		return usb_host.get_device_info_seq();
	}

private:
	// While CC-attached as a sink, a compliant partner is a host and will
	// enumerate us promptly. A non-compliant self-powered device presenting
	// Rp + VBUS never will. If we haven't been enumerated after a timeout,
	// swap the OTG core to host mode -- without sourcing VBUS, the partner
	// already drives it -- and look for their D+ pull-up. If nothing attaches
	// there either (e.g. a charger, or a host that's just slow), swap back,
	// alternating until one role succeeds. Only in Auto role mode: ForceDevice
	// means device, period. The FUSB302 stays in AsDevice throughout, so CC
	// detach detection (VBUS/BCLevel drop, plus the 250 ms backstop above) is
	// unaffected.
	void update_role_fallback() {
		if (role_settled || role_mode != UsbRoleMode::Auto)
			return;

		if (!host_fallback) {
			if (usb_device.is_configured()) {
				role_settled = true;
				return;
			}
			if (HAL_GetTick() - role_phase_tm > RolePhaseTimeoutMs) {
				pr_info("USB: not enumerated by partner, trying host data role (not sourcing VBUS)\n");
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
				// Full stop + full host init: the host port only detects
				// pull-ups after the MspInit USBO force-reset, and resetting
				// the core with the partner's VBUS hot is proven safe (every
				// device re-connect to a computer does the same).
				usb_device.stop();
				usb_host.start(false);
				host_fallback = true;
				role_phase_tm = HAL_GetTick();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
			}
		} else {
			if (usb_host.is_device_attached()) {
				role_settled = true;
				return;
			}
			if (HAL_GetTick() - role_phase_tm > RolePhaseTimeoutMs) {
				// PCSTS (bit0) is the live electrical connect status: if it's 0
				// here, the partner never presented a D+ pull-up at all
				pr_info("USB: no device attached (HPRT=0x%08x), trying device data role\n",
						(unsigned)usb_host.read_port_status());
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
				usb_host.stop();
				usb_device.start();
				host_fallback = false;
				role_phase_tm = HAL_GetTick();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
			}
		}
	}

	// Start (or restart) the FUSB302 toggle polling for the current role policy.
	void start_polling_for_role() {
		// Hold off the force-device idle probe for one interval after any
		// (re)poll, so the freshly (re)armed SNK toggle settles before the probe
		// stops it to measure. Probing a just-reset chip can mis-read.
		last_device_probe = HAL_GetTick();

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
