#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "printf.h"
#include <cstring>

class UsbHostManager {
private:
	static inline MidiHost *_midihost_instance;
	mdrivlib::Pin src_enable;
	USBH_HandleTypeDef usbhost;
	static inline HCD_HandleTypeDef hhcd;
	MidiHost midi_host{usbhost};

public:
	UsbHostManager(mdrivlib::PinNoInit enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
		_midihost_instance = &midi_host;
	}

	void init() {
	}

	void start() {
		init_hhcd();

		auto status = USBH_Init(&usbhost, usbh_state_change_callback, 0);
		if (status != USBH_OK) {
			printf_("Error init USB Host: %d\n", status);
			return;
		}
		midi_host.init();

		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 0, 0, [this] { HAL_HCD_IRQHandler(&hhcd); });
		auto err = USBH_Start(&usbhost);
		if (err != USBH_OK)
			printf_("Error starting host\n");

		src_enable.high();
		printf_("VBus high, starting host\n");
		// HAL_Delay(500);
	}
	void stop() {
		src_enable.low();
		HAL_Delay(250);
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		HAL_Delay(250);
		USBH_Stop(&usbhost);
		usbhost.pData = nullptr;
		USBH_DeInit(&usbhost); //sets hhcd to NULL?
	}

	void process() {
		USBH_Process(&usbhost);
	}

	static void usbh_state_change_callback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBHostHelper host{phost};

		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				printf_("Select config\n");
				break;

			case HOST_USER_CONNECTION:
				printf_("Connected\n");
				break;

			case HOST_USER_CLASS_SELECTED:
				printf_("Class selected\n");
				break;

			case HOST_USER_CLASS_ACTIVE: {
				printf_("Class active\n");
				auto mshandle = host.get_class_handle<MidiStreamingHandle>();
				if (!mshandle) {
					printf_("Error, no MSHandle\n");
					return;
				}
				USBH_MIDI_Receive(phost, mshandle->rx_buffer, MidiStreamingBufferSize);
			} break;

			case HOST_USER_DISCONNECTION:
				printf_("Disconnected\n");
				break;

			case HOST_USER_UNRECOVERED_ERROR:
				printf_("Error\n");
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

	MidiHost &get_midi_host() {
		return midi_host;
	}
};
