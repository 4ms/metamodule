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
#include "util/lockfree_fifo_spsc.hh"
#include <array>
#include <cstring>

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

	// TX path, same pattern as UsbMidiDevice: the only state shared between
	// producer and consumer is a true SPSC FIFO of 4-byte USB-MIDI events.
	//   producer = transmit() (FrameRate ISR): put() only
	//   consumer = pump_tx(), main-loop context only -- called from process()
	//   and from tx_callback (which fires inside USBH_Process)
	// This replaces a DoubleBufferStream whose ISR-vs-main-loop buffer sharing
	// silently lost packets: as compiled, start_tx captured the buffer length
	// before publishing the new in_progress index, so packets the ISR appended
	// in that window were excluded from the transfer, then destroyed by the
	// completion-time clear().
	using MidiEventPacket = std::array<uint8_t, 4>;
	LockFreeFifoSpsc<MidiEventPacket, 512> tx_fifo;
	std::array<uint8_t, 512> tx_buf{}; // staging for the one in-flight transfer
	bool tx_in_flight = false;		   // main-loop context only

	// Drain the FIFO into one transfer if none is in flight. Main loop only.
	void pump_tx() {
		if (tx_in_flight)
			return;

		uint32_t n = 0;
		MidiEventPacket pkt;
		while ((n + pkt.size()) <= tx_buf.size() && tx_fifo.get_move(pkt)) {
			std::memcpy(&tx_buf[n], pkt.data(), pkt.size());
			n += pkt.size();
		}
		if (n == 0)
			return;

		tx_in_flight = true;
		if (USBH_MIDI_Transmit(&usbhost, tx_buf.data(), n) != USBH_OK) {
			// Not accepted (shouldn't happen in steady state): retry next pump.
			// The drained bytes stay in tx_buf and n is rebuilt, so packets
			// drained here would be lost -- count on it never triggering, but
			// log if it does.
			pr_err("MIDI Host: USBH_MIDI_Transmit rejected %u bytes\n", (unsigned)n);
			tx_in_flight = false;
		}
	}

public:
	MidiHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh} {

		MSHandle.tx_callback = [this]() {
			// Transfer finished (main-loop context): send the next batch
			tx_in_flight = false;
			pump_tx();
		};
	}

	// Call from the main loop: starts a transfer for packets queued while idle
	void process() {
		pump_tx();
	}

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		MSHandle.rx_callback = rx_callback;
	}

	bool init() {
		pr_info("Listening as a MIDI Host\n");
		USBH_RegisterClass(&usbhost, &midi_class_ops);
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
		tx_in_flight = false;
		tx_fifo.reset();
	}

	USBH_StatusTypeDef receive() {
		//TODO: if we use double-buffers, swap buffers here
		return USBH_MIDI_Receive(&usbhost, MSHandle.rx_buffer, MidiStreamingBufferSize);
	}

	// ISR context (FrameRate): enqueue only. Returns false if the FIFO is full.
	bool transmit(std::span<uint8_t> bytes) {
		bool ok = true;
		for (size_t i = 0; (i + 4) <= bytes.size(); i += 4) {
			MidiEventPacket pkt;
			std::memcpy(pkt.data(), &bytes[i], pkt.size());
			if (!tx_fifo.put(pkt)) {
				ok = false;
				break;
			}
		}
		return ok;
	}
};
