#include "conf/hsem_conf.hh"
#include "core_a7/smp_api.hh"
#include "core_intercom/shared_memory.hh"
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

	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	auto patch_player = SharedMemoryS::ptrs.patch_player;
	auto patch_playloader = SharedMemoryS::ptrs.patch_playloader;
	auto patch_storage_proxy = SharedMemoryS::ptrs.patch_storage;
	auto sync_params = SharedMemoryS::ptrs.sync_params;
	auto patch_mod_queue = SharedMemoryS::ptrs.patch_mod_queue;

	struct AuxCorePlayerContext {
		uint32_t starting_idx;
		uint32_t num_modules;
		uint32_t idx_increment;
	} context;

	// UpdateListOfModules
	InterruptManager::register_and_start_isr(SGI4_IRQn, 0, 0, [&context, &patch_player]() {
		for (unsigned i = context.starting_idx; i < context.num_modules; i += context.idx_increment) {
			patch_player->modules[i]->update();
		}
		SMPThread::signal_done();
	});

	// NewModuleList
	InterruptManager::register_and_start_isr(SGI2_IRQn, 0, 0, [&context]() {
		context.starting_idx = SMPControl::read<SMPRegister::ModuleID>();
		context.num_modules = SMPControl::read<SMPRegister::NumModulesInPatch>();
		context.idx_increment = SMPControl::read<SMPRegister::UpdateModuleOffset>();
		SMPThread::signal_done();
	});

	// UpdateModule
	InterruptManager::register_and_start_isr(SGI1_IRQn, 0, 0, [&patch_player]() {
		auto module_idx = SMPControl::read<SMPRegister::ModuleID>();
		patch_player->modules[module_idx]->update();
		SMPThread::signal_done();
	});

	// CallFunction
	InterruptManager::register_and_start_isr(SGI3_IRQn, 0, 0, []() { SMPThread::execute(); });

	Ui ui{*patch_playloader, *patch_storage_proxy, *sync_params, *patch_mod_queue};
	ui.start();

	while (true) {
		__WFI();
	}
}
