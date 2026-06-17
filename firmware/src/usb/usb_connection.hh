#pragma once
#include "../metamodule-plugin-sdk/core-interface/system/usb.hh"

namespace MetaModule
{

using UsbConnection = System::UsbConnectionType;
using UsbConnectionStatus = System::UsbConnectionStatus;
using UsbMidiJackInfo = System::UsbMidiJackInfo;

// Full device state held in shared memory.
struct UsbDeviceState {
	UsbConnectionStatus status;
	UsbMidiJackInfo midi_in_jacks[System::MaxMidiJacks];
	UsbMidiJackInfo midi_out_jacks[System::MaxMidiJacks];
};

} // namespace MetaModule
