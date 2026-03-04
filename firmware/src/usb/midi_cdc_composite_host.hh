#pragma once

#include "pr_dbg.hh"
#include "usb/usbh_midi.hh"
#include "usbh_cdc.h"
#include "util/doublebuf_stream.hh"
#include <functional>
#include <span>

struct MidiCdcCompositeHandle {
	MidiStreamingHandle midi{};
	CDC_HandleTypeDef cdc{};
	bool cdc_available = false;
};

class MidiCdcCompositeHost {
public:
	using CDCRxCallbackType = std::function<void(uint8_t *data, uint32_t len)>;

	MidiCdcCompositeHost(USBH_HandleTypeDef &usbhh);

	// Registration
	void init();

	// Connection management
	void connect();
	void disconnect();

	// MIDI interface (matches MidiHost signatures)
	bool is_connected();
	bool transmit(std::span<uint8_t> bytes);
	void set_rx_callback(MidiStreamRxCallbackType rx_callback);
	USBH_StatusTypeDef receive();

	// CDC interface
	bool is_cdc_available();
	bool cdc_transmit(std::span<uint8_t> bytes);
	void set_cdc_rx_callback(CDCRxCallbackType cb);
	bool set_cdc_line_coding(uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);
	bool set_cdc_control_line_state(bool dtr, bool rts);
	USBH_StatusTypeDef cdc_receive();

	// Handle access
	MidiStreamingHandle &get_midi_handle() { return composite_handle.midi; }
	CDC_HandleTypeDef &get_cdc_handle() { return composite_handle.cdc; }
	MidiCdcCompositeHandle &get_composite_handle() { return composite_handle; }

	// CDC callbacks (called from static context)
	void on_cdc_tx_done();
	void on_cdc_rx_done();

	// Static instance pointer for C-style callbacks
	static inline MidiCdcCompositeHost *instance = nullptr;

private:
	USBH_HandleTypeDef &usbhost;
	MidiCdcCompositeHandle composite_handle{};
	bool _is_connected = false;

	DoubleBufferStream<uint8_t, 64> midi_tx_stream;
	DoubleBufferStream<uint8_t, 256> cdc_tx_stream;

	CDCRxCallbackType cdc_rx_callback = nullptr;
	uint8_t cdc_rx_buffer[128]{};

	// Composite class driver callbacks
	static USBH_StatusTypeDef composite_interface_init(USBH_HandleTypeDef *phost);
	static USBH_StatusTypeDef composite_interface_deinit(USBH_HandleTypeDef *phost);
	static USBH_StatusTypeDef composite_class_request(USBH_HandleTypeDef *phost);
	static USBH_StatusTypeDef composite_process(USBH_HandleTypeDef *phost);
	static USBH_StatusTypeDef composite_sof_process(USBH_HandleTypeDef *phost);

	// CDC state machine helpers
	static void cdc_process_transmission(USBH_HandleTypeDef *phost, CDC_HandleTypeDef *cdc);
	static void cdc_process_reception(USBH_HandleTypeDef *phost, CDC_HandleTypeDef *cdc);

	USBH_ClassTypeDef composite_class_ops;

	std::function<bool(std::span<uint8_t>)> make_midi_transmit_lambda();
	std::function<bool(std::span<uint8_t>)> make_cdc_transmit_lambda();
};
