#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "printf.h"
#include <cstring>

class UsbHostManager {
	USBH_HandleTypeDef usbhost;
	HCD_HandleTypeDef hhcd;
	MidiHost midi_host{usbhost};

public:
	UsbHostManager(mdrivlib::PinNoInit enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
		_midihost_instance = &midi_host;
	}

	void init() {
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		init_hhcd();
		auto status = USBH_Init(&usbhost, usbh_state_change_callback, 0);
		if (status != USBH_OK) {
			printf_("Error init USB Host: %d\n", status);
			return;
		}

		midi_host.init();

		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		mdrivlib::InterruptManager::register_isr(OTG_IRQn, [this] { HAL_HCD_IRQHandler(&hhcd); });
		mdrivlib::InterruptControl::set_irq_priority(OTG_IRQn, 0, 0);
		mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
	}

	void start() {
		USBH_Start(&usbhost);
		src_enable.high();
		printf_("Pausing...\n");
		// HAL_Delay(500);
	}
	void stop() {
		src_enable.low();
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		USBH_Stop(&usbhost);
		// USBH_DeInit(&usbh_handle); //sets hhcd to NULL
	}

	void process() {
		USBH_Process(&usbhost);
	}

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

	MidiHost &get_midi_host() {
		return midi_host;
	}

private:
	static inline MidiHost *_midihost_instance;
	mdrivlib::Pin src_enable;
};
