#include "app_startup.hh"
#include "audio/audio.hh"
#include "calibrate/calibration_data_reader.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/static_buffers.hh"
#include "core_intercom/semaphore_action.hh"
#include "core_intercom/shared_memory.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "git_version.h"
#include "hsem_handler.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "system/time.hh"
#include "uart_log.hh"

#include "fs/norflash_layout.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, UartLog, Debug, Hardware {
} _sysinit;

// Binary command handling for firmware version
void send_fw_version() {
	// Command format: 0x5A 0x01 0x01 0x00 0x00
	// Where:
	// 0x5A = start byte
	// 0x01 = command type (GENERAL)
	// 0x01 = command subtype (GET FW VERSION)
	// 0x00 0x00 = command length (2 bytes, MSB first)
	
	// Make sure there's a small gap before binary data
	HAL_Delay(50);
	
	uint8_t command[5] = {0x5A, 0x01, 0x01, 0x00, 0x00};
	
	// Send the command directly without using printf before/after
	UartLog::write_binary_usb(command, sizeof(command));
	
	// Add a small delay after binary data
	HAL_Delay(50);
}

// SET MODE command
void send_set_mode() {
	// Command format: 0x5A 0x01 0x03 0x00 0x02 0x01 0x00
	// Where:
	// 0x5A = start byte
	// 0x01 = command type (GENERAL)
	// 0x03 = command subtype (SET MODE)
	// 0x00 0x02 = command length (2 bytes, MSB first) = 2 bytes
	// 0x01 = mode: PLUGIN (01)
	// 0x00 = page index: 00 = Page 1
	
	// Make sure there's a small gap before binary data
	HAL_Delay(50);
	
	uint8_t command[7] = {0x5A, 0x01, 0x03, 0x00, 0x02, 0x01, 0x00};
	
	// Send the command directly without using printf before/after
	UartLog::write_binary_usb(command, sizeof(command));
	
	// Add a small delay after binary data
	HAL_Delay(50);
}

} // namespace MetaModule

int main() {
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
		&StaticBuffers::icc_module_fs_message_core0,
		&StaticBuffers::icc_module_fs_message_core1,
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

	// prevents M4 from using it as a USBD device:
	mdrivlib::HWSemaphore<MetaModule::RamDiskLock>::lock(0);
	// Invalidate our I cache when plugin code is loaded
	SemaphoreActionOnUnlock<InvalidateICache> clean_cache([] { mdrivlib::SystemCache::invalidate_icache(); });

	start_module_threads();

	pr_info("A7 Core 1 initialized\n");
	// Note: from after the HAL_Delay(50) until here, it takes 20ms

#ifdef CONSOLE_USE_USB
	printf("Stopping UART buffer\n");
	UartLog::use_usb(&StaticBuffers::console_a7_0_buff);
	printf("Using USB buffer\n");
	
	// Add a delay to make sure text output is complete
	HAL_Delay(100);
	
	// Send binary commands
	send_fw_version();
	send_set_mode();
	
	// Return to normal text output
	HAL_Delay(100);
	printf("Binary commands sent\n");
#endif

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready: ~2400ms + more for preloading plugins
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked() || mdrivlib::HWSemaphore<AuxCoreReady>::is_locked())
		;

	StaticBuffers::sync_params.clear();

	audio.start();

	print_time();

	while (true) {
		__NOP();

		audio.handle_overruns();

		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}
	}
}
