#pragma once
#include "usb/usb_manager.hh"

// Test/characterization builds for UsbManager. Each test is enabled by setting
// its macro to 1 (all default to 0); with the macros off, the hooks defined
// here compile to no-ops, so normal builds carry no test code. Included at the
// bottom of usb_manager.hh so the hook definitions see the complete class.

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
#define USB_STATIC_SINK_HOST_TEST 0
#endif

// Variant for the test above: 0 = present Rd (sink persona; partner Rp reads
// BC_LVL 1/2), 1 = present Rp (source persona; partner Rd reads BC_LVL 1/2,
// open line reads 3). Tests whether a partner (OXI One) latches its data role
// from what its CC sees at cable-insert.
#ifndef USB_STATIC_TEST_PRESENT_RP
#define USB_STATIC_TEST_PRESENT_RP 1
#endif

// Set to 1 to build an attach-reliability test firmware: whenever a host-mode
// attach resolves (a class connects, or 5s pass without one), log a running
// ok/fail tally with port diagnostics, then tear the connection down (VBUS
// off, so a bus-powered partner cold-reboots -- a true replug) and re-poll.
// Plug a device in once and it re-attaches forever; read the tally over the
// console. For chasing intermittent attach failures (found the Inotech Grid
// attach-bounce bug, see USBH_LL_Connect in usbh_core.c).
#ifndef USB_ATTACH_CYCLE_TEST
#define USB_ATTACH_CYCLE_TEST 0
#endif

namespace MetaModule
{

// Replaces UsbManager::start() when enabled (returns true if it took over)
inline bool UsbManager::start_static_sink_host_test() {
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
	return true;
#else
	return false;
#endif
}

// Replaces UsbManager::process() when enabled (returns true if it took over)
inline bool UsbManager::process_static_sink_host_test() {
#if USB_STATIC_SINK_HOST_TEST
	usb_host.process();
	static uint32_t log_tm = 0;
	if (HAL_GetTick() - log_tm >= 200) {
		log_tm = HAL_GetTick();
		auto cc = usbctl.read_both_cc();
		pr_info("[%u] CC1=%u CC2=%u VBUS=%u HPRT=%08x attached=%d\n",
				(unsigned)log_tm,
				cc.cc1,
				cc.cc2,
				cc.vbusok,
				(unsigned)usb_host.read_port_status(),
				(int)usb_host.is_device_attached());
	}
	return true;
#else
	return false;
#endif
}

// Runs at the end of UsbManager::process() when enabled.
// printf (not pr_*) so the tally shows at any LOG_LEVEL.
inline void UsbManager::run_attach_cycle_test() {
#if USB_ATTACH_CYCLE_TEST
	using enum FUSB302::Device::ConnectedState;
	static uint32_t oks = 0, fails = 0, attach_tm = 0;
	static bool in_attach = false;

	if (state != AsHost) {
		in_attach = false;
		return;
	}

	if (!in_attach) {
		in_attach = true;
		attach_tm = HAL_GetTick();
		return;
	}

	auto conn = get_connection_status();
	const bool ok = (conn == UsbConnection::HostMidiDevice) || (conn == UsbConnection::HostUsbDrive);
	const uint32_t elapsed = HAL_GetTick() - attach_tm;
	if (!ok && elapsed <= 5000)
		return;

	ok ? oks++ : fails++;
	printf("CYCLETEST %s: ok=%u fail=%u t=%ums HPRT=%08x attached=%d otg_irq_en=%u\n",
		   ok ? "OK" : "FAIL",
		   (unsigned)oks,
		   (unsigned)fails,
		   (unsigned)elapsed,
		   (unsigned)usb_host.read_port_status(),
		   (int)usb_host.is_device_attached(),
		   (unsigned)NVIC_GetEnableIRQ(OTG_IRQn));
	if (!ok)
		usb_host.print_state_debug();

	// Tear down exactly like the None branch of handle_fusb_int, then re-poll
	mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
	usb_host.vbus_off();
	usb_host.stop();
	host_fallback = false;
	state = None;
	in_attach = false;
	start_polling_for_role();
#endif
}

} // namespace MetaModule
