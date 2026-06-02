#pragma once
#include "device_midi/usbd_midi.h"
#include "usbd_core.h"
#include <cstdint>
#include <span>

namespace MetaModule
{

// Thin C++ wrapper around the USB-MIDI class driver (usbd_midi.c), mirroring
// UsbVideoDevice. For this first pass the data path is a debug loopback: MIDI
// received from the host is echoed straight back. Real routing into the app's
// MIDI router (Controls) will replace the loopback later.
class UsbMidiDevice {
public:
	UsbMidiDevice(USBD_HandleTypeDef *pDevice);

	void start();
	void stop();
	void soft_stop();

	// Queue raw 4-byte USB-MIDI event packets for transmission to the host.
	// Returns false if the IN endpoint is busy.
	bool transmit(std::span<const uint8_t> usb_midi_packets);

private:
	USBD_HandleTypeDef *pdev;

	// Drain the TX FIFO into the IN endpoint while it is free. Safe to call from
	// the USB ISR (DataOut/DataIn) and, later, from the app (single producer).
	void pump_tx();

	static int8_t MIDI_Itf_Init();
	static int8_t MIDI_Itf_DeInit();
	static int8_t MIDI_Itf_Receive(uint8_t *Buf, uint32_t *Len);
	static int8_t MIDI_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum);

	static USBD_MIDI_ItfTypeDef fops;
	static inline UsbMidiDevice *_instance = nullptr;
};

} // namespace MetaModule
