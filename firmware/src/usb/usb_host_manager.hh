#include "concurrent_buffer.hh"
#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_cdc_composite_host.hh"
#include "msc_host.hh"
#include "rotocontrol_host.hh"
#include "pr_dbg.hh"
#include <cstring>

class UsbHostManager {
	mdrivlib::Pin src_enable;
	USBH_HandleTypeDef usbhost{};
	static inline HCD_HandleTypeDef hhcd;
	MidiCdcCompositeHost composite_host{usbhost};
	MSCHost msc_host{usbhost, MetaModule::Volume::USB};
	RotocontrolHost roto_host{composite_host};

	static inline bool did_init = false;

	// For access in C-style callback:
	static inline MidiCdcCompositeHost *_composite_instance;
	static inline MSCHost *_mschost_instance;
	static inline ConcurrentBuffer *_console_cdc_buff;
	static inline unsigned _current_read_pos;
	static inline UsbHostManager *_manager_instance;

public:
	UsbHostManager(mdrivlib::PinDef enable_5v, ConcurrentBuffer *console_cdc_buff)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		usbhost.pActiveClass = nullptr;
		for (auto &cls : usbhost.pClass) {
			cls = nullptr;
		}
		src_enable.low();
		_composite_instance = &composite_host;
		_mschost_instance = &msc_host;
		_console_cdc_buff = console_cdc_buff;
		_current_read_pos = console_cdc_buff->current_write_pos;
		_manager_instance = this;
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

		composite_host.init();
		msc_host.init();

		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 3, 0, [] { HAL_HCD_IRQHandler(&hhcd); });
		auto err = USBH_Start(&usbhost);
		if (err != USBH_OK)
			pr_err("Error starting host\n");

		src_enable.high();
		pr_trace("VBus high, starting host\n");
	}

	void stop() {
		did_init = false;
		src_enable.low();
		HAL_Delay(250);
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		HAL_Delay(250);
		USBH_Stop(&usbhost);
		usbhost.pData = nullptr;
		USBH_DeInit(&usbhost);
	}

	void process() {
		USBH_Process(&usbhost);

		// If CDC available, poll ConcurrentBuffer and transmit directly
		if (composite_host.is_cdc_available() && composite_host.is_connected()) {
			poll_and_transmit_cdc_buffer();
		}
	}

	static inline uint8_t connected_classcode = 0xFF;

	static void usbh_state_change_callback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBHostHelper host{phost};

		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				pr_trace("Select config\n");
				break;

			case HOST_USER_CONNECTION:
				pr_trace("Connected\n");
				break;

			case HOST_USER_CLASS_SELECTED: {
				connected_classcode = host.get_active_class_code();
				pr_dbg("Class selected: %d\n", connected_classcode);
			} break;

			case HOST_USER_CLASS_ACTIVE: {
				connected_classcode = host.get_active_class_code();
				const char *classname = host.get_active_class_name();

				pr_dbg("Class active: %.8s code %d\n", classname, connected_classcode);

				if (connected_classcode == AudioClassCode && !strcmp(classname, "MIDI")) {
					_composite_instance->connect();

					// Start MIDI receive
					USBH_MIDI_Receive_Direct(phost, &_composite_instance->get_midi_handle(),
											  _composite_instance->get_midi_handle().rx_buffer, MidiStreamingBufferSize);

					// If CDC is available, configure Rotocontrol
					if (_composite_instance->is_cdc_available()) {
						pr_trace("CDC available on composite device\n");
						if (_manager_instance)
							_manager_instance->roto_host.on_cdc_connected();
					}
				}
				else if (connected_classcode == USB_MSC_CLASS && !strcmp(classname, "MSC")) {
					pr_trace("MSC connected\n");
					_mschost_instance->connect();
				}

				did_init = true;
			} break;

			case HOST_USER_DISCONNECTION: {
				pr_trace("Disconnected class code %d\n", connected_classcode);
				if (connected_classcode == AudioClassCode)
					_composite_instance->disconnect();
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
		hhcd.Init.use_external_vbus = ENABLE;
		hhcd.Init.vbus_sensing_enable = DISABLE;
		hhcd.Init.low_power_enable = DISABLE;
		hhcd.Init.dev_endpoints = 0;
		hhcd.Init.ep0_mps = EP_MPS_64;
		hhcd.Init.use_dedicated_ep1 = DISABLE;

		// Link The driver to the stack
		hhcd.pData = &usbhost;
		usbhost.pData = &hhcd;
	}

	MidiCdcCompositeHost &get_midi_host() {
		return composite_host;
	}

	FatFileIO &get_msc_fileio() {
		return msc_host.get_fileio();
	}

	bool is_msc_connected() {
		return connected_classcode == USB_MSC_CLASS;
	}

	bool is_msc_mounted() {
		return msc_host.is_mounted();
	}

private:
	void poll_and_transmit_cdc_buffer() {
		auto *buff = _console_cdc_buff;
		if (!buff)
			return;

		auto start_pos = _current_read_pos;
		unsigned end_pos = buff->current_write_pos & buff->buffer.SIZEMASK;

		if (start_pos == end_pos)
			return;

		// Find first terminator (F0 F1) to determine actual end position
		{
			unsigned scan_pos = start_pos;
			while (scan_pos != end_pos) {
				unsigned next_pos = (scan_pos + 1) & buff->buffer.SIZEMASK;
				if (next_pos != end_pos) {
					if (buff->buffer.data[scan_pos] == 0xF0 && buff->buffer.data[next_pos] == 0xF1) {
						end_pos = scan_pos;
						break;
					}
				}
				scan_pos = next_pos;
			}
		}

		if (start_pos == end_pos)
			return;

		auto transmit = [this](uint8_t *ptr, int len) {
			return composite_host.cdc_transmit(std::span<uint8_t>(ptr, len));
		};

		if (start_pos > end_pos) {
			// Wraparound
			if (transmit(&buff->buffer.data[start_pos], buff->buffer.data.size() - start_pos)) {
				_current_read_pos = 0;
			}
		} else {
			if (transmit(&buff->buffer.data[start_pos], end_pos - start_pos)) {
				_current_read_pos = end_pos;
				// Skip over terminator if we stopped at one
				unsigned actual_write_pos = buff->current_write_pos & buff->buffer.SIZEMASK;
				if (end_pos < actual_write_pos) {
					unsigned check_pos = end_pos;
					unsigned next_check = (check_pos + 1) & buff->buffer.SIZEMASK;
					if (buff->buffer.data[check_pos] == 0xF0 && buff->buffer.data[next_check] == 0xF1) {
						_current_read_pos = (next_check + 1) & buff->buffer.SIZEMASK;
					}
				}
			}
		}
	}
};
