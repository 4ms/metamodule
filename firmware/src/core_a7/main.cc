#include "app_startup.hh"
#include "audio/audio.hh"
#include "core_a7/static_buffers.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "fs/time_convert.hh"
#include "gui/ui.hh"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_file/patchlist.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
// #include "core_intercom/semaphore_action.hh" //TODO use this

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

	PatchPlayer patch_player;
	PatchStorageProxy patch_storage_proxy{
		StaticBuffers::raw_patch_data, StaticBuffers::icc_shared_message, StaticBuffers::shared_patch_file_list};
	PatchPlayLoader patch_playloader{patch_storage_proxy, patch_player};

	SyncParams param_cache;
	PatchModQueue patch_mod_queue;

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_playloader,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block,
					  patch_mod_queue};

	StaticBuffers::raw_patch_span = {StaticBuffers::raw_patch_data.data(), StaticBuffers::raw_patch_data.size()};
	SharedMemoryS::ptrs = {
		&StaticBuffers::param_blocks,
		&StaticBuffers::auxsignal_block,
		&StaticBuffers::virtdrive,
		&patch_player,
		&StaticBuffers::icc_shared_message,
		&StaticBuffers::shared_patch_file_list,
		&StaticBuffers::raw_patch_span,
	};

	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));
	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

	printf_("A7 initialized. Unlocking M4\n");

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	Ui ui{patch_playloader, patch_storage_proxy, param_cache, patch_mod_queue};
	param_cache.clear();
	//TODO: load the initial patch by getting patch_storage_proxy to make requests
	//to patch_storage...
	patch_playloader.load_initial_patch();

	ui.start();
	audio.start();

	while (true) {
		__WFI();
	}
}
