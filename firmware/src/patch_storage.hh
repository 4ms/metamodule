#include "a7/static_buffers.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "fatfs/fat_fileio.hh"
#include "fatfs/ramdisk_ops.hh"
#include "fatfs/sdcard_ops.hh"
#include "littlefs/norflash_lfs.hh"
#include "patch_fileio.hh"
#include "qspi_flash_driver.hh"

namespace MetaModule
{

// PatchStorage manages all patch filesystems <--> PatchList
struct PatchStorage {
	FatFileIO<SDCardOps<SDCardConf>, DiskID::SDCard> sdcard;
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	LfsFileIO norflash{flash};
	FatFileIO<RamDiskOps, DiskID::RamDisk> ramdisk{StaticBuffers::virtdrive};
	PatchList &patch_list;

	PatchStorage(PatchList &patch_list, bool reset_to_factory_patches = false)
		: patch_list{patch_list} {

		// NOR Flash: if it's unformatted, put default patches there
		//-- just for testing our API (probably won't put patches there)
		auto status = norflash.initialize();
		if (status == LfsFileIO::Status::NewlyFormatted || reset_to_factory_patches) {
			norflash.reformat();
			PatchFileIO::create_default_patches(norflash);
		}

		// RamDisk: format it and copy patches to it
		// --Just for testing, really we should copy patches when USB MSC device starts
		ramdisk.format_disk();
		PatchFileIO::copy_patches_from_to(norflash, ramdisk);
		PatchFileIO::copy_patches_from_to(sdcard, ramdisk);

		// Populate Patch List
		PatchFileIO::overwrite_patchlist(norflash, patch_list);
		PatchFileIO::add_to_patchlist(sdcard, patch_list);
	}
};

} // namespace MetaModule
