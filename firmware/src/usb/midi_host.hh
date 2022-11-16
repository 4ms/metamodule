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
	USBH_HandleTypeDef usbhost;
	HCD_HandleTypeDef hhcd;
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

public:
	MidiHost() = default;

	void set_rx_callback(MidiStreamRxCallbackType rx_callback) {
		MSHandle.rx_callback = rx_callback;
	}
	void set_tx_callback(MidiStreamTxCallbackType tx_callback) {
		MSHandle.tx_callback = tx_callback;
	}

	bool init() {
		init_hhcd();
		auto status = USBH_Init(&usbhost, usbh_state_change_callback, 0);
		if (status != USBH_OK)
			return false;

		InterruptControl::disable_irq(OTG_IRQn);
		InterruptManager::registerISR(OTG_IRQn, [this] { HAL_HCD_IRQHandler(&hhcd); });
		InterruptControl::set_irq_priority(OTG_IRQn, 0, 0);
		InterruptControl::enable_irq(OTG_IRQn);

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
		return USBH_MIDI_Receive(&usbhost, MSHandle.rx_buffer, 128);
	}
	USBH_StatusTypeDef transmit(uint8_t *buff, uint32_t len) {
		return USBH_MIDI_Transmit(&usbhost, buff, len);
	}

private:
	static void usbh_state_change_callback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBHostHelper host{phost};
		auto mshandle = host.get_class_handle<MidiStreamingHandle>();
		if (!mshandle)
			return;

		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				printf("Select config\n");
				break;

			case HOST_USER_CONNECTION:
				printf("Connected\n");
				break;

			case HOST_USER_CLASS_SELECTED:
				printf("Class selected\n");
				break;

			case HOST_USER_CLASS_ACTIVE:
				printf("Class active\n");
				USBH_MIDI_Receive(phost, mshandle->rx_buffer, MidiStreamingBufferSize);
				break;

			case HOST_USER_DISCONNECTION:
				printf("Disconnected\n");
				break;

			case HOST_USER_UNRECOVERED_ERROR:
				printf("Error\n");
				break;
		}
	}

	void init_hhcd() {
		memset(&hhcd, 0, sizeof(HCD_HandleTypeDef));

		hhcd.Instance = USB_OTG_HS;
		hhcd.Init.Host_channels = 16;
		hhcd.Init.speed = HCD_SPEED_HIGH;
		hhcd.Init.dma_enable = DISABLE;
		hhcd.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
		hhcd.Init.Sof_enable = DISABLE;
		hhcd.Init.battery_charging_enable = ENABLE;
		hhcd.Init.lpm_enable = ENABLE;
		hhcd.Init.use_external_vbus = ENABLE;	 // Might only be used for ULPI?
		hhcd.Init.vbus_sensing_enable = DISABLE; // Doesn't seem to be used for hosts?
		hhcd.Init.low_power_enable = DISABLE;	 // Doesn't seem to be used?
		hhcd.Init.dev_endpoints = 0;			 // Not used for hosts?
		hhcd.Init.ep0_mps = EP_MPS_64;			 // Max packet size. Doesnt seem to be used?
		hhcd.Init.use_dedicated_ep1 = DISABLE;

		// Link The driver to the stack
		hhcd.pData = &usbhost;
		usbhost.pData = &hhcd;
	}
};

#if 0
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
		return _is_connected;
	}

	void connect() {
		_is_connected = true;
	}

	void disconnect() {
		_is_connected = false;
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

#endif
