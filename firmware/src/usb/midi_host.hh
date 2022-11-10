#pragma once
#include "drivers/callable.hh"
#include "usb/midi_message.hh"
#include "usbh_midi.h"
#include <span>

void debug_midi_rx_callback(std::span<uint8_t> data);

class MidiHost {
	using CallbackFunc = Function<void(std::span<uint8_t>)>;

public:
	MidiHost() {
		_instance = this;
	}

	void register_rx_cb(CallbackFunc &&cb) {
		_rx_callback = std::move(cb);
	}

	void start_rx(USBH_HandleTypeDef *phost) {
		// Only receive into the write_buf
		USBH_MIDI_Receive(phost, rxbuffers[write_buf_idx].data(), rxbuffers[write_buf_idx].size());
	}

	std::span<uint8_t> get_midi_data() {
		// Only allow reading from the non-write_buf (aka read_buf)
		return rxbuffers[1 - write_buf_idx];
	}

	void swap_rx_buffers() {
		// Only safe to swap after an RX. How to ensure this?
		write_buf_idx = 1 - write_buf_idx;
	}

	bool is_connected() {
		//TODO:
		return true;
	}

	friend void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost, uint8_t *end_data);

private:
	static inline MidiHost *_instance;

	static constexpr uint32_t RxBufferSize = 256;
	std::array<std::array<uint8_t, RxBufferSize>, 2> rxbuffers;
	uint32_t write_buf_idx = 0;

	CallbackFunc _rx_callback = debug_midi_rx_callback;

	bool _is_connected = false;
};
