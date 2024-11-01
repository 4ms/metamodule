#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"

extern "C" PCD_HandleTypeDef hpcd;

//TODO: Add support for multiple usb interfaces (CDC/MIDI): "AddClass()" not RegisterClass
// Will need to modify USBD_HandleTypeDef such that pClass and pConfDesc are arrays (and maybe more fields?)

struct UsbDeviceManager {

	void start() {
		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 0, 0, [] { HAL_PCD_IRQHandler(&hpcd); });
	}
};
