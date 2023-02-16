#include "app_startup.hh"
#include "audio.hh"
#include "debug.hh"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_fileio.hh"
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "patch_playloader.hh"
#include "patch_storage.hh"
#include "patchlist.hh"
#include "semaphore_action.hh"
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

	PatchStorage patch_storage; //on M4
	PatchPlayer patch_player;	//on A7
	PatchPlayLoader patch_playloader{patch_player,
									 patch_storage}; //patch_storage => message queue for loading raw patch file data
	//PatchPlayLoader is on A7? It gets raw data from PatchStorage on M4, runs yaml_to_patch, and loads that into PatchPlayer

	// "Thread"-shared data:
	ParamCache param_cache;		   //needed, same, right? syncs M4-gui and A7-audio?
	PatchModQueue patch_mod_queue; //queue lives on A7 but is now filled from M4 (gui)

	Ui ui{patch_playloader, patch_storage, param_cache, patch_mod_queue}; //on M4.
	//PatchPlayerLoader(A7) => a way to know what the currently playing patch is, and to request loading a new patch
	//Gui uses PatchPlayLoader for cur_patch_index()->int and request_load_patch(id)

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_playloader,
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
	patch_playloader.load_initial_patch("enosc");

	// RamDisk goes away
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

	auto *testpd = new PatchData;
	auto patchraw = DefaultPatches::get_patch(0);
	Debug::Pin2::high();
	yaml_raw_to_patch(patchraw,  *testpd);
	Debug::Pin2::low();

	printf_("A7 initialized. Unlocking M4\n");

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	//Test m4's ability to convert a patch
	auto pd = SharedMemory::read_address_of<PatchData *>(SharedMemory::PatchDataLocation);
	printf_("A7: pd ptr = %p\n", pd);
	printf_("A7: patch name: %.31s\n", pd->patch_name.c_str());
	printf_("A7: Num Modules: %d, Num static knobs: %d\n", pd->module_slugs.size(), pd->static_knobs.size());
	for (auto &n : pd->module_slugs)
		printf_("   [%s]\n", n.c_str());
	for (auto &n : pd->static_knobs)
		printf_("   Knob: %d %d %f\n", n.module_id, n.param_id, (double)n.value);
	//////////////

	audio.start();
	ui.start(); //=>M4
	//Probably need some sort of PatchPlayLoader queue checker (to check for new patch load requests)

	while (true) {
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
