#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "cdc_host.hh"
#include "msc_host.hh"
#include "pr_dbg.hh"
#include <cstring>

class UsbHostManager {
public:
	enum class PreferredClass {
		AUTO,    // Pick first available (default behavior)
		MIDI,    // Prefer MIDI class
		CDC,     // Prefer CDC class  
		MSC      // Prefer MSC class
	};

private:
	mdrivlib::Pin src_enable;
	USBH_HandleTypeDef usbhost{};
	static inline HCD_HandleTypeDef hhcd;
	MidiHost midi_host{usbhost};
	CDCHost cdc_host{usbhost};
	MSCHost msc_host{usbhost, MetaModule::Volume::USB};
	
	PreferredClass preferred_class = PreferredClass::MIDI;
	static inline bool did_init = false;
	static inline unsigned inflight_cdc_commands = 0;

	// For access in C-style callback:
	static inline MidiHost *_midihost_instance;
	static inline CDCHost *_cdchost_instance;
	static inline MSCHost *_mschost_instance;
	static inline ConcurrentBuffer *_console_cdc_buff;
	static inline unsigned _current_read_pos;
	static inline PreferredClass *_preferred_class_ptr;
	static inline UsbHostManager *_manager_instance;

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
		_preferred_class_ptr = &preferred_class;
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
		
		// Set the preferred class if specified
		if (preferred_class != PreferredClass::AUTO) {
			switch (preferred_class) {
				case PreferredClass::MIDI:
					usbhost.PreferredClassName = "MIDI";
					break;
				case PreferredClass::CDC:
					usbhost.PreferredClassName = "CDC";
					break;
				case PreferredClass::MSC:
					usbhost.PreferredClassName = "MSC";
					break;
				default:
					usbhost.PreferredClassName = nullptr;
					break;
			}
		}
		
		cdc_host.init();
		midi_host.init();
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
		did_init = false;
		inflight_cdc_commands = 0; // Reset inflight counter on stop
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
		// Scan buffers for data to transmit, and exit after first transmission
		auto *buff = _console_cdc_buff;

		auto start_pos = _current_read_pos;
		unsigned end_pos = buff->current_write_pos; //.load(std::memory_order_acquire);
		end_pos = end_pos & buff->buffer.SIZEMASK;

		// Find first terminator (FF FF) to determine actual end position
		if (start_pos != end_pos) {
			unsigned scan_pos = start_pos;
			bool found_terminator = false;
			
			while (scan_pos != end_pos && !found_terminator) {
				unsigned next_pos = (scan_pos + 1) & buff->buffer.SIZEMASK;
				if (next_pos != end_pos) {
					if (buff->buffer.data[scan_pos] == 0xF0 && buff->buffer.data[next_pos] == 0xF1) {
						// Found terminator, stop transmission before it
						end_pos = scan_pos;
						found_terminator = true;
					}
				}
				scan_pos = next_pos;
			}
		}

		if (start_pos == end_pos) {
			return;
		}

		if (preferred_class != PreferredClass::CDC) {
			pr_dbg("Switching to CDC\n");
			did_init = false;
			
			stop();	
			set_preferred_class(PreferredClass::CDC);
			start();
			return;
		}

		if (!did_init) {
			return;
		}

		pr_dbg("Transmitting CDC data, did_init is true\n");

		// Don't try to transmit if CDC host is not ready
		if (!_cdchost_instance->is_ready_to_transmit()) {
			return;
		}

		pr_dbg("Transmitting CDC data, cdc host is ready\n");
		
		auto transmit = [this](uint8_t *ptr, int len) {
			inflight_cdc_commands++;
			return _cdchost_instance->transmit(std::span<uint8_t>(ptr, len));
		};

		if (start_pos > end_pos) {
			// Data to transmit spans the "seam" of the circular buffer,
			// Send the first chunk
			pr_dbg("Transmitting data from pos %d to %d: ", start_pos, buff->buffer.data.size());
			for (size_t i = start_pos; i < buff->buffer.data.size(); i++)
				pr_dbg("%02X ", buff->buffer.data[i]);
			pr_dbg("\n");
			if (transmit(&buff->buffer.data[start_pos], buff->buffer.data.size() - start_pos)) {
				_current_read_pos = 0;
				// Note: For wraparound case, terminator logic is handled in the scanning phase
			}
			return;

		} else if (start_pos < end_pos) {
			pr_dbg("Transmitting data from pos %d to %d: ", start_pos, end_pos);
			for (size_t i = start_pos; i < end_pos; i++)
				pr_dbg("%02X ", buff->buffer.data[i]);
			pr_dbg("\n");
			if (transmit(&buff->buffer.data[start_pos], end_pos - start_pos)) {
				_current_read_pos = end_pos;
				// If we stopped at a terminator, skip over the FF FF
				if (end_pos < (buff->current_write_pos & buff->buffer.SIZEMASK)) {
					unsigned check_pos = end_pos;
					unsigned next_check = (check_pos + 1) & buff->buffer.SIZEMASK;
					if (buff->buffer.data[check_pos] == 0xFF && buff->buffer.data[next_check] == 0xFF) {
						_current_read_pos = (next_check + 1) & buff->buffer.SIZEMASK;
					}
				}
			}
			return;
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
				pr_dbg("Class selected: %d\n", connected_classcode);
				
				// Check if this matches our preference
				if (_preferred_class_ptr && *_preferred_class_ptr != PreferredClass::AUTO) {
					bool should_accept = false;
					switch (*_preferred_class_ptr) {
						case PreferredClass::MIDI:
							should_accept = (connected_classcode == AudioClassCode);
							break;
						case PreferredClass::CDC:
							should_accept = (connected_classcode == USB_CDC_CLASS);
							break;
						case PreferredClass::MSC:
							should_accept = (connected_classcode == USB_MSC_CLASS);
							break;
						default:
							should_accept = true;
					}
					
					if (!should_accept) {
						pr_dbg("Skipping class %d, waiting for preferred class\n", connected_classcode);
						// TODO: Need to implement a way to reject this class and try another
						// For now, we'll just log the mismatch
					}
				}
			} break;

