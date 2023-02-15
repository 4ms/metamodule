#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "usb_host_helper.hh"

#include "usbh_core.h"
#include "usbh_msc.h"

class MSCHost {
	USBH_HandleTypeDef &usbhost;
	bool _is_connected = false;

public:
	MSCHost(USBH_HandleTypeDef &usbhh)
		: usbhost{usbhh} {
	}

	bool init() {
		printf_("Registered MSC Host\n");
		USBH_RegisterClass(&usbhost, USBH_MSC_CLASS);

		return true;
	}

	// bool start() {
	// 	return USBH_Start(&usbhost) == USBH_OK;
	// }
	// bool stop() {
	// 	return USBH_Stop(&usbhost) == USBH_OK;
	// }
	// void process() {
	// 	USBH_Process(&usbhost);
	// }

	//USBH_StatusTypeDef receive() {
	//	//TODO: if we use double-buffers, swap buffers here
	//	return USBH_MIDI_Receive(&usbhost, MSHandle.rx_buffer, 128);
	//}
	//USBH_StatusTypeDef transmit(uint8_t *buff, uint32_t len) {
	//	return USBH_MIDI_Transmit(&usbhost, buff, len);
	//}

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
