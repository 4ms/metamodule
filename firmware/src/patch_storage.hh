#include "a7/static_buffers.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "fatfs/fat_file_io.hh"
#include "fatfs/ramdisk_ops.hh"
#include "fatfs/sdcard_ops.hh"
#include "littlefs/norflash_lfs.hh"
#include "patch_fileio.hh"
#include "qspi_flash_driver.hh"

//TODO: Figure out how to handle NOR FLash internal patches
// - Ship with some patches on there
// - In Patch View, user can click "Save" or "copy" and give the patch a name and destination
// - In Patch List, patches show their location
// - Don't use RAMDisk USB
namespace MetaModule
{

// PatchStorage manages all patch filesystems <--> PatchList
struct PatchStorage {
	SDCardOps<SDCardConf> sdcard_ops;
	FatFileIO sdcard{&sdcard_ops, DiskID::SDCard};
	bool sdcard_valid = false;

	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	LfsFileIO norflash{flash};

	RamDiskOps ramdisk_ops{StaticBuffers::virtdrive};
	FatFileIO ramdisk{&ramdisk_ops, DiskID::RamDisk};

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

		// Populate Patch List
		patch_list.clear_all_patches();
		PatchFileIO::add_all_to_patchlist(norflash, patch_list);
		PatchFileIO::add_all_to_patchlist(sdcard, patch_list);

		// RamDisk: format it and copy patches to it
		// --Just for testing, really we should copy patches when USB MSC device starts
		// ramdisk.format_disk();
		// PatchFileIO::copy_patches_from_to(norflash, ramdisk);
		// PatchFileIO::copy_patches_from_to(sdcard, ramdisk);
	}

	void update_patchlist_from_sdcard() {
		printf_("Updating patchlist from SD Card.\n");
		patch_list.lock();
		{

			//TODO: clear just norflash patches
			patch_list.clear_all_patches();
			PatchFileIO::add_all_to_patchlist(norflash, patch_list);

			PatchFileIO::add_all_to_patchlist(sdcard, patch_list);
			patch_list.mark_modified();
		}
		patch_list.unlock();
		printf_("Patchlist updated.\n");
	}

	void update_norflash_from_ramdisk() {
		patch_list.lock();
		printf_("NOR Flash writeback begun.\r\n");

		ramdisk.unmount_disk();

		// Must invalidate the cache because M4 wrote to it???
		// SystemCache::invalidate_dcache_by_range(StaticBuffers::virtdrive.virtdrive,
		// 										sizeof(StaticBuffers::virtdrive.virtdrive));
		if (PatchFileIO::copy_patches_from_to(ramdisk, norflash, PatchFileIO::FileFilter::NewerTimestamp)) {
			printf_("NOR Flash writeback done. Refreshing patch list.\r\n");
			PatchFileIO::overwrite_patchlist(ramdisk, patch_list);
			patch_list.mark_modified();
		} else {
			printf_("NOR Flash writeback failed!\r\n");
		}
		patch_list.unlock();
		printf_("RamDisk Available to M4\n");
	}
};

} // namespace MetaModule
