#include "usb/midi_message.hh"
#include "usbh_midi.h"

class MidiHost {
	USBH_HandleTypeDef &usbh_handle;

	static constexpr uint32_t USB_HOST_RX_BUFF_SIZE = 256;
	std::array<uint8_t, USB_HOST_RX_BUFF_SIZE> rxbuffer;

public:
	MidiHost(USBH_HandleTypeDef &usbhandle)
		: usbh_handle{usbhandle} {
	}

	void start_rx() {
		USBH_MIDI_Receive(&usbh_handle, rxbuffer.data(), rxbuffer.size());
	}

	Midi::MidiMessage get_rx_message() {
		return Midi::MidiMessage{rxbuffer[1], rxbuffer[2], rxbuffer[3]};
	}
};
