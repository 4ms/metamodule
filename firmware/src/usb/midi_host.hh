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
