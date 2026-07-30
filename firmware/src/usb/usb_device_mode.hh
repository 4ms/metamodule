#pragma once
#include <cstdint>

namespace MetaModule
{

// Which USB *device* class the OTG core presents to a connected host.
// These are mutually exclusive (non-composite): exactly one is active at a time.
enum class UsbDeviceMode : uint32_t {
	Cdc,   // CDC ACM serial (console) -- the default/fallback
	Video, // UVC video (MetaModule Screen)
	Midi,  // USB-MIDI device
};

} // namespace MetaModule
