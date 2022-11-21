#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
// #include "fatfs/ramdisk_fileio.hh"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_loader.hh"
#include "patch_player.hh"
#include "patchfileio.hh"
#include "patchlist.hh"
#include "patchstorage.hh"
#include "ramdisk_ops.hh"
#include "semaphore_action.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "ui.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	HAL_Delay(100);
	// Setup RAM disk: ~300us on A7 for 4MB disk
	RamDiskOps ramdiskops{StaticBuffers::virtdrive};
	RamDiskFileIO::register_disk(&ramdiskops, Disk::RamDisk);
	RamDiskFileIO::format_disk(Disk::RamDisk);

	// Setup Patch Storage on QSPI flash and load patches to RamDisk
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	PatchStorage patchdisk{flash}; //TODO: add object for RamDiskFileIO

	// Populate Patch List from Patch Storage
	PatchList patch_list{};
	patchdisk.factory_clean(); //Remove this when not testing!
	patchdisk.fill_patchlist_from_norflash(patch_list);
	patchdisk.norflash_patches_to_ramdisk();

	PatchPlayer patch_player;
	PatchLoader patch_loader{patch_list, patch_player};

	ParamCache param_cache;
	UiAudioMailbox mbox;

	Ui ui{patch_loader, patch_list, param_cache, mbox};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_loader,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

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
			printf("Error getting lock on RamDisk to read back\n");
			return;
		}
		patch_list.lock();
		printf_("NOR Flash writeback begun.\r\n");
		RamDiskFileIO::unmount_disk(Disk::RamDisk);
		if (patchdisk.ramdisk_patches_to_norflash()) {
			printf_("NOR Flash writeback done. Refreshing patch list.\r\n");
			patch_list.mark_modified();
		} else {
			printf_("NOR Flash writeback failed!\r\n");
		}
		patch_list.unlock();
		printf("RamDisk Available to M4\n");
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
