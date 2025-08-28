#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "msc_fatfs_ops.hh"
#include "usb_host_helper.hh"
#include "usbh_core.h"
#include "usbh_msc.h"
#include <string_view>

class MSCHost {
	MSCOps msc_ops;
	FatFileIO msc;

public:
	MSCHost(MetaModule::Volume vol)
		: msc{&msc_ops, vol} {
	}

	bool init(USBH_HandleTypeDef *root_host) {
		pr_info("Listening for MSC devices on host %p\n", root_host);
		USBH_RegisterClass(root_host, USBH_MSC_CLASS);

		return true;
	}

	void set_handle(USBH_HandleTypeDef *usbhost) {
		msc_ops.set_handle(usbhost);
	}

	void connect() {
		pr_trace("USB MSC connect(): calling mount_disk()\n");
		msc.mount_disk();
	}

	void disconnect() {
		pr_trace("USB MSC disconnect()\n");
		msc.unmount_disk();
		msc_ops.set_handle(nullptr);
	}

	FatFileIO &get_fileio() {
		return msc;
	}

	bool is_mounted() {
		return msc.is_mounted();
	}
};
