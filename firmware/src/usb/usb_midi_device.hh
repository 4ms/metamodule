#pragma once
#include "device_midi/usbd_midi.h"
#include "usbd_core.h"
#include "usbh_midi.hh" // for MidiStreamRxCallbackType
#include <cstdint>
#include <span>

namespace MetaModule
{

// Thin C++ wrapper around the USB-MIDI class driver (usbd_midi.c), mirroring
// UsbVideoDevice. MIDI received from the host is handed to a registered RX
// callback (Controls feeds it into the app's MIDI router, exactly like the
// MIDI-host path); app-generated MIDI is queued for transmission to the host.
class UsbMidiDevice {
public:
	UsbMidiDevice(USBD_HandleTypeDef *pDevice);

	void start();
	void stop();
	void soft_stop();

	// Idle-kick TX drain; call from the main loop (UsbDeviceManager::process).
	void process();

	// Queue raw 4-byte USB-MIDI event packets for transmission to the host.
	// Returns false if the IN endpoint is busy.
	bool transmit(std::span<const uint8_t> usb_midi_packets);

	// Register a callback invoked (in the USB ISR) with each batch of raw 4-byte
	// USB-MIDI event packets received from the host. Same signature as MidiHost,
	// so Controls can register an identical lambda for host and device.
	void set_rx_callback(MidiStreamRxCallbackType cb) {
		_rx_callback = cb;
	}

	// "Connected" == the USB device is configured (class Init ran on SetConfig,
	// DeInit not yet run). Read from the app (FrameRate ISR); written from the
	// USB ISR -- volatile, single aligned byte (atomic on M4).
	bool is_connected() const {
		return _connected;
	}

private:
	USBD_HandleTypeDef *pdev;
	MidiStreamRxCallbackType _rx_callback{};
	volatile bool _connected = false;

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
