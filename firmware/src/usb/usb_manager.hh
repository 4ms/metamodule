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

// Set to 1 to build the static sink+host characterization firmware:
// - FUSB302 presents Rd on both CCs, statically -- no toggling, no probes, no
//   PD, nothing ever perturbs the CC lines
// - The host data stack (HCD) runs from boot; the device stack (PCD) never
//   starts, so OUR D+ pull-up never appears: every D+ edge on a scope is the
//   partner's
// - VBUS_ENABLE is never driven
// - One compact log line per 200ms: CC levels, VBUS, HPRT, attach state.
// If the partner enumerates, the full MIDI path runs normally.
// For characterizing partners like the OXI One "Device Self Powered".
#ifndef USB_STATIC_SINK_HOST_TEST
#define USB_STATIC_SINK_HOST_TEST 1
#endif

// Variant for the test above: 0 = present Rd (sink persona; partner Rp reads
// BC_LVL 1/2), 1 = present Rp (source persona; partner Rd reads BC_LVL 1/2,
// open line reads 3). Tests whether a partner (OXI One) latches its data role
// from what its CC sees at cable-insert.
#ifndef USB_STATIC_TEST_PRESENT_RP
#define USB_STATIC_TEST_PRESENT_RP 1
#endif

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
	uint8_t role_flips = 0;		// failed PCD<->HCD swaps since this CC attach
	uint32_t cc_attach_tm = 0;	// when the current CC attach (AsDevice) began
	uint32_t last_pd_tick = 0;

	// CC-level Try.SRC: a partner that presents steady Rp + VBUS but neither
	// enumerates us nor presents D+ in the data-role trials is a self-powered
	// DRP stuck in its source role (OXI One "Device Self Powered"): it only
	// runs its device stack after settling as a CC *sink*. Re-attach with
	// SRC-only polling (steady Rp, never Rd): losing our Rd forces it out of
	// Attached.SRC, its toggle meets our Rp, and it settles SNK -- the same
	// thing it does when plugged into a computer. A real host never fires a
	// TOGDONE in SRC polling (Rp vs Rp), so the window times out and we return
	// to DRP polling and re-attach as its device.
	bool try_src_active = false;
	bool tried_src_this_attach = false;
	uint32_t try_src_deadline = 0;
	static constexpr uint32_t TrySrcWindowMs = 1500;

	// Full attach cycles (device trial + host trial + Try.SRC) that found
	// nothing with the same partner still attached. After one failed cycle,
	// re-attach with the *host* data role first: in the device trial our PCD
	// D+ pull-up sits on an otherwise host-less bus, and a device-role partner
	// (OXI One) that samples D+ then refuses to present its own pull-up --
	// the rare successes were races against our D+ release. A real host never
	// fails a full cycle (it enumerates us in the first device trial), so
	// only stuck partners get the inverted order. Cleared when VBUS
	// disappears while unattached (partner truly left).
	uint8_t failed_attach_cycles = 0;
	uint32_t last_partner_check = 0;
	uint32_t static_test_log_tm = 0;
	static constexpr uint32_t RolePhaseTimeoutMs = 2000;
	static constexpr uint32_t PdTickMs = 50;
	// If the partner hasn't enumerated us (nor swapped roles on its own) by
	// this long after CC attach, ask for the data-host role via PD DR_Swap
	static constexpr uint32_t DrSwapRequestMs = 1000;
	// After this many failed data-role swaps, give up on this CC attach and
	// re-poll: the FUSB302 re-toggle drops our CC presentation, so the partner
	// sees a detach and resets its own state machine. Some partners (OXI One)
	// only present their device-mode D+ pull-up shortly after a fresh CC
	// attach, so swapping data roles forever on a stale attach never connects.
	static constexpr uint8_t MaxRoleFlips = 4;

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

#if USB_STATIC_SINK_HOST_TEST
		pr_info("USB: STATIC %s+HOST TEST (HCD from boot, no PCD, no VBUS sourcing)\n",
				USB_STATIC_TEST_PRESENT_RP ? "SRC (Rp presented)" : "SINK (Rd presented)");
		usb_host.init();
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		mdrivlib::InterruptControl::set_irq_priority(OTG_IRQn, 3, 0);
		mdrivlib::InterruptManager::register_isr(OTG_IRQn, [] { HAL_HCD_IRQHandler(&UsbHostManager::hhcd); });
#if USB_STATIC_TEST_PRESENT_RP
		usbctl.configure_static_src();
#else
		usbctl.configure_static_sink();
#endif
		state = FUSB302::Device::ConnectedState::AsDevice;
		host_fallback = true;
		usb_host.start(false); // never source VBUS in this experiment
		mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
		return;
