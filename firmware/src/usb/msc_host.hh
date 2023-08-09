#pragma once
#include "drivers/interrupt.hh"
#include "drivers/interrupt_control.hh"
#include "usb_host_helper.hh"

#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "msc_fatfs_ops.hh"
#include "usbh_core.h"
#include "usbh_msc.h"

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

	// bool is_connected() {
	// 	return _is_connected;
	// }

	void connect() {
		if (msc.mount_disk()) {
			printf_("Mounted MSC drive with FATFS\n");
			msc.foreach_file_with_ext(".yml", [](std::string_view fname, uint32_t timestamp, uint32_t fsize) {
				if (fname[0] == '\0' | fname[0] == '.')
					return;
				printf_("%.255s\t\t0x%x\t\t%d B\n", fname.data(), timestamp, fsize);
			});
			// _is_connected = true;
		} else
			printf_("Failed to mount MSC drive\n");
	}

	void disconnect() {
		msc.unmount_disk();
		// _is_connected = false;
	}

	FatFileIO &get_fileio() {
		return msc;
	}
};
