#pragma once
#include "../metamodule-plugin-sdk/core-interface/system/usb.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

using UsbConnection = System::UsbConnectionType;
using UsbConnectionStatus = System::UsbConnectionStatus;
using UsbMidiJackInfo = System::UsbMidiJackInfo;

// Marks a cable slot that has no jack in the snapshot (the device associated a
// jack id we didn't store, or the cable number is past the device's count).
inline constexpr uint8_t NoJackIdx = 0xFF;

using CableJackMap = std::array<uint8_t, System::MaxMidiCables>;

// Used as a default member initializer, so that a cable map with no device
// attached reads as "no jack here" rather than "jack 0".
constexpr CableJackMap empty_cable_map() {
	CableJackMap map{};
	for (auto &idx : map)
		idx = NoJackIdx;
	return map;
}

// Full device state held in shared memory.
struct UsbDeviceState {
	UsbConnectionStatus status;
	UsbMidiJackInfo midi_in_jacks[System::MaxMidiJacks];
	UsbMidiJackInfo midi_out_jacks[System::MaxMidiJacks];

	// Cable number -> index into the jack arrays above, from the baAssocJackID
	// table of the device's bulk endpoints. An rx cable (device -> MetaModule)
	// is served by an Embedded MIDI *OUT* jack, and a tx cable by an Embedded
	// MIDI *IN* jack, so the two maps index different arrays.
	CableJackMap rx_cable_out_jack_idx = empty_cable_map();
	CableJackMap tx_cable_in_jack_idx = empty_cable_map();
};

} // namespace MetaModule
