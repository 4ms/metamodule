//
// midi_host.hh
// A USB MIDI Host manager - interfaces with the usbh_midi driver
//
// By Dan Green
// Copyright (c) 2022 Dan Green
//

#pragma once
#include "pr_dbg.hh"
#include "usb/usbh_midi.hh"
#include "util/doublebuf_stream.hh"

extern MidiStreamingHandle s_MIDIHandle;

class MidiHost {
	// MidiStreamingHandle MSHandle;
	USBH_HandleTypeDef *usbhost = nullptr;

	USBH_ClassTypeDef midi_class_ops = {
		"MIDI",
		AudioClassCode,
		USBH_MIDI_InterfaceInit,
		USBH_MIDI_InterfaceDeInit,
		USBH_MIDI_ClassRequest,
		USBH_MIDI_Process,
		USBH_MIDI_SOFProcess,
		// &MSHandle,
	};

	bool _is_connected = false;

	DoubleBufferStream<uint8_t, 64> tx_stream;

public:
	MidiHost()
		: tx_stream{[this](std::span<uint8_t> bytes) {
			if (!usbhost)
				return false;

			auto res = USBH_MIDI_Transmit(usbhost, bytes.data(), bytes.size());

			if (res == USBH_BUSY) {
				// TODO: how to handle?
				pr_err("MIDI Host: USBH is busy, cannot send\n");
			}
			return res == USBH_OK;
		}} {

		s_MIDIHandle.tx_callback = [this]() {
			tx_stream.tx_done_callback();
		};
	}

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		s_MIDIHandle.rx_callback = rx_callback;
	}

	bool init(USBH_HandleTypeDef *usbhost_root) {
		pr_info("Listening for MIDI devices on host handle %p\n", usbhost_root);
		USBH_RegisterClass(usbhost_root, &midi_class_ops);
		return true;
	}

	bool is_connected() {
		return _is_connected;
	}

	void connect(USBH_HandleTypeDef *usbhost) {
		this->usbhost = usbhost;
		_is_connected = true;
	}

	void disconnect() {
		_is_connected = false;
		this->usbhost->classData[0] = nullptr;
		this->usbhost = nullptr;
	}

	USBH_StatusTypeDef receive() {
		if (!usbhost)
			return USBH_FAIL;

		//TODO: if we use double-buffers, swap buffers here
		return USBH_MIDI_Receive(usbhost, s_MIDIHandle.rx_buffer, 128);
	}

	bool transmit(std::span<uint8_t> bytes) {
		return tx_stream.transmit(bytes);
	}
};
