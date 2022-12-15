//
// midi_host.hh
// A USB MIDI Host manager - interfaces with the usbh_midi driver
//
// By Dan Green
// Copyright (c) 2022 Dan Green
// Licensed under MIT License, see LICENSE file
//

#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "usbh_midi.hh"

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

public:
	MidiHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh} {
	}

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		MSHandle.rx_callback = rx_callback;
	}
	void set_tx_callback(MidiStreamTxCallbackType tx_callback) {
		MSHandle.tx_callback = tx_callback;
	}

	bool init() {
		printf_("Registered MIDI Host\n");
		USBH_RegisterClass(&usbhost, &midi_class_ops);
		return true;
	}

	bool start() {
		return USBH_Start(&usbhost) == USBH_OK;
	}
	bool stop() {
		return USBH_Stop(&usbhost) == USBH_OK;
	}
	void process() {
		USBH_Process(&usbhost);
	}
	USBH_StatusTypeDef receive() {
		//TODO: if we use double-buffers, swap buffers here
		return USBH_MIDI_Receive(&usbhost, MSHandle.rx_buffer, 128);
	}
	USBH_StatusTypeDef transmit(uint8_t *buff, uint32_t len) {
		return USBH_MIDI_Transmit(&usbhost, buff, len);
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
};

// #if 0
// #pragma once
// #include "drivers/callable.hh"
// #include "usb/midi_message.hh"
// #include "usbh_midi.h"
// #include <span>

// void debug_midi_rx_callback(std::span<uint8_t> data);

// class MidiHost {
// 	using CallbackFunc = Function<void(std::span<uint8_t>)>;

// public:
// 	MidiHost() {
// 		_instance = this;
// 	}

// 	void register_rx_cb(CallbackFunc &&cb) {
// 		_rx_callback = std::move(cb);
// 	}

// 	void start_rx(USBH_HandleTypeDef *phost) {
// 		// Only receive into the write_buf
// 		USBH_MIDI_Receive(phost, rxbuffers[write_buf_idx].data(), rxbuffers[write_buf_idx].size());
// 	}

// 	std::span<uint8_t> get_midi_data() {
// 		// Only allow reading from the non-write_buf (aka read_buf)
// 		return rxbuffers[1 - write_buf_idx];
// 	}

// 	void swap_rx_buffers() {
// 		// Only safe to swap after an RX. How to ensure this?
// 		write_buf_idx = 1 - write_buf_idx;
// 	}

// 	bool is_connected() {
// 		return _is_connected;
// 	}

// 	void connect() {
// 		_is_connected = true;
// 	}

// 	void disconnect() {
// 		_is_connected = false;
// 	}

// 	friend void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost, uint8_t *end_data);

// private:
// 	static inline MidiHost *_instance;

// 	static constexpr uint32_t RxBufferSize = 256;
// 	std::array<std::array<uint8_t, RxBufferSize>, 2> rxbuffers;
// 	uint32_t write_buf_idx = 0;

// 	CallbackFunc _rx_callback = debug_midi_rx_callback;

// 	bool _is_connected = false;
// };

// #endif
