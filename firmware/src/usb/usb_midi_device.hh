#pragma once
#include "usbd_cdc.h"
#include "usbd_core.h"

class UsbMidiDevice {

public:
	UsbMidiDevice() = default;
	void init_usb_device();
	void start();
	void stop();

private:
	USBD_HandleTypeDef pdev;
};
