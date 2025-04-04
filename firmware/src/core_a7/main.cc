#include "app_startup.hh"
#include "audio/audio.hh"
#include "calibrate/calibration_data_reader.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/static_buffers.hh"
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

#include "CoreModules/4ms/tests/djembe-selfcontained-test.hh"

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

	{
		volatile float out;
		struct Params {
			unsigned hit_ctr = 0;
			unsigned hit_rate = 12'000;
			std::array<bool, 4> knob_changed{true, true, true, true};
			std::array<float, 4> knobs{0.5f, 0.5f, 0.5f, 0.5f};
		} params;

		DjembeSelfContained::MetaModule::DjembeCore dj;
		dj.set_samplerate(48000);
		dj.set_param(0, 0.5f);
		dj.set_param(1, 0.5f);
		dj.set_param(2, 0.5f);
		dj.set_param(3, 0.5f);
		dj.set_input(0, 0);
		dj.set_input(1, 0);
		dj.set_input(2, 0);
		dj.set_input(3, 0);
		dj.set_input(4, 0);

		Debug::Pin1::high();
		for (auto i = 0u; i < 48000; i++) {
			Debug::Pin0::high();
			params.hit_ctr++;

			for (auto knob_id = 0; auto &changed : params.knob_changed) {
				if (changed) {
					dj.set_param(knob_id, params.knobs[knob_id]);
					changed = false;
				}
				knob_id++;
			}

			dj.set_input(4, params.hit_ctr % params.hit_rate == 0 ? 1 : 0);
			dj.update();

			out = dj.get_output(0);
			Debug::Pin0::low();
		}
		Debug::Pin1::low();
	}

	start_module_threads();

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
