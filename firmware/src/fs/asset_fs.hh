#pragma once
#include "conf/qspi_flash_conf.hh"
#include "fs/littlefs/norflash_lfs.hh"
#include "fs/littlefs/norflash_ops.hh"
#include "lvgl.h"

namespace MetaModule
{

struct AssetFS {
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	LfsFileIO<AssetVolFlashOffset> lfs_io{flash};

	AssetFS() {
		lfs_io.initialize();

		// 		auto *lfs = lfs_io.get_lfs();
		// 		auto drv = lv_fs_littlefs_set_driver('M', lfs);
		// 		if (drv)
		// 			printf("%c: drv->userdata = %p\n", drv->letter, drv->user_data);
		// 		else
		// 			printf("drv is null\n");
	}
};

} // namespace MetaModule
