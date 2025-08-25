#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "midi_host.hh"
#include "msc_host.hh"
#include "pr_dbg.hh"
#include "stm32-usb-host-lib/Class/HUB/usbh_hub.h"
#include <cstring>

class UsbHostManager {
private:
	mdrivlib::Pin src_enable;

	USBH_HandleTypeDef host_handles[9]{};
	// root_host_handle (aka host_handles[0]) handles the device directly attached to the MM
	// the other host_handles[1-8] handle the devices attached to hub ports
	USBH_HandleTypeDef &root_host_handle = host_handles[0];

	// Host handle currently being processed (round-robin)
	USBH_HandleTypeDef *cur_host_handle = nullptr;
	int cur_host_idx = -1;

	static inline HCD_HandleTypeDef hhcd;

	MidiHost midi_host{};
	MSCHost msc_host{root_host_handle, MetaModule::Volume::USB};

	// For access in C-style callback:
	static inline MidiHost *_midihost_instance;
	static inline MSCHost *_mschost_instance;

public:
	UsbHostManager(mdrivlib::PinDef enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		root_host_handle.pActiveClass = nullptr;
		for (auto &cls : root_host_handle.pClass) {
			cls = nullptr;
		}
		src_enable.low();
		_midihost_instance = &midi_host;
		_mschost_instance = &msc_host;
	}

	void init() {
		init_hhcd();
	}

	void start() {
		init_hhcd();

		for (auto i = 0; i < 9; i++)
			pr_info("&host_handle[%d] = %p\n", i, &host_handles[i]);

		auto status = USBH_Init(&root_host_handle, usbh_state_change_callback, 0);
		if (status != USBH_OK) {
			pr_err("Error init USB Host: %d\n", status);
			return;
		}
		midi_host.init(&root_host_handle);
		msc_host.init();

		// hub_host.init():
		pr_info("Listening for Hub devices\n");
		USBH_RegisterClass(&root_host_handle, USBH_HUB_CLASS);
		/////

		mdrivlib::InterruptManager::register_and_start_isr(OTG_IRQn, 3, 0, [] { HAL_HCD_IRQHandler(&hhcd); });
		auto err = USBH_Start(&root_host_handle);
		if (err != USBH_OK)
			pr_err("Error starting host\n");

		src_enable.high();
		pr_trace("VBus high, starting host\n");
		// HAL_Delay(500);
	}

	void stop() {
		pr_dbg("Stopping USB Host\n");

		src_enable.low();
		HAL_Delay(250);
		mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
		HAL_Delay(250);

		// TODO: stop all handles
		USBH_Stop(&root_host_handle);
		root_host_handle.pData = nullptr;
		USBH_DeInit(&root_host_handle); //sets hhcd to NULL?
	}

	void process() {
		if (cur_host_handle != nullptr && cur_host_handle->valid == 1) {

			USBH_Process(cur_host_handle);

			if (cur_host_handle->busy)
				return;
		}

		// scan for next host
		for (auto tries = 0; tries < MAX_HUB_PORTS; tries++) {

			if (++cur_host_idx > MAX_HUB_PORTS)
				cur_host_idx = 0;

			if (host_handles[cur_host_idx].valid) {
				cur_host_handle = &host_handles[cur_host_idx];
				// pr_dbg("Setup EP0 for host idx %d", cur_host_idx);
				USBH_LL_SetupEP0(cur_host_handle);

				if (cur_host_handle->valid == 3) {
					pr_dbg("PROCESSING ATTACH %d", cur_host_handle->hubPortAddress);
					cur_host_handle->valid = 1;
					cur_host_handle->busy = 1;
				}

				break;
			}
		}
	}

	static inline uint8_t connected_classcode = 0xFF;

	static void usbh_state_change_callback(USBH_HandleTypeDef *phost, uint8_t id) {
		USBHostHelper host{phost};

		switch (id) {
			case HOST_USER_SELECT_CONFIGURATION:
				pr_dbg("UsbHostManager: Select config\n");
				break;

			case HOST_USER_CONNECTION:
				pr_dbg("UsbHostManager: Connected\n");
				break;

			case HOST_USER_CLASS_SELECTED: {
				connected_classcode = host.get_active_class_code();
				pr_dbg("UsbHostManager: Class selected: %d\n", connected_classcode);
			} break;

			case HOST_USER_CLASS_ACTIVE: {
				connected_classcode = host.get_active_class_code();
				const char *classname = host.get_active_class_name();

				pr_dbg("UsbHostManager: Class active: %.8s code %d\n", classname, connected_classcode);

				if (connected_classcode == AudioClassCode && !strcmp(classname, "MIDI")) {
					_midihost_instance->connect(phost);
					auto mshandle = host.get_class_handle<MidiStreamingHandle>();
					if (!mshandle) {
						pr_err("UsbHostManager: Error, no MSHandle\n");
						return;
					}
					USBH_MIDI_Receive(phost, mshandle->rx_buffer, MidiStreamingBufferSize);
				}

				if (connected_classcode == USB_MSC_CLASS && !strcmp(classname, "MSC")) {
					pr_dbg("UsbHostManager: MSC connected\n");
					_mschost_instance->connect();
				}
			} break;

			case HOST_USER_DISCONNECTION: {
				pr_dbg("Disconnected class code %d\n", connected_classcode);
				if (connected_classcode == AudioClassCode)
					_midihost_instance->disconnect();
				else if (connected_classcode == USB_MSC_CLASS)
					_mschost_instance->disconnect();
				else
					pr_warn("UsbHostManager: Unknown disconnected class code %d\n", connected_classcode);
				connected_classcode = 0xFF;
			} break;

			case HOST_USER_UNRECOVERED_ERROR:
				pr_err("UsbHostManager: USB Host Manager Error\n");
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
		hhcd.pData = &root_host_handle;

		for (auto &handle : host_handles) {
			// All handles reference the host controller (OTG host driver)
			handle.pData = &hhcd;
			// All handles have a pointer to the array of all handles
			handle.handles = host_handles;

			// All handles reference all classes we are capable of hosting
			handle.pClass[0] = USBH_MSC_CLASS;
			handle.pClass[1] = midi_host.usb_class();
			handle.ClassNumber = 2;

			handle.currentTarget = &handle.rootTarget;
		}
		host_handles[0].valid = 1;
		host_handles[0].rootTarget.dev_address = USBH_DEVICE_ADDRESS;
		host_handles[0].rootTarget.speed = USBH_HS_SPEED;
		// host_handles[0].Pipes = USBH_malloc(sizeof(uint32_t) * USBH_MAX_PIPES_NBR);

		cur_host_idx = -1;
	}

	MidiHost &get_midi_host() {
		return midi_host;
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
};
