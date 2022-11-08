#pragma once
#include "drivers/callable.hh"
#include "usb/midi_message.hh"
#include "usbh_midi.h"

void debug_midi_rx_callback(Midi::MidiMessage msg);

class MidiHost {
	USBH_HandleTypeDef &usbh_handle;

	static constexpr uint32_t USB_HOST_RX_BUFF_SIZE = 256;
	std::array<uint8_t, USB_HOST_RX_BUFF_SIZE> rxbuffer;

public:
	MidiHost(USBH_HandleTypeDef &usbhandle)
		: usbh_handle{usbhandle} {
		_instance = this;
	}

	void register_rx_cb(Function<void(Midi::MidiMessage &)> &&cb) {
		_rx_callback = std::move(cb);
	}

	void start_rx() {
		USBH_MIDI_Receive(&usbh_handle, rxbuffer.data(), rxbuffer.size());
	}

	Midi::MidiMessage get_rx_message() {
		return Midi::MidiMessage{rxbuffer[1], rxbuffer[2], rxbuffer[3]};
	}

	friend void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost, uint8_t *end_data);

private:
	static inline MidiHost *_instance;
	Function<void(Midi::MidiMessage)> _rx_callback = debug_midi_rx_callback;
};
