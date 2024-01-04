#pragma once
#include "debug.hh"
#include "fat_file_io.hh"
#include "sdcard_ops.hh"

namespace MetaModule
{

class SDCardHost {

public:
	SDCardHost() {
		sdcard_ops_.initialize();
	}

	void process() {

		if (HAL_GetTick() - last_poll_tm_ > 200) {
			last_poll_tm_ = HAL_GetTick();

			bool card_detected = sd_.is_mounted(); //misnomer: should be sd.is_detected()

			if (is_detected_ && !card_detected) //unmount event
			{
				is_detected_ = false;
				if (sd_.unmount_disk()) {
					pr_trace("Unmounted SD\n");
					is_mounted_ = false;
				} else
					pr_err("Failed to unmount sd\n");
			}

			else if (!is_detected_ && card_detected) //mount event
			{
				is_detected_ = true;
				if (sd_.mount_disk()) {
					pr_trace("Mounted SD\n");
					is_mounted_ = true;
				} else
					pr_err("Failed to mount sd\n");
			}
			//
		}
	}

	FatFileIO &get_fileio() {
		return sd_;
	}

	bool is_mounted() {
		return is_mounted_;
	}

private:
	SDCardOps<SDCardConf> sdcard_ops_;
	FatFileIO sd_{&sdcard_ops_, Volume::SDCard};

	uint32_t last_poll_tm_ = 0;
	bool is_mounted_ = false;
	bool is_detected_ = false;
};

} // namespace MetaModule
