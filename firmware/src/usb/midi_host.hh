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

class MidiHost {
	MidiStreamingHandle MSHandle;
	USBH_HandleTypeDef &usbhost;
	USBH_ClassTypeDef midi_class_ops = {
		"MIDI",
		AudioClassCode,
		USBH_MIDI_InterfaceInit,
		USBH_MIDI_InterfaceDeInit,
		USBH_MIDI_ClassRequest,
		USBH_MIDI_Process,
		USBH_MIDI_SOFProcess,
		&MSHandle,
	};
	bool _is_connected = false;

	DoubleBufferStream<uint8_t, 64> tx_stream;

public:
	MidiHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh}
		, tx_stream{[this](std::span<uint8_t> buf) {
			auto res = USBH_MIDI_Transmit(&usbhost, buf.data(), buf.size());
			if (res == USBH_BUSY) {
				// TODO: how to handle?
				pr_err("MIDI Host: USBH is busy, cannot send\n");
			}
			return res == USBH_OK;
		}} {

		MSHandle.tx_callback = [this]() {
			tx_stream.tx_done_callback();
		};
	}

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		MSHandle.rx_callback = rx_callback;
	}

	bool init() {
		pr_info("Registered MIDI Host\n");
		USBH_RegisterClass(&usbhost, &midi_class_ops);
		return true;
	}

	bool start() {
		return USBH_Start(&usbhost) == USBH_OK;
	}

	bool stop() {
		return USBH_Stop(&usbhost) == USBH_OK;
	}

	// void process() {
	// 	USBH_Process(&usbhost);
	// }

	bool is_connected() {
		return _is_connected;
	}

	void connect() {
		_is_connected = true;
	}

	void disconnect() {
		_is_connected = false;
	}

	USBH_StatusTypeDef receive() {
		//TODO: if we use double-buffers, swap buffers here
		return USBH_MIDI_Receive(&usbhost, MSHandle.rx_buffer, 128);
	}

	// Pushes to the inactive buffer and starts transmission if it's not already started
	bool transmit(uint32_t word) {
		// rely on unsigned overflow:
		std::array<uint8_t, 3> bytes{uint8_t(word >> 16), uint8_t(word >> 8), uint8_t(word)};

		return tx_stream.transmit(bytes);
	}
};
