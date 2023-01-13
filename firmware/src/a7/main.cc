#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include "fatfs/fat_fileio.hh"
#include "fatfs/ramdisk_ops.hh"
#include "fatfs/sdcard_ops.hh"
#include "hsem_handler.hh"
#include "littlefs/norflash_lfs.hh"
#include "params.hh"
#include "patch_loader.hh"
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "patchstorage.hh"
#include "qspi_flash_driver.hh"
#include "semaphore_action.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "time_convert.hh"
#include "ui.hh"

namespace MetaModule
{

constexpr inline bool reset_to_factory_patches = false;

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	HAL_Delay(200);

	auto now = ticks_to_fattime(HAL_GetTick());
	printf_("%u/%u/%u %u:%02u:%02u\n", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());

	// SD Card
	FatFileIO<SDCardOps<SDCardConf>, DiskID::SDCard> sdcard;

	// NOR Flash -- just for testing our API (probably won't put patches there)
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	LittleNorFS norflash{flash};
	auto status = norflash.initialize();
	if (status == LittleNorFS::Status::AlreadyFormatted || reset_to_factory_patches) {
		norflash.reformat();
		PatchStorage::create_default_patches(norflash);
	}

	// RamDisk: format it and copy patches to it
	// --Just for testing, really we should copy patches when USB MSC device starts
	FatFileIO<RamDiskOps, DiskID::RamDisk> ramdisk{StaticBuffers::virtdrive};
	ramdisk.format_disk();
	PatchStorage::copy_patches_from_to(norflash, ramdisk);
	PatchStorage::copy_patches_from_to(sdcard, ramdisk);

	// Populate Patch List
	PatchList patch_list{};
	PatchStorage::overwrite_patchlist(norflash, patch_list);
	PatchStorage::add_to_patchlist(sdcard, patch_list);

	PatchPlayer patch_player;
	PatchLoader patch_loader{patch_list, patch_player};

	// "Thread"-shared data:
	ParamCache param_cache;
	MessageQueue mbox;
	PatchModQueue patch_mod_queue;

	Ui ui{patch_loader, patch_list, param_cache, mbox, patch_mod_queue};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_loader,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block,
					  patch_mod_queue};

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);
	SharedMemory::write_address_of(&StaticBuffers::virtdrive, SharedMemory::RamDiskLocation);
	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));

	param_cache.clear();
	patch_loader.load_initial_patch();

	HWSemaphore<RamDiskLock>::unlock();

	SemaphoreActionOnUnlock<RamDiskLock> ramdisk_readback([&] {
		if (HWSemaphore<RamDiskLock>::lock(1) == HWSemaphoreFlag::LockFailed) {
			printf_("Error getting lock on RamDisk to read back\n");
			return;
		}
		patch_list.lock();
		printf_("NOR Flash writeback begun.\r\n");
		ramdisk.unmount_disk();

		// Must invalidate the cache because M4 wrote to it???
		// SystemCache::invalidate_dcache_by_range(StaticBuffers::virtdrive.virtdrive,
		// 										sizeof(StaticBuffers::virtdrive.virtdrive));
		if (PatchStorage::copy_patches_from_to(ramdisk, norflash)) {
			printf_("NOR Flash writeback done. Refreshing patch list.\r\n");
			PatchStorage::overwrite_patchlist(ramdisk, patch_list);
			patch_list.mark_modified();
		} else {
			printf_("NOR Flash writeback failed!\r\n");
		}
		patch_list.unlock();
		printf_("RamDisk Available to M4\n");
		HWSemaphore<RamDiskLock>::unlock_nonrecursive(1);
	});

	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

	printf_("A7 initialized. Unlocking M4\n");

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	audio.start();
	ui.start();

	while (true) {
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
