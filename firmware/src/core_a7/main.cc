#include "app_startup.hh"
#include "audio/audio.hh"
#include "audio/calibrator.hh"
#include "core_a7/a7_shared_memory.hh"
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

#include "conf/qspi_flash_conf.hh"
#include "drivers/pin.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/norflash_layout.hh"

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

	SharedMemoryS::ptrs = {
		&StaticBuffers::param_blocks,
		&StaticBuffers::auxsignal_block,
		&StaticBuffers::virtdrive,
		&StaticBuffers::icc_shared_message,
	};
	A7SharedMemoryS::ptrs = {
		&patch_player,
		&patch_playloader,
		&file_storage_proxy,
		&sync_params,
		&patch_mod_queue,
		&StaticBuffers::virtdrive,
	};

	mdrivlib::SystemCache::clean_dcache_by_range(&StaticBuffers::virtdrive, sizeof(StaticBuffers::virtdrive));
	mdrivlib::SystemCache::clean_dcache_by_range(&A7SharedMemoryS::ptrs, sizeof(A7SharedMemoryS::ptrs));
	mdrivlib::SystemCache::clean_dcache_by_range(&SharedMemoryS::ptrs, sizeof(SharedMemoryS::ptrs));
	HWSemaphoreCoreHandler::enable_global_ISR(3, 3);

#ifdef ENABLE_WIFI_BRIDGE
	WifiUpdate::run();
#endif

	// prevents M4 from using it as a USBD device: TODO remove this or remove usb_device in M4, or make it a config option to enable USB MSC Device mode
	mdrivlib::HWSemaphore<MetaModule::RamDiskLock>::lock(0);

	pr_info("A7 Core 1 initialized\n");

	// Tell other cores we're done with init
	mdrivlib::HWSemaphore<MainCoreReady>::unlock();

	// wait for other cores to be ready
	while (mdrivlib::HWSemaphore<AuxCoreReady>::is_locked() && mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;

	sync_params.clear();
	patch_playloader.load_initial_patch();

	//TODO:
	AudioInCalibrator cal;
	if (!cal.read_calibration(audio)) {
		cal.calibrate(audio);
	} else
		audio.start();

	//std::array<std::pair<float, float>, PanelDef::NumAudioIn> caldata;
	//mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	//bool do_calibrate = true;

	//if (flash_.read(reinterpret_cast<uint8_t *>(caldata.data()), CalDataFlashOffset, sizeof caldata)) {
	//	bool valid_data_found = true;
	//	//validate
	//	for (auto chan : caldata) {
	//		pr_info("Read: %f %f\n", chan.first, chan.second);
	//		if (isnanf(chan.first) || isnanf(chan.second) || chan.first < -100'000.f || chan.first > 100'000.f ||
	//			chan.second < 3'000'000.f || chan.second > 3'500'000.f)
	//		{
	//			valid_data_found = false;
	//		}
	//	}
	//	if (valid_data_found) {
	//		pr_info("Cal data validated\n");
	//		audio.set_calibration<0, 4000>(caldata);
	//		do_calibrate = false;
	//	} else {
	//		pr_info("Cal data invalid\n");
	//		do_calibrate = true;
	//	}
	//}

	//if (do_calibrate) {
	//	std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> cal_readings;
	//	audio.start();
	//	audio.start_calibration_mode(cal_readings);

	//	HAL_Delay(1000);

	//	pr_dbg("Ready to calibrate: patch 0V and press the back button\n");

	//	mdrivlib::
	//		FPin<mdrivlib::GPIO::D, mdrivlib::PinNum::_8, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>
	//			button0{mdrivlib::PinPull::Up};

	//	while (!button0.read())
	//		;
	//	while (button0.read())
	//		;

	//	audio.step_calibration();
	//	HAL_Delay(1000);
	//	for (auto [i, ain] : enumerate(cal_readings)) {
	//		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
	//			   i,
	//			   (int)(ain.iir),				// * 32768.f),
	//			   (int)(ain.min),				// * 32768.f),
	//			   (int)(ain.max),				// * 32768.f),
	//			   (int)((ain.max - ain.min))); // * 32768.f));
	//		caldata[i].first = ain.iir;
	//	}

	//	pr_dbg("Ready: patch 4V and press the back button\n");
	//	while (!button0.read())
	//		;
	//	while (button0.read())
	//		;

	//	audio.step_calibration();
	//	HAL_Delay(1000);
	//	for (auto [i, ain] : enumerate(cal_readings)) {
	//		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
	//			   i,
	//			   (int)(ain.iir),				// * 32768.f),
	//			   (int)(ain.min),				// * 32768.f),
	//			   (int)(ain.max),				// * 32768.f),
	//			   (int)((ain.max - ain.min))); // * 32768.f));
	//		caldata[i].second = ain.iir;
	//	}

	//	if (!flash_.write(reinterpret_cast<uint8_t *>(caldata.data()), CalDataFlashOffset, sizeof caldata))
	//		pr_err("Could not write cal data to flash\n");
	//	audio.set_calibration<0, 4000>(caldata);
	//	audio.end_calibration_mode();
	//} else
	//	audio.start();

	print_time();

	while (true) {
		__NOP();
	}
}
