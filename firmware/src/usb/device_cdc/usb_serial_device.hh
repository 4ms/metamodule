#pragma once
#include "usbd_cdc.h"
#include "usbd_core.h"

class UsbSerialDevice {

public:
	UsbSerialDevice();
	void init_usb_device();
	void start();
	void stop();
	// static inline USBD_StorageTypeDef ops;

private:
	USBD_HandleTypeDef *pdev;
};
