#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "usb_host_helper.hh"

#include "fat_file_io.hh"
#include "msc_fatfs_ops.hh"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "volumes.hh"

class MSCHost {
	USBH_HandleTypeDef &usbhost;
	bool _is_connected = false;
	MSCOps msc_ops{usbhost};
	FatFileIO msc;

public:
	MSCHost(USBH_HandleTypeDef &usbhost, MetaModule::Volume vol)
		: usbhost{usbhost}
		, msc{&msc_ops, vol} {
	}

	bool init() {
		printf_("Registered MSC with USB Host\n");
		USBH_RegisterClass(&usbhost, USBH_MSC_CLASS);

		return true;
	}

	bool is_connected() {
		return _is_connected;
	}

	void connect() {
		if (msc.mount_disk()) {
			printf_("Mounted MSC drive with FATFS\n");
			_is_connected = true;
		} else
			printf_("Failed to mount MSC drive\n");
	}

	void disconnect() {
		_is_connected = false;
	}
};
