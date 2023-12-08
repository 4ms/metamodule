#pragma once
#include "fat_file_io.hh"
#include "sdcard_ops.hh"

namespace MetaModule
{

class SDCardHost {

public:
	void process() {
		if (HAL_GetTick() - last_poll_tm > 200) {
			bool card_detected = sd.is_mounted(); //misnomer: should be sd.is_detected()

			if (is_detected && !card_detected) //unmount event
			{
				is_detected = false;
				if (sd.unmount_disk()) {
					printf("Unmounted SD\n");
					is_mounted = false;
				} else
					pr_err("Failed to unmount sd\n");
			} else if (!is_detected && card_detected) //mount event
			{
				is_detected = true;
				if (sd.mount_disk()) {
					printf("Mounted SD\n");
					is_mounted = true;
				} else
					pr_err("Failed to mount sd\n");
			}
			//
		}
	}

	FatFileIO &get_fileio() {
		return sd;
	}

private:
	SDCardOps<SDCardConf> sdcard_ops;
	FatFileIO sd{&sdcard_ops, Volume::SDCard};

	uint32_t last_poll_tm = 0;
	bool is_mounted = false;
	bool is_detected = false;
};

} // namespace MetaModule
