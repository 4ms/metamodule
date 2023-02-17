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

	PatchPlayer patch_player; //on A7
	PatchPlayLoader patch_playloader{patch_player};
	//add a message queue for loading raw patch file data or complete yml data from M4
	//Can use an HSEM and shared ptr to PatchData on the heap:
	//M4 locks->writes->unlocks triggers A7 ISR to lock->load PatchData into player-> unlock
	//M4 would ignore, try again if it can't lock

	// "Thread"-shared data:
	ParamCache param_cache;		   //needed, same, right? syncs M4-gui and A7-audio?
	PatchModQueue patch_mod_queue; //queue lives on A7 but is now filled from M4 (gui)

	Ui ui{patch_playloader, param_cache, patch_mod_queue}; //on M4.
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

	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

	printf_("A7 initialized. Unlocking M4\n");

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

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
