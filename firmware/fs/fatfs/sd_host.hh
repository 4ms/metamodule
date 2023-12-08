#pragma once
#include "fat_file_io.hh"
#include "sdcard_ops.hh"

namespace MetaModule
{

class SDCardHost {

public:
	void process() {
		if (HAL_GetTick() - last_poll_tm > 200) {
			bool detect_mounted = sd.is_mounted();

			if (is_mounted && !detect_mounted) //unmount event
			{
				if (sd.unmount_disk()) {
					printf("Unmounted SD\n");
					is_mounted = false;
				} else
					pr_err("Failed to unmount sd\n");
			} else if (!is_mounted && detect_mounted) //mount event
			{
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
};

} // namespace MetaModule