			case HOST_USER_CLASS_ACTIVE: {
				connected_classcode = host.get_active_class_code();
				const char *classname = host.get_active_class_name();

				pr_dbg("Class active: %.8s code %d\n", classname, connected_classcode);

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
					
					// Configure UART parameters for 115200 8N1
					if (!_cdchost_instance->set_uart_115200_8N1()) {
						pr_err("Failed to set CDC line coding to 115200 8N1\n");
					} else {
						pr_trace("CDC line coding set to 115200 8N1\n");
					}
					
					// Set DTR and RTS high - many devices require this to start communication
					if (!_cdchost_instance->set_control_line_state(true, true)) {
						pr_warn("CDC device does not support control line state (DTR/RTS) - this is often normal\n");
					} else {
						pr_trace("CDC control lines DTR/RTS set high\n");
					}
					
					// Give the device time to initialize after configuration
					HAL_Delay(100);
					
					// Set up receive callback to handle incoming UART data
					_cdchost_instance->set_rx_callback([](uint8_t *data, uint32_t len) {
						pr_dbg("CDC received %d bytes: ", len);
						for (uint32_t i = 0; i < len; i++) {
							pr_dbg("%02X ", data[i]);
						}
						pr_dbg("\n");
						
						// TODO: Process your UART binary data here
						// For example, you might want to:
						// - Parse the data according to your protocol
						// - Forward it to another component
						// - Store it in a buffer for later processing
					});
					
					// Start receiving data 
					_cdchost_instance->receive();
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

	void set_preferred_class(PreferredClass pref) {
		preferred_class = pref;
	}

	// Friend function declaration to allow access to private members
	friend void USBH_CDC_ReceiveCallback(USBH_HandleTypeDef *phost);
	friend void USBH_CDC_TransmitCallback(USBH_HandleTypeDef *phost);
};

// USB Host CDC Transmit Callback - called by the USB stack when CDC data has been sent
extern "C" void USBH_CDC_TransmitCallback(USBH_HandleTypeDef *phost) {
	pr_dbg("CDC Host: Transmit completed\n");
	
	// Decrement inflight commands counter
	if (UsbHostManager::inflight_cdc_commands > 0) {
		UsbHostManager::inflight_cdc_commands--;
	}
	
	// Notify the CDC host that transmission is complete
	auto *cdc_instance = UsbHostManager::_cdchost_instance;
	if (cdc_instance && cdc_instance->is_connected()) {
		cdc_instance->tx_done_callback();
	}
	
	// Switch back to MIDI mode only when all CDC transmissions are complete
	auto *manager = UsbHostManager::_manager_instance;
	if (manager && 
		UsbHostManager::_preferred_class_ptr && 
		*UsbHostManager::_preferred_class_ptr == UsbHostManager::PreferredClass::CDC && 
		UsbHostManager::inflight_cdc_commands == 0) {
		
		pr_dbg("Switching back to MIDI mode after all CDC transmissions complete (inflight: %u)\n", UsbHostManager::inflight_cdc_commands);
		manager->stop();
		manager->set_preferred_class(UsbHostManager::PreferredClass::MIDI);
		manager->start();
	}
}

// USB Host CDC Receive Callback - called by the USB stack when CDC data is received
extern "C" void USBH_CDC_ReceiveCallback(USBH_HandleTypeDef *phost) {
	auto *cdc_instance = UsbHostManager::_cdchost_instance;
	if (cdc_instance && cdc_instance->is_connected()) {
		// Get the received data from the CDC handle
		CDC_HandleTypeDef *CDCHandle = (CDC_HandleTypeDef *)phost->pActiveClass->pData;
		if (CDCHandle && CDCHandle->pRxData) {
			// Get the actual received data length
			uint32_t len = USBH_CDC_GetLastReceivedDataSize(phost);
			if (len > 0) {
				// Process the received data through the CDCHost
				// The data is in the buffer that was passed to USBH_CDC_Receive
				cdc_instance->process_rx_data(CDCHandle->pRxData, len);
				
				// Re-arm the receive to get more data
				cdc_instance->receive();
			}
		}
	}
}
