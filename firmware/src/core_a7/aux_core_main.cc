#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "core_a7/smp_api.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/smp.hh"
#include "drivers/timekeeper.hh"
#include "gui/ui.hh"
#include "lvgl.h"
#include "patch_play/patch_player.hh"

extern "C" void aux_core_main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	// Make m4 core wait for this core to be ready
	HWSemaphore<AuxCoreReady>::lock();

	// Wait for main core to be ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	pr_info("A7 Core 2 starting\n");

	auto patch_player = A7SharedMemoryS::ptrs.patch_player;
	auto patch_playloader = A7SharedMemoryS::ptrs.patch_playloader;
	auto patch_storage_proxy = A7SharedMemoryS::ptrs.patch_storage;
	auto sync_params = A7SharedMemoryS::ptrs.sync_params;
	auto patch_mod_queue = A7SharedMemoryS::ptrs.patch_mod_queue;

	Ui ui{*patch_playloader, *patch_storage_proxy, *sync_params, *patch_mod_queue};

	struct AuxCorePlayerContext {
		uint32_t starting_idx = 1;
		uint32_t num_modules = 0;
		uint32_t idx_increment = 2;
	} context;

	constexpr auto PlayModuleListIRQn = SMPControl::IRQn(SMPCommand::PlayModuleList);
	InterruptManager::register_and_start_isr(PlayModuleListIRQn, 1, 0, [&context, &patch_player]() {
		for (unsigned i = context.starting_idx; i < context.num_modules; i += context.idx_increment) {
			patch_player->modules[i]->update();
		}
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
			ui.new_patch_data = true;
		}

		SMPThread::signal_done();
	});

	// Signal that we're ready
	pr_info("A7 Core 2 initialized\n");
	HWSemaphore<AuxCoreReady>::unlock();

	while (HWSemaphore<M4CoreReady>::is_locked())
		;

	while (true) {
		ui.update();
		__NOP();
	}
}
