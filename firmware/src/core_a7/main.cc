#include "../patches/default/LC100.hh"
#include "app_startup.hh"
#include "audio/audio.hh"
#include "calibrate/calibration_data_reader.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/static_buffers.hh"
#include "core_intercom/semaphore_action.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "git_version.h"
#include "hsem_handler.hh"
#include "internal_plugin_manager.hh"
#include "patch_play/patch_player.hh"
#include "system/print_time.hh"
#include "uart_log.hh"

#include "fs/norflash_layout.hh"
#include "yaml_to_patch.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, UartLog, Debug, ListenClosely::Hardware {
} _sysinit;

} // namespace MetaModule

int main() {
	using namespace MetaModule;

	StaticBuffers::init();

	HAL_Delay(50);
	print_time();
	printf("Build: %s (%s)\n", GIT_HASH.data(), GIT_COMMIT_TIME.data());
	printf("Version: %s\n", GIT_FIRMWARE_VERSION_TAG.data());

	PatchPlayer patch_player;

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  StaticBuffers::param_blocks};

	SharedMemoryS::ptrs = {
		&StaticBuffers::param_blocks,
		&StaticBuffers::console_a7_0_buff,
		&StaticBuffers::console_a7_1_buff,
		&StaticBuffers::console_m4_buff,
	};

	A7SharedMemoryS::ptrs = {
		&StaticBuffers::console_a7_1_buff,
	};

	audio.set_calibration(CalibrationDataReader::read_calibration_or_defaults(FlashLoader{}, CalDataFlashOffset));

	mdrivlib::SystemCache::clean_dcache_by_range(&A7SharedMemoryS::ptrs, sizeof(A7SharedMemoryS::ptrs));
	mdrivlib::SystemCache::clean_dcache_by_range(&SharedMemoryS::ptrs, sizeof(SharedMemoryS::ptrs));
	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

	// prevents M4 from using it as a USBD device:
	mdrivlib::HWSemaphore<MetaModule::RamDiskLock>::lock(0);
	// Invalidate our I cache when plugin code is loaded
	SemaphoreActionOnUnlock<InvalidateICache> clean_cache([] { mdrivlib::SystemCache::invalidate_icache(); });

	pr_info("A7 Core 1 initialized\n");

#ifdef CONSOLE_USE_USB
	printf("Stopping UART buffer\n");
	UartLog::use_usb(&StaticBuffers::console_a7_0_buff);
	printf("Using USB buffer\n");
#endif

	InternalPluginManager internal_plugin_manager;

	// Load initial patch file
	PatchData patch;
	std::string p{LC100_patch};
	yaml_raw_to_patch(p, patch);
	patch_player.load_patch(patch);

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready: ~2400ms + more for preloading plugins
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked() || mdrivlib::HWSemaphore<AuxCoreReady>::is_locked())
		;

	audio.start();

	while (true) {
		__NOP();

		audio.handle_overruns();

		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}
	}
}
