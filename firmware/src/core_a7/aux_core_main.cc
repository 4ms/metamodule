#include "aux_core_player.hh"
#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/async_thread_control.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "dynload/plugin_manager.hh"
#include "fs/filesystem.hh"
#include "fs/norflash_layout.hh"
#include "gui/ui.hh"
#include "internal_plugin_manager.hh"

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

#ifdef CONSOLE_USE_USB
	UartLog::use_usb(A7SharedMemoryS::ptrs.console_buffer);
#endif

	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	RamDiskOps ramdisk_ops{*A7SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	AssetFS asset_fs{AssetVolFlashOffset};
	Filesystem::Init(ramdisk);
	PluginManager plugin_manager{*A7SharedMemoryS::ptrs.patch_storage, ramdisk};
	Ui ui{*A7SharedMemoryS::ptrs.patch_playloader,
		  *A7SharedMemoryS::ptrs.patch_storage,
		  *A7SharedMemoryS::ptrs.open_patch_manager,
		  *A7SharedMemoryS::ptrs.sync_params,
		  *A7SharedMemoryS::ptrs.patch_mod_queue,
		  plugin_manager,
		  ramdisk};
	ui.update_screen();
	ui.update_page();

	InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};

	AuxPlayer aux_player{*A7SharedMemoryS::ptrs.patch_player, ui};

	// Wait for M4 to be ready (so USB and SD are available)
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;
	ui.autoload_plugins();

	// Signal that we're ready
	pr_info("A7 Core 2 initialized\n");
	HWSemaphore<AuxCoreReady>::unlock();

#ifdef CPU_TEST_ALL_MODULES
	// Wait for main core to be done with testing all modules
	HAL_Delay(50);
	while (mdrivlib::HWSemaphore<MainCoreReady>::is_locked()) {
		ui.update_screen();
	};
#endif

	ui.load_initial_patch();

	start_module_threads();

	while (true) {
		ui.update_screen();
		ui.update_page();
		__NOP();
	}
}
