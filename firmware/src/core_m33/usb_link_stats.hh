#pragma once
#include <cstdint>

namespace MetaModule
{

// Counts of USB device events, kept by usbd_conf.cc (in the USB interrupt), for the console
struct UsbLinkStats {
	uint32_t irqs;
	uint32_t resets;	 // bus resets (Connect Done)
	uint32_t setups;	 // SETUP packets received
	uint32_t suspends;
	uint32_t disconnects;
	uint32_t speed; // PCD_SPEED_*, as enumerated at the last reset
};

extern volatile UsbLinkStats usb_link_stats;

} // namespace MetaModule
