#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "cdc_host.hh"
#include "msc_host.hh"
#include "pr_dbg.hh"
#include <cstring>

class UsbHostManager {
private:
	mdrivlib::Pin src_enable;
	USBH_HandleTypeDef usbhost{};
	static inline HCD_HandleTypeDef hhcd;
	MidiHost midi_host{usbhost};
	CDCHost cdc_host{usbhost};
	MSCHost msc_host{usbhost, MetaModule::Volume::USB};

	// For access in C-style callback:
	static inline MidiHost *_midihost_instance;
	static inline CDCHost *_cdchost_instance;
	static inline MSCHost *_mschost_instance;
	static inline ConcurrentBuffer *_console_cdc_buff;
	static inline unsigned _current_read_pos;

public:
	UsbHostManager(mdrivlib::PinDef enable_5v, ConcurrentBuffer *console_cdc_buff)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		usbhost.pActiveClass = nullptr;
		for (auto &cls : usbhost.pClass) {
			cls = nullptr;
		}
		src_enable.low();
		_midihost_instance = &midi_host;
		_cdchost_instance = &cdc_host;
		_mschost_instance = &msc_host;
		_console_cdc_buff = console_cdc_buff;
		_current_read_pos = console_cdc_buff->current_write_pos;
	}

	void init() {
		init_hhcd();
	}

	void start() {
		init_hhcd();

		auto status = USBH_Init(&usbhost, usbh_state_change_callback, 0);
		if (status != USBH_OK) {
			pr_err("Error init USB Host: %d\n", status);
			return;
		}
		midi_host.init();
		cdc_host.init();
		msc_host.init();

		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 3, 0, [] { HAL_HCD_IRQHandler(&hhcd); });
		auto err = USBH_Start(&usbhost);
		if (err != USBH_OK)
			pr_err("Error starting host\n");

		src_enable.high();
		pr_trace("VBus high, starting host\n");
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
		transmit_cdc_buffer();
	}

	void transmit_cdc_buffer() {
		auto transmit = [this](uint8_t *ptr, int len) {
			_cdchost_instance->transmit(std::span<uint8_t>(ptr, len));
		};

		// // Don't transmit if we already are transmitting
		// // But have a 100ms timeout in case of a USB error
		// if (is_transmitting) {
		// 	if (HAL_GetTick() - last_transmission_tm > 100) {
		// 		is_transmitting = false;
		// 		last_transmission_tm = HAL_GetTick();
		// 	} else
		// 		return;
		// }

		// Scan buffers for data to transmit, and exit after first transmission
		auto *buff = _console_cdc_buff;

		if (buff->writer_ref_count == 0) {
			auto start_pos = _current_read_pos;
			unsigned end_pos = buff->current_write_pos; //.load(std::memory_order_acquire);
			end_pos = end_pos & buff->buffer.SIZEMASK;

			if (start_pos > end_pos) {
				// Data to transmit spans the "seam" of the circular buffer,
				// Send the first chunk
				transmit(&buff->buffer.data[start_pos], buff->buffer.data.size() - start_pos);
				_current_read_pos = 0;
				return;

			} else if (start_pos < end_pos) {
				transmit(&buff->buffer.data[start_pos], end_pos - start_pos);
				_current_read_pos = end_pos;
				return;
			}
		}
	}

	static void usbh_state_change_callback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBHostHelper host{phost};
		static uint8_t connected_classcode = 0xFF;

		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				pr_trace("Select config\n");
				break;

			case HOST_USER_CONNECTION:
				pr_trace("Connected\n");
				break;

			case HOST_USER_CLASS_SELECTED: {
				connected_classcode = host.get_active_class_code();
				pr_trace("Class selected: %d\n", connected_classcode);
			} break;

			case HOST_USER_CLASS_ACTIVE: {
				connected_classcode = host.get_active_class_code();
				const char *classname = host.get_active_class_name();

				pr_trace("Class active: %.8s code %d\n", classname, connected_classcode);

				if (connected_classcode == AudioClassCode && !strcmp(classname, "MIDI")) {
					_midihost_instance->connect();
					auto mshandle = host.get_class_handle<MidiStreamingHandle>();
					if (!mshandle) {
						pr_err("Error, no MSHandle\n");
						return;
					}
					USBH_MIDI_Receive(phost, mshandle->rx_buffer, MidiStreamingBufferSize);
				}
				else if (connected_classcode == USB_CDC_CLASS && !strcmp(classname, "CDC")) {
					_cdchost_instance->connect();
					// Start receiving data 
					uint8_t rx_buffer[128];
					USBH_CDC_Receive(phost, rx_buffer, 128);
				}
				else if (connected_classcode == USB_MSC_CLASS && !strcmp(classname, "MSC")) {
					pr_trace("MSC connected\n");
					_mschost_instance->connect();
				}
			} break;

			case HOST_USER_DISCONNECTION: {
				pr_trace("Disconnected class code %d\n", connected_classcode);
				if (connected_classcode == AudioClassCode)
					_midihost_instance->disconnect();
				else if (connected_classcode == USB_CDC_CLASS)
					_cdchost_instance->disconnect();
				else if (connected_classcode == USB_MSC_CLASS)
					_mschost_instance->disconnect();
				else
					pr_warn("Unknown disconnected class code %d\n", connected_classcode);
				connected_classcode = 0xFF;
			} break;

			case HOST_USER_UNRECOVERED_ERROR:
				pr_err("USB Host Manager Error\n");
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

	CDCHost &get_cdc_host() {
		return cdc_host;
	}

	FatFileIO &get_msc_fileio() {
		return msc_host.get_fileio();
	}
};
