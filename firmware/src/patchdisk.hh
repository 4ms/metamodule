#pragma once
#include "conf/ramdisk_conf.hh"
#include "littlefs/norflash_lfs.hh"
#include "patchlist.hh"
#include "qspi_flash_driver.hh"
#include "ramdisk.hh"

namespace MetaModule
{
// PatchStorage transfers patches between NorFlash (littleFS) and the RamDisk (FatFS) and PatchList
class PatchStorage {
public:
	PatchStorage(mdrivlib::QSpiFlash &flash, RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &rmdisk);

	LittleNorFS::Status init_norflash();
	bool ramdisk_patches_to_norflash();
	bool norflash_patches_to_ramdisk();

	bool create_default_patches_in_norflash();

	bool fill_patchlist_from_norflash(PatchList &patch_list);

private:
	LittleNorFS lfs;
	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk;
};
} // namespace MetaModule
