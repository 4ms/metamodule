#pragma once
#include <cstdint>

namespace MetaModule
{

// What the OTG core presents to a connected host. The two modes are mutually
// exclusive: each is a separate USB configuration with its own descriptors and
// product id, so switching between them re-enumerates.
enum class UsbDeviceMode : uint32_t {
	// One composite device carrying USB-MIDI and a CDC ACM serial console (and,
	// in developer mode, an MSC drive). The default.
	MidiConsole,
	// UVC video (MetaModule Screen), on its own: the isochronous video stream
	// wants the whole FIFO budget, and hosts are fussier about composite UVC.
	Video,
};

} // namespace MetaModule
