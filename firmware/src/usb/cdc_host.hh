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

class CDCHost {
	CDC_HandleTypeDef CDCHandle;
	USBH_HandleTypeDef &usbhost;
	USBH_ClassTypeDef *cdc_class_ops = USBH_CDC_CLASS;
	bool _is_connected = false;

	DoubleBufferStream<uint8_t, 128> tx_stream;

public:
	CDCHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh}
		, tx_stream{[this](std::span<uint8_t> bytes) {
			auto res = USBH_CDC_Transmit(&usbhost, bytes.data(), bytes.size());

			if (res == USBH_BUSY) {
				// TODO: how to handle?
				pr_err("CDC Host: USBH is busy, cannot send\n");
			}
			return res == USBH_OK;
		}} {
		
		cdc_class_ops->pData = &CDCHandle;
	}

	using CDCRxCallbackType = std::function<void(uint8_t *data, uint32_t len)>;
	void set_rx_callback(CDCRxCallbackType rx_callback) {
		// Store the callback to be used when data is received
		rx_callback_ = rx_callback;
	}

	bool init() {
		pr_info("Listening as a CDC Host\n");
		USBH_RegisterClass(&usbhost, cdc_class_ops);
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
		if (!_is_connected) {
			return USBH_FAIL;
		}
		return USBH_CDC_Receive(&usbhost, rx_buffer_, 128);
	}

	bool transmit(std::span<uint8_t> bytes) {
		if (!_is_connected) {
			return false;
		}
		return tx_stream.transmit(bytes);
	}
	
	// For processing received data
	void process_rx_data(uint8_t *data, uint32_t len) {
		if (rx_callback_) {
			rx_callback_(data, len);
		}
	}

private:
	CDCRxCallbackType rx_callback_ = nullptr;
	uint8_t rx_buffer_[128];
};
