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
#include <functional>

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

private:
	std::function<bool(std::span<uint8_t>)> make_transmit_lambda() {
		return [this](std::span<uint8_t> bytes) {
			auto res = USBH_MIDI_Transmit(&usbhost, bytes.data(), bytes.size());

			if (res == USBH_BUSY) {
				// TODO: how to handle?
				pr_err("MIDI Host: USBH is busy, cannot send\n");
			}
			return res == USBH_OK;
		};
	}

public:
	MidiHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh}
		, tx_stream{make_transmit_lambda()} {

		MSHandle.tx_callback = [this]() {
			tx_stream.tx_done_callback();
		};
	}

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		MSHandle.rx_callback = rx_callback;
	}

	bool init() {
		pr_info("Listening as a MIDI Host\n");
		USBH_RegisterClass(&usbhost, &midi_class_ops);
		tx_stream = DoubleBufferStream<uint8_t, 64>{make_transmit_lambda()};
		return true;
	}

	bool start() {
		return USBH_Start(&usbhost) == USBH_OK;
	}

	bool stop() {
		return USBH_Stop(&usbhost) == USBH_OK;
	}

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

	bool transmit(std::span<uint8_t> bytes) {
		return tx_stream.transmit(bytes);
	}
};
