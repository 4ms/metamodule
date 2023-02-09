#include "app_startup.hh"
#include "audio.hh"
// #include "conf/board_codec_conf.hh"
#include "debug.hh"
// #include "drivers/hsem.hh"
// #include "drivers/stm32xx.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_fileio.hh"
#include "patch_loader.hh"
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "patch_storage.hh"
#include "patchlist.hh"
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
	printf_("Current Time: %u/%u/%u %u:%02u:%02u\n",
			now.year(),
			now.month(),
			now.day(),
			now.hour(),
			now.minute(),
			now.second());

	PatchList patch_list{};
	PatchStorage patch_storage{patch_list};

	PatchPlayer patch_player;
	PatchLoader patch_loader{patch_list, patch_player};

	// "Thread"-shared data:
	ParamCache param_cache;
	PatchModQueue patch_mod_queue;

	Ui ui{patch_loader, patch_list, param_cache, patch_mod_queue};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_loader,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block,
					  patch_mod_queue};

	//TODO: create struct with fields for each address, and write addr of the struct
	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);
	SharedMemory::write_address_of(&StaticBuffers::virtdrive, SharedMemory::RamDiskLocation);
	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));

	param_cache.clear();
	patch_loader.load_initial_patch();

	HWSemaphore<RamDiskLock>::unlock();

	SemaphoreActionOnUnlock<RamDiskLock> ramdisk_readback([&patch_storage] {
		if (HWSemaphore<RamDiskLock>::lock(1) == HWSemaphoreFlag::LockFailed) {
			printf_("Error getting lock on RamDisk to read back\n");
			return;
		}
		patch_storage.update_norflash_from_ramdisk();
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
