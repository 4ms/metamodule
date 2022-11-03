#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "printf.h"

class UsbHostManager {

public:
	UsbHostManager(mdrivlib::PinNoInit enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
		_midihost_instance = &midi_host;
	}

	void init() {
		auto err = USBH_Init(&usbh_handle, USBH_StateChangeCallback, HOST_HS);
		if (err != USBH_OK)
			printf_("Error init USB Host: %d\n", err);

		//hhcd defined in usbh_conf.c
		extern HCD_HandleTypeDef hhcd;
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		mdrivlib::InterruptManager::register_isr(OTG_IRQn, [] { HAL_HCD_IRQHandler(&hhcd); });
		mdrivlib::InterruptControl::set_irq_priority(OTG_IRQn, 0, 0);
	}

	void start() {
		src_enable.high();
		mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
		USBH_RegisterClass(&usbh_handle, USBH_MIDI_CLASS);
		USBH_Start(&usbh_handle);
	}
	void stop() {
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		USBH_Stop(&usbh_handle);
		src_enable.low();
	}

	void process() {
		USBH_Process(&usbh_handle);
	}

	enum ApplicationState {
		APPLICATION_IDLE = 0,
		APPLICATION_START,
		APPLICATION_READY,
		APPLICATION_DISCONNECT,
	};
	static inline ApplicationState state;

	static void USBH_StateChangeCallback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBH_DbgLog("USBH_StateChangeCallback: %d %d %d", phost->EnumState, phost->gState, id);
		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				break;

			case HOST_USER_CONNECTION:
				state = APPLICATION_START;
				break;

			case HOST_USER_CLASS_ACTIVE:
				if (state == APPLICATION_START) {
					_midihost_instance->start_rx();
					state = APPLICATION_READY;
				}
				break;

			case HOST_USER_DISCONNECTION:
				state = APPLICATION_DISCONNECT;
				break;

			case HOST_USER_UNRECOVERED_ERROR:
				state = APPLICATION_DISCONNECT;
				printf_("USB Host error");
				break;

			default:
				break;
		}
	}

private:
	USBH_HandleTypeDef usbh_handle;
	MidiHost midi_host{usbh_handle};
	static inline MidiHost *_midihost_instance;
	mdrivlib::Pin src_enable;
};