#endif

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
			} else {
				// No active stack to service (and thereby clear) the interrupt in
				// this state, so the pending GINTSTS source would never clear and
				// the IRQ would re-fire forever. As OTG (priority 3) preempts
				// SysTick (priority 15), that storm starves SysTick and hangs any
				// HAL_Delay in the main loop. Mask the IRQ here so it can't storm;
				// the next connect re-inits the core (clearing GINTSTS) and
				// re-enables it. Backstops the teardown ordering in handle_fusb_int.
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
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
				state = newstate;
				role_settled = false;
				role_flips = 0;
				try_src_active = false;
				tried_src_this_attach = false;
				role_phase_tm = HAL_GetTick();
				cc_attach_tm = role_phase_tm;

				if (failed_attach_cycles > 0 && role_mode == UsbRoleMode::Auto) {
					// This partner already flunked a full cycle: keep our D+
					// pull-up off the bus and offer it a host instead
					pr_info("Connected as a device (retry: host data role first)\n");
					host_fallback = true;
					tried_src_this_attach = true; // Try.SRC already failed for this partner
					usb_host.start(false);
				} else {
					pr_info("Connected as a device\n");
					host_fallback = false;
					// start() before enabling IRQ: clears pending host-mode GINTSTS events
					usb_device.start();
				}
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

			} else if (newstate == AsHost) {
				try_src_active = false; // a Try.SRC pass (if any) succeeded
				// As the CC source we must always provide VBUS. Do NOT skip it
				// when the partner was backfeeding VBUS: a self-powered DRP
				// (OXI One) turns its own source *off* the moment it settles as
				// a sink, then abandons the attach (pulls Rd) unless VBUS
				// appears from us within its window. Rigs that backfeed
				// unconditionally (RPi gadget) tolerate the paralleled 5V --
				// that was the long-standing behavior.
				pr_info("Starting host\n");
				state = newstate;
				usb_host.start();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

			} else if (newstate == None) {
				// Mask the OTG IRQ *before* tearing down. Once we stop servicing
				// the core (below), its ISR no-ops and a pending GINTSTS source
				// would storm; since OTG (priority 3) preempts SysTick (priority
				// 15), that storm starves SysTick and the teardown's HAL_Delays
				// (vbus_off/stop) would hang forever -- leaving us stuck with
				// state==None and the IRQ spinning. So disable first, then tear
				// down. (Use the pre-transition `state` to pick the branch; the
				// final `state = newstate` below commits None.)
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);

				if (state == AsHost) {
					pr_info("Stopping host\n");
					usb_host.vbus_off();
					usb_host.stop();

				} else if (state == AsDevice) {
					pr_info("Stopping device\n");
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
#if USB_STATIC_SINK_HOST_TEST
		usb_host.process();
		if (HAL_GetTick() - static_test_log_tm >= 200) {
			static_test_log_tm = HAL_GetTick();
			auto cc = usbctl.read_both_cc();
			pr_info("[%u] CC1=%u CC2=%u VBUS=%u HPRT=%08x attached=%d\n",
					(unsigned)static_test_log_tm,
					cc.cc1,
					cc.cc2,
					cc.vbusok,
					(unsigned)usb_host.read_port_status(),
					(int)usb_host.is_device_attached());
		}
		return;
#endif

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
		// Try.SRC window expiry: nothing settled on our Rp (partner is a real
		// host, or gone) -- return to the configured role polling so a host
		// can re-attach us as its device
		// (state walks None -> TogglePolling during the window, so compare
		// against the success state, not None)
		if (try_src_active && state != FUSB302::Device::ConnectedState::AsHost &&
			(int32_t)(HAL_GetTick() - try_src_deadline) > 0) {
			pr_info("USB: no sink settled on our Rp, resuming normal role polling\n");
			try_src_active = false;
			if (failed_attach_cycles < 255)
				failed_attach_cycles++; // a full cycle found nothing
			usb_host.vbus_off(); // was pre-enabled for the Try.SRC window
			start_polling_for_role();
		}

		// Partner-gone detection: the failed-cycle memory is per-partner, so
		// clear it once VBUS reads absent while we're unattached (a partner
		// swap always drops VBUS at least briefly)
		if (failed_attach_cycles > 0 && !try_src_active && state != FUSB302::Device::ConnectedState::AsDevice &&
			state != FUSB302::Device::ConnectedState::AsHost) {
			if (HAL_GetTick() - last_partner_check > 500) {
				last_partner_check = HAL_GetTick();
				if (usbctl.read<FUSB302::Status0>().VBusOK == 0) {
					pr_dbg("USB: partner gone, clearing failed-attach memory\n");
					failed_attach_cycles = 0;
				}
			}
		}

		// While attached as sink, poll the PD engine so its timeouts advance
		// and no RX is left sitting in the FIFO (INT_N covers the fast path)
		if (state == FUSB302::Device::ConnectedState::AsDevice) {
			if (HAL_GetTick() - last_pd_tick > PdTickMs) {
				last_pd_tick = HAL_GetTick();
				usbctl.pd.tick();
			}
		}

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

	UsbConnection get_connection_status() {
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
		// device we can't use in this role
		if (device_detected_in_device_mode)
			return UsbConnection::DeviceModePeripheralIgnored;

		return UsbConnection::None;
	}

	UsbDeviceState get_status() {
		using enum FUSB302::Device::ConnectedState;
		const bool as_host = (state == AsHost) || host_fallback;

		UsbDeviceState state_out = as_host ? usb_host.get_connected_device() : UsbDeviceState{};
		state_out.status.connection = get_connection_status();
		return state_out;
	}

	// Monotonic counter that changes whenever the attached device's details are
	// (re)captured or cleared. Required for MSC
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
	// alternating until one role succeeds. Only in Auto role mode.
	// The FUSB302 stays in AsDevice throughout, so CC detach detection
	// (VBUS/BCLevel drop, plus the 250 ms backstop above) is unaffected.
	void update_role_fallback() {
		if (role_settled || role_mode != UsbRoleMode::Auto)
			return;

		if (!host_fallback) {
			if (usb_device.is_configured()) {
				role_settled = true;
				failed_attach_cycles = 0;
				// Established: from here on, ride out partner VBUS/CC dips
				// instead of tearing down the session
				usbctl.set_link_debounce(true);
				return;
			}

			// PD path: once the data roles are swapped (partner-initiated, or
			// requested below), take the host role immediately
			if (usbctl.pd.data_role_is_host()) {
				pr_info("USB: PD data-role swap complete, taking host data role (not sourcing VBUS)\n");
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
				usb_device.stop();
				usb_host.start(false);
				host_fallback = true;
				role_phase_tm = HAL_GetTick();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
				return;
			}

			// Not enumerated a while after attach: ask the partner (if it
			// speaks PD) to hand us the data-host role properly. No-op unless
			// a PD contract is in place; at most one request per attach.
			if (HAL_GetTick() - cc_attach_tm > DrSwapRequestMs)
				usbctl.pd.request_dr_swap();

			// While PD negotiation is in flight, hold off the blind data-role
			// experiments -- mixing the two confuses PD-aware partners
			if (usbctl.pd.busy())
				role_phase_tm = HAL_GetTick();

			if (HAL_GetTick() - role_phase_tm > RolePhaseTimeoutMs) {
				if (++role_flips > MaxRoleFlips) {
					restart_cc_attach();
					return;
				}
				pr_info("USB: not enumerated by partner, trying host data role (not sourcing VBUS)\n");
				mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
				// Full stop + full host init: the host port only detects
				// pull-ups after the MspInit USBO force-reset, and resetting
				// the core with the partner's VBUS hot is proven safe.
				usb_device.stop();
				usb_host.start(false);
				host_fallback = true;
				role_phase_tm = HAL_GetTick();
				mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
			}
		} else {
			if (usb_host.is_device_attached()) {
				role_settled = true;
				failed_attach_cycles = 0;
				usbctl.set_link_debounce(true);
				return;
			}
			if (HAL_GetTick() - role_phase_tm > RolePhaseTimeoutMs) {
				if (++role_flips > MaxRoleFlips) {
					restart_cc_attach();
					return;
				}
				// PD agreed we are the data host (DFP): flipping our data role
				// back would contradict the contract. Re-attach from scratch
				// instead so both sides restart coherently.
				if (usbctl.pd.data_role_is_host()) {
					pr_info("USB: PD-swapped host saw no device, restarting CC attach\n");
					restart_cc_attach();
					return;
				}
				// Partner neither enumerated us (device trial) nor presented
				// D+ (this host trial): try the CC-level SRC role once per
				// attach (see try_src_active)
				if (!tried_src_this_attach) {
					tried_src_this_attach = true;
					start_try_src();
					return;
				}
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

	// Tear down the data stacks and re-poll CC with SRC-only (steady Rp).
	// Success shows up as a normal AsHost attach (partner's Rd settles on us);
	// expiry is handled in process(), returning to the role-pref polling.
	void start_try_src() {
		pr_info("USB: partner won't enumerate us or present D+; trying SRC CC role for %u ms\n", TrySrcWindowMs);
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		if (host_fallback)
			usb_host.stop();
		else
			usb_device.stop();
		host_fallback = false;
		role_flips = 0;
		state = FUSB302::Device::ConnectedState::None;
		try_src_active = true;
		try_src_deadline = HAL_GetTick() + TrySrcWindowMs;
		// Present VBUS together with Rp, like a (dumb) host port: a partner
		// settling as sink expects VBUS immediately and pulls its Rd back if
		// it isn't there -- usb_host.start()'s init is too slow to provide it
		// after the fact (observed with the OXI One)
		usb_host.vbus_on();
		usbctl.start_src_polling();
	}

	// Give up on the current CC attach and restart toggle polling. Re-toggling
	// drops our CC presentation, so the partner sees a Type-C detach and resets
	// its own connection state machine -- a fresh start for partners that only
	// offer their data role briefly after attach. Mirrors the teardown ordering
	// of the None branch in handle_fusb_int (mask the OTG IRQ before stopping,
	// so a pending GINTSTS source can't storm once nothing services it).
	void restart_cc_attach() {
		pr_info("USB: no data role settled after %u swaps, restarting CC attach\n", role_flips - 1);
		if (failed_attach_cycles < 255)
			failed_attach_cycles++;
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		if (host_fallback)
			usb_host.stop();
		else
			usb_device.stop();
		host_fallback = false;
		role_flips = 0;
		state = FUSB302::Device::ConnectedState::None;
		start_polling_for_role();
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
