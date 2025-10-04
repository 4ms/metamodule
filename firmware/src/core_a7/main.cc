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
#include "system/print_time.hh"
#include "uart_log.hh"

#include "fs/norflash_layout.hh"

#define A7_OWNS_SDCARD

#if defined A7_OWNS_SDCARD
#include "fs/fatfs/sd_host.hh"
#endif

namespace MetaModule
{

struct SystemInit : AppStartup, UartLog, Debug, Hardware {
} _sysinit;

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
#endif

#if defined A7_OWNS_SDCARD
	SDCardHost sd;
	std::array<ConcurrentBuffer *, 3> console_buffers;
	std::array<unsigned, 3> current_read_pos{};

	auto end_tm = HAL_GetTick() + 2000;
	while (HAL_GetTick() < end_tm) {
		sd.process();
	}

	sd.get_fileio().write_file("log.txt", "\n\nLOG BEGIN\n", FA_OPEN_APPEND);
#endif

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready: ~2400ms + more for preloading plugins
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked() || mdrivlib::HWSemaphore<AuxCoreReady>::is_locked())
		;

	StaticBuffers::sync_params.clear();

	audio.start();

	while (true) {
		__NOP();

		audio.handle_overruns();

		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}

#if defined A7_OWNS_SDCARD
		sd.process();

		for (auto i = 0u; auto *buff : console_buffers) {
			if (buff->writer_ref_count == 0) {
				auto start_pos = current_read_pos[i];
				unsigned end_pos = buff->current_write_pos;
				end_pos = end_pos & buff->buffer.SIZEMASK;

				if (start_pos > end_pos) {
					// Data to transmit spans the "seam" of the circular buffer,
					// Send the first chunk
					sd.get_fileio().write_file(
						"log.txt",
						{(char *)&buff->buffer.data[start_pos], buff->buffer.data.size() - start_pos},
						FA_OPEN_APPEND);
					current_read_pos[i] = 0;

				} else if (start_pos < end_pos) {
					sd.get_fileio().write_file(
						"log.txt", {(char *)&buff->buffer.data[start_pos], end_pos - start_pos}, FA_OPEN_APPEND);
					current_read_pos[i] = end_pos;
				}
			}
			i++;
		}

#endif
	}
}
