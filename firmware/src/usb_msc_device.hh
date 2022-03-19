#pragma once

#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc_storage.h"
#include <functional>

//TODO: move MSC_fops here
//Use norfs interface (read/write/eject)
//TODO: to support multiple USB device interfaces (CDC/MIDI + MSC device)
//

extern "C" PCD_HandleTypeDef hpcd;

class UsbDriveDevice {
	using InterruptControl = mdrivlib::InterruptControl;
	using InterruptManager = mdrivlib::InterruptManager;

public:
	UsbDriveDevice() = default;
	void start() {
		auto init_ok = USBD_Init(&USBD_Device, &MSC_Desc, 0);
		if (init_ok != USBD_OK) {
			printf("USB Device failed to initialize!\r\n");
			printf("Error code: %d", static_cast<int>(init_ok));
		}
		InterruptControl::disable_irq(OTG_IRQn);
		InterruptControl::set_irq_priority(OTG_IRQn, 1, 0);
		InterruptManager::register_isr(OTG_IRQn, std::bind_front(HAL_PCD_IRQHandler, &hpcd));
		InterruptControl::enable_irq(OTG_IRQn, InterruptControl::LevelTriggered);
		USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);
		USBD_MSC_RegisterStorage(&USBD_Device, &USBD_MSC_fops);
		USBD_Start(&USBD_Device);
	}

private:
	USBD_HandleTypeDef USBD_Device;
};
