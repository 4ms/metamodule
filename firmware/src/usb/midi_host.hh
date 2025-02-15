//
// midi_host.hh
// A USB MIDI Host manager - interfaces with the usbh_midi driver
//
// By Dan Green
// Copyright (c) 2022 Dan Green
//

#pragma once
#include "pr_dbg.hh"
#include "usbh_midi.hh"
#include "util/fixed_vector.hh"
#include <optional>

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

	// This size can be adjusted if needed
	FixedVector<uint8_t, 64> tx_buffer[2];
	std::optional<unsigned> in_progress_idx = 0;

public:
	MidiHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh} {

		MSHandle.tx_callback = [this]() {
			tx_done_callback();
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

	void process() {
		USBH_Process(&usbhost);
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

	// Pushes to the inactive buffer and starts transmission if it's not already started
	bool transmit(uint32_t word) {
		auto inactive_idx = 1 - in_progress_idx.value_or(1);
		auto &inactive_buf = tx_buffer[inactive_idx];

		// Note: STM USB host library does not call the tx callback in an IRQ,
		// so we do not run the risk of tx_done_callback() interrupting us
		if (inactive_buf.available() >= 3) {
			inactive_buf.push_back(word >> 16);
			inactive_buf.push_back(word >> 8);
			inactive_buf.push_back(word);

			// Start a new transmission if one isn't in progress
			if (!in_progress_idx.has_value()) {
				auto res = start_tx(inactive_idx);
				return res == USBH_OK;
			}

			// tx_done_callback() will transmit our data when it's called
			return true;
		} else
			return false;
	}

private:
	USBH_StatusTypeDef start_tx(unsigned idx) {
		in_progress_idx = idx;
		auto &active_buf = tx_buffer[idx];
		auto res = USBH_MIDI_Transmit(&usbhost, active_buf.begin(), active_buf.size());

		if (res == USBH_BUSY) {
			// TODO: how to handle?
			pr_err("MIDI Host: USBH is busy, cannot send\n");
		}
		return res;
	}

	void tx_done_callback() {
		if (!in_progress_idx.has_value())
			pr_err("MIDI Host internal error: tx_done_callback called but no buffer is in progress\n");

		tx_buffer[in_progress_idx.value()].clear();

		// Check if we should start transmitting the other buffer
		auto other_buffer = 1 - in_progress_idx.value();

		if (tx_buffer[other_buffer].size()) {
			start_tx(other_buffer);
		} else {
			in_progress_idx = std::nullopt;
		}
	}
};
