#include "aux_core_player.hh"
#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "dynload/plugin_manager.hh"
#include "fs/norflash_layout.hh"
#include "fs/syscall/filesystem.hh"
#include "fw_update/auto_updater.hh"
#include "gui/ui.hh"
#include "internal_plugin_manager.hh"
#include "load_test/test_manager.hh"
#include "ramdisk_ops.hh"
#include "rotocontrol.hh"

using FrameBufferT =
	std::array<lv_color_t, MetaModule::ScreenBufferConf::width * MetaModule::ScreenBufferConf::height / 4>;
static inline FrameBufferT framebuf1 alignas(64);
static inline FrameBufferT framebuf2 alignas(64);

extern "C" void aux_core_main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	// Tell A7 we're not ready yet
	HWSemaphore<AuxCoreReady>::lock();

	// Wait for m4 core to be ready
	while (HWSemaphore<MainCoreReady>::is_locked() || HWSemaphore<M4CoreReady>::is_locked())
		;

	pr_info("A7 Core 2 starting\n");

	start_module_threads();

#ifdef CONSOLE_USE_USB
	UartLog::use_usb(A7SharedMemoryS::ptrs.console_buffer);
#endif

	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	RamDiskOps ramdisk_ops{*A7SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	AssetFS asset_fs{AssetVolFlashOffset};
	Filesystem::init(ramdisk);
	auto &file_storage_proxy = *A7SharedMemoryS::ptrs.patch_storage;
	PluginManager plugin_manager{file_storage_proxy, ramdisk};
	Ui ui{*A7SharedMemoryS::ptrs.patch_playloader,
		  file_storage_proxy,
		  *A7SharedMemoryS::ptrs.open_patch_manager,
		  *A7SharedMemoryS::ptrs.sync_params,
		  *A7SharedMemoryS::ptrs.patch_mod_queue,
		  plugin_manager,
		  ramdisk};
	ui.update_screen();
	ui.update_page();

	InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};
	if (!internal_plugin_manager.asset_fs_valid) {
		ui.notify_error("Graphic assets are corrupted!\nRe-install firmware.");
	}

	RotoControl::init(A7SharedMemoryS::ptrs.console_cdc_buff);

	AuxPlayer aux_player{*A7SharedMemoryS::ptrs.patch_player, *A7SharedMemoryS::ptrs.open_patch_manager, ui};

	// Wait for M4 to be ready (so USB and SD are available)
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;

	hil_message("*ready\n");

	AutoUpdater::run(file_storage_proxy, ui);

	if (CpuLoadTest::should_run_tests(file_storage_proxy)) {
		CpuLoadTest::run_tests(file_storage_proxy, ui);
	} else {
		ui.preload_plugins();
	}

	hil_message("*initialized\n");

	// Signal that we're ready
	printf("A7 Core 2 initialized\n");

	HWSemaphore<AuxCoreReady>::unlock();

	ui.load_initial_patch();

	while (true) {
		ui.update_screen();
		ui.update_page();
		__NOP();
	}
}
