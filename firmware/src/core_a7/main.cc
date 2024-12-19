#include "app_startup.hh"
#include "audio/audio.hh"
#include "calibrate/calibration_data_reader.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/async_thread_control.hh"
#include "core_a7/static_buffers.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "fs/time_convert.hh"
#include "git_version.h"
#include "hsem_handler.hh"
#include "load_test/test_modules.hh"
#include "params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "system/time.hh"
#include "uart_log.hh"

#include "conf/qspi_flash_conf.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/norflash_layout.hh"

#ifdef CPU_TEST_ALL_MODULES
#include "conf/pin_conf.hh"
#include "fs/general_io.hh"
#include "load_test/tester.hh"
#endif

#ifdef ENABLE_WIFI_BRIDGE
#include <wifi_update.hh>
#endif

namespace MetaModule
{

struct SystemInit : AppStartup, UartLog, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	HAL_Delay(50);
	print_time();
	pr_info("Build: %s (%s)\n", GIT_HASH.data(), GIT_COMMIT_TIME.data());
	pr_info("Version: %s\n", GIT_FIRMWARE_VERSION_TAG.data());

	PatchPlayer patch_player;
	FileStorageComm patch_comm{StaticBuffers::icc_shared_message};
	FileStorageProxy file_storage_proxy{StaticBuffers::raw_patch_data, patch_comm, StaticBuffers::patch_dir_list};
	OpenPatchManager open_patches_manager;
	PatchPlayLoader patch_playloader{file_storage_proxy, open_patches_manager, patch_player};

	PatchModQueue patch_mod_queue;

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  StaticBuffers::sync_params,
					  patch_playloader,
					  StaticBuffers::param_blocks,
					  patch_mod_queue};

	SharedMemoryS::ptrs = {
		&StaticBuffers::param_blocks,
		&StaticBuffers::virtdrive,
		&StaticBuffers::icc_shared_message,
		&StaticBuffers::console_a7_0_buff,
		&StaticBuffers::console_a7_1_buff,
		&StaticBuffers::console_m4_buff,
	};

	A7SharedMemoryS::ptrs = {
		&patch_player,
		&patch_playloader,
		&file_storage_proxy,
		&open_patches_manager,
		&StaticBuffers::sync_params,
		&patch_mod_queue,
		&StaticBuffers::virtdrive,
		&StaticBuffers::console_a7_1_buff,
	};

	{
		CalibrationDataReader cal;
		audio.set_calibration(cal.read_calibration_or_defaults(FlashLoader{}, CalDataFlashOffset));
	}

	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));
	mdrivlib::SystemCache::clean_dcache_by_range(&A7SharedMemoryS::ptrs, sizeof(A7SharedMemoryS::ptrs));
	mdrivlib::SystemCache::clean_dcache_by_range(&SharedMemoryS::ptrs, sizeof(SharedMemoryS::ptrs));
	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

#ifdef ENABLE_WIFI_BRIDGE
	WifiUpdate::run();
#endif

	// prevents M4 from using it as a USBD device:
	mdrivlib::HWSemaphore<MetaModule::RamDiskLock>::lock(0);

	pr_info("A7 Core 1 initialized\n");
	// Note: from after the HAL_Delay(50) until here, it takes 20ms

#ifdef CONSOLE_USE_USB
	printf("Stopping UART buffer\n");
	UartLog::use_usb(&StaticBuffers::console_a7_0_buff);
	printf("Using USB buffer\n");
#endif

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready: ~2400ms + more for auto-loading plugins
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked() || mdrivlib::HWSemaphore<AuxCoreReady>::is_locked())
		;

		// ~290ms until while loop

#ifdef CPU_TEST_ALL_MODULES
	mdrivlib::HWSemaphore<MainCoreReady>::lock();

	mdrivlib::Pin but0{
		ControlPins::but0, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up, mdrivlib::PinPolarity::Inverted};
	if (but0.is_on()) {
		auto db = LoadTest::test_all_modules();
		auto filedata = LoadTest::entries_to_csv(db);
		FS::write_file(file_storage_proxy, filedata, {"cpu_test.csv", Volume::USB});
	}

	mdrivlib::HWSemaphore<MainCoreReady>::unlock();
#endif

	StaticBuffers::sync_params.clear();

	audio.start();

	print_time();

	start_module_threads();

	while (true) {
		__NOP();
		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}
	}
}
