#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/smp_api.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/smp.hh"
#include "drivers/timekeeper.hh"
#include "dynload/plugin_manager.hh"
#include "fs/norflash_layout.hh"
#include "gui/ui.hh"
#include "internal_plugin_manager.hh"
#include "patch_play/patch_player.hh"

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

	auto patch_player = A7SharedMemoryS::ptrs.patch_player;
	auto patch_playloader = A7SharedMemoryS::ptrs.patch_playloader;
	auto file_storage_proxy = A7SharedMemoryS::ptrs.patch_storage;
	auto open_patch_manager = A7SharedMemoryS::ptrs.open_patch_manager;
	auto sync_params = A7SharedMemoryS::ptrs.sync_params;
	auto patch_mod_queue = A7SharedMemoryS::ptrs.patch_mod_queue;
	auto ramdisk_storage = A7SharedMemoryS::ptrs.ramdrive;

	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	RamDiskOps ramdisk_ops{*ramdisk_storage};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	AssetFS asset_fs{AssetVolFlashOffset};

	PluginManager plugin_manager{*file_storage_proxy, ramdisk};
	Ui ui{*patch_playloader, *file_storage_proxy, *open_patch_manager, *sync_params, *patch_mod_queue, plugin_manager};
	ui.update_screen();
	ui.update_page();

	InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};

	struct AuxCorePlayerContext {
		uint32_t starting_idx = 1;
		uint32_t num_modules = 0;
		uint32_t idx_increment = 2;
	} context;

	constexpr auto PlayModuleListIRQn = SMPControl::IRQn(SMPCommand::PlayModuleList);
	InterruptManager::register_and_start_isr(PlayModuleListIRQn, 1, 0, [&context, &patch_player]() {
		// Debug::Pin1::high();
		for (unsigned i = context.starting_idx; i < context.num_modules; i += context.idx_increment) {
			patch_player->modules[i]->update();
		}
		// Debug::Pin1::low();
		SMPThread::signal_done();
	});

	constexpr auto NewModuleListIRQn = SMPControl::IRQn(SMPCommand::NewModuleList);
	InterruptManager::register_and_start_isr(NewModuleListIRQn, 0, 0, [&context]() {
		context.starting_idx = SMPControl::read<SMPRegister::ModuleID>();
		context.num_modules = SMPControl::read<SMPRegister::NumModulesInPatch>();
		context.idx_increment = SMPControl::read<SMPRegister::UpdateModuleOffset>();
		SMPThread::signal_done();
	});

	constexpr auto ReadPatchLightsIRQn = SMPControl::IRQn(SMPCommand::ReadPatchLights);
	InterruptManager::register_and_start_isr(ReadPatchLightsIRQn, 2, 0, [patch_player, &ui]() {
		if (ui.new_patch_data == false) {

			for (auto &w : ui.lights().watch_lights) {
				if (w.is_active()) {
					auto val = patch_player->get_module_light(w.module_id, w.light_id);
					w.value = val;
				}
			}

			for (auto &d : ui.displays().watch_displays) {
				if (d.is_active()) {
					auto text = std::span<char>(d.text._data, d.text.capacity);
					patch_player->get_display_text(d.module_id, d.light_id, text);
				}
			}

			ui.new_patch_data = true;
		}

		SMPThread::signal_done();
	});

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

	while (true) {
		ui.update_screen();
		ui.update_page();
		__NOP();
	}
}
