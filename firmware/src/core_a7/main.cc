#include "app_startup.hh"
#include "audio/audio.hh"
#include "core_a7/static_buffers.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "fs/time_convert.hh"
#include "git_version.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "system/time.hh"
#include "uart_log.hh"

// #include "core_intercom/semaphore_action.hh" //TODO use this

namespace MetaModule
{

constexpr inline bool reset_to_factory_patches = false;

struct SystemInit : AppStartup, UartLog, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	HAL_Delay(50);
	print_time();
	printf("Build: %s (%s)\n", GIT_HASH.data(), GIT_COMMIT_TIME.data());
	printf("Version: %s\n", GIT_FIRMWARE_VERSION_TAG.data());

	PatchPlayer patch_player;
	FileStorageProxy file_storage_proxy{
		StaticBuffers::raw_patch_data, StaticBuffers::icc_shared_message, StaticBuffers::patch_dir_list};
	PatchPlayLoader patch_playloader{file_storage_proxy, patch_player};

	SyncParams sync_params;
	PatchModQueue patch_mod_queue;

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  sync_params,
					  patch_playloader,
					  StaticBuffers::param_blocks,
					  patch_mod_queue};

	StaticBuffers::raw_patch_span = {StaticBuffers::raw_patch_data.data(), StaticBuffers::raw_patch_data.size()};
	SharedMemoryS::ptrs = {&StaticBuffers::param_blocks,
						   &StaticBuffers::auxsignal_block,
						   &StaticBuffers::virtdrive,
						   &StaticBuffers::icc_shared_message,
						   &StaticBuffers::raw_patch_span, //DEPRECATE
						   &patch_player,
						   &patch_playloader,
						   &file_storage_proxy,
						   &sync_params,
						   &patch_mod_queue};

	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));
	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

	pr_info("A7 Core 1 initialized\n");

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready
	while (mdrivlib::HWSemaphore<AuxCoreReady>::is_locked() && mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;

	sync_params.clear();
	patch_playloader.load_initial_patch();

	audio.start();
	print_time();

	while (true) {
		__NOP();
	}
}
