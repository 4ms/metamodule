//
// cdc_host.hh
// A USB CDC Host manager - interfaces with the usbh_cdc driver
//
// By Dan Green
// Copyright (c) 2022 Dan Green
//

#pragma once
#include "pr_dbg.hh"
#include "usbh_cdc.h"
#include "util/doublebuf_stream.hh"
#include <functional>

class CDCHost {
	CDC_HandleTypeDef CDCHandle;
	USBH_HandleTypeDef &usbhost;
	USBH_ClassTypeDef *cdc_class_ops = USBH_CDC_CLASS;
	bool _is_connected = false;

	DoubleBufferStream<uint8_t, 256> tx_stream;
	bool tx_pending = false;

private:
	// Helper function to create the transmit lambda
	std::function<bool(std::span<uint8_t>)> make_transmit_lambda() {
		return [this](std::span<uint8_t> bytes) {
			auto res = USBH_CDC_Transmit(&usbhost, bytes.data(), bytes.size());

			if (res == USBH_BUSY) {
				pr_dbg("CDC Host: USBH is busy, cannot send (state might not be ready)\n");
				// Check the current CDC state for debugging
				CDC_HandleTypeDef *active_cdc_handle = (CDC_HandleTypeDef *)usbhost.pActiveClass->pData;
				if (active_cdc_handle) {
					pr_dbg("CDC Host: Current state=%d, tx_state=%d\n", active_cdc_handle->state, active_cdc_handle->data_tx_state);
				}
				return false;  // Important: return false when busy
			} else if (res == USBH_OK) {
				pr_dbg("CDC Host: Queued %zu bytes for transmission\n", bytes.size());
				// Debug print the state after queuing
				CDC_HandleTypeDef *active_cdc_handle = (CDC_HandleTypeDef *)usbhost.pActiveClass->pData;
				if (active_cdc_handle) {
					pr_dbg("CDC Host: After queue - state=%d, tx_state=%d\n",
						active_cdc_handle->state, active_cdc_handle->data_tx_state);
				}
				return true;
			} else {
				pr_err("CDC Host: Transmit failed with error %d\n", res);
				return false;
			}
		};
	}

public:
	using CDCRxCallbackType = std::function<void(uint8_t *data, uint32_t len)>;
	void set_rx_callback(CDCRxCallbackType rx_callback) {
		// Store the callback to be used when data is received
		rx_callback_ = rx_callback;
	}

	CDCHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh}
		, tx_stream{make_transmit_lambda()} {
		
		cdc_class_ops->pData = &CDCHandle;
	}

	bool init() {
		pr_info("Listening as a CDC Host\n");
		USBH_RegisterClass(&usbhost, cdc_class_ops);
		
		// Re-initialize tx_stream by constructing a new one with the lambda
		tx_stream = DoubleBufferStream<uint8_t, 256>{make_transmit_lambda()};
		tx_pending = false;
		
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

	bool set_line_coding(uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity) {
		if (!_is_connected) {
			pr_dbg("CDC Host: Not connected, cannot set line coding\n");
			return false;
		}
		
		CDC_LineCodingTypeDef line_coding;
		line_coding.b.dwDTERate = baud_rate;
		line_coding.b.bDataBits = data_bits;
		line_coding.b.bCharFormat = stop_bits;  // 0 = 1 stop bit, 1 = 1.5, 2 = 2 stop bits
		line_coding.b.bParityType = parity;     // 0 = None, 1 = Odd, 2 = Even, 3 = Mark, 4 = Space
		
		return USBH_CDC_SetLineCoding(&usbhost, &line_coding) == USBH_OK;
	}

	// Convenience method for common UART settings
	bool set_uart_115200_8N1() {
		return set_line_coding(115200, 8, 0, 0);  // 115200 baud, 8 data bits, 1 stop bit, no parity
	}

	bool set_control_line_state(bool dtr, bool rts) {
		if (!_is_connected) {
			pr_dbg("CDC Host: Not connected, cannot set control line state\n");
			return false;
		}
		
		// Get the CDC handle to find the correct interface number
		CDC_HandleTypeDef *CDCHandle = (CDC_HandleTypeDef *)usbhost.pActiveClass->pData;
		if (!CDCHandle) {
			pr_dbg("CDC Host: No CDC handle available\n");
			return false;
		}
		
		uint16_t wValue = 0;
		if (dtr) wValue |= CDC_ACTIVATE_SIGNAL_DTR;
		if (rts) wValue |= CDC_ACTIVATE_CARRIER_SIGNAL_RTS;
		
		// Set up control request
		usbhost.Control.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;
		usbhost.Control.setup.b.bRequest = CDC_SET_CONTROL_LINE_STATE;
		usbhost.Control.setup.b.wValue.w = wValue;
		usbhost.Control.setup.b.wIndex.w = 2;  // Control interface is interface 2 in this implementation
		usbhost.Control.setup.b.wLength.w = 0;
		
		pr_dbg("CDC Host: Setting control line state DTR=%d RTS=%d\n", dtr, rts);
		auto result = USBH_CtlReq(&usbhost, nullptr, 0);
		if (result != USBH_OK) {
			pr_dbg("CDC Host: Control line state request returned %d\n", result);
		}
		return result == USBH_OK;
	}

	USBH_StatusTypeDef receive() {
		if (!_is_connected) {
			return USBH_FAIL;
		}
		return USBH_CDC_Receive(&usbhost, rx_buffer_, 128);
	}

	bool transmit(std::span<uint8_t> bytes) {
		if (!_is_connected) {
			pr_dbg("CDC Host: Not connected, cannot transmit\n");
			return false;
		}
		
		// Check if we're already transmitting
		if (is_transmit_busy()) {
			pr_dbg("CDC Host: Already transmitting, cannot send more data\n");
			return false;
		}
		
		pr_dbg("CDC Host: Transmitting %zu bytes\n", bytes.size());
		return tx_stream.transmit(bytes);
	}
	
	void tx_done_callback() {
		// Notify the DoubleBufferStream that transmission is complete
		pr_dbg("CDC Host: tx_done_callback called\n");
		tx_stream.tx_done_callback();
		pr_dbg("CDC Host: tx_done_callback finished\n");
		// Set flag to indicate we may have pending data to transmit
		tx_pending = true;
	}
	
	void process_pending_tx() {
		// Check if we have pending transmissions to process
		if (tx_pending && !is_transmit_busy()) {
			tx_pending = false;
			// The DoubleBufferStream will automatically start the next transmission
			// when we call tx_done_callback, so nothing else needed here
		}
	}

	// For processing received data
	void process_rx_data(uint8_t *data, uint32_t len) {
		if (rx_callback_) {
			rx_callback_(data, len);
		}
	}

	bool is_transmit_busy() {
		// Check if the USB CDC is busy with a transmission
		CDC_HandleTypeDef *CDCHandle = (CDC_HandleTypeDef *)usbhost.pActiveClass->pData;
		if (!CDCHandle) {
			return false;
		}
		// Check both the main state and the transmission state
		bool busy = (CDCHandle->data_tx_state != CDC_IDLE);
		if (busy) {
			pr_dbg("CDC Host: TX busy - state=%d, tx_state=%d\n", CDCHandle->state, CDCHandle->data_tx_state);
		}
		return busy;
	}

	void debug_print_state() {
		CDC_HandleTypeDef *CDCHandle = (CDC_HandleTypeDef *)usbhost.pActiveClass->pData;
		if (CDCHandle) {
			pr_dbg("CDC Host Debug: state=%d, tx_state=%d, rx_state=%d\n", 
				CDCHandle->state, CDCHandle->data_tx_state, CDCHandle->data_rx_state);
		}
	}

	bool is_ready_to_transmit() {
		return _is_connected && !is_transmit_busy();
	}

private:
	CDCRxCallbackType rx_callback_ = nullptr;
	uint8_t rx_buffer_[128];
};
