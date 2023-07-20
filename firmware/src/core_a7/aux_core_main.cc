#include "conf/hsem_conf.hh"
#include "core_a7/smp_api.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/smp.hh"
#include "patch_play/patch_player.hh"

extern "C" void aux_core_main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	auto patch_player = SharedMemoryS::ptrs.patch_player;

	uint32_t starting_idx;
	uint32_t num_modules;
	uint32_t idx_increment;

	while (true) {
		using namespace SMPRegister;

		__DSB();
		__WFI();
		auto irqnum = GIC_AcknowledgePending();
		GIC_EndInterrupt(irqnum);
		uint32_t command = irqnum;

		switch (command) {
			case SMPCommand::UpdateModule: {
				auto module_idx = SMPControl::read<ModuleID>();
				patch_player->modules[module_idx]->update();
				SMPThread::signal_done();
			} break;

			case SMPCommand::UpdateListOfModules: {
				// Debug::Pin3::high();
				for (unsigned i = starting_idx; i < num_modules; i += idx_increment) {
					patch_player->modules[i]->update();
				}
				// Debug::Pin3::low();

				SMPThread::signal_done();
			} break;

			case SMPCommand::NewModuleList: {
				starting_idx = SMPControl::read<ModuleID>();
				num_modules = SMPControl::read<NumModulesInPatch>();
				idx_increment = SMPControl::read<UpdateModuleOffset>();
				SMPThread::signal_done();
			} break;

			case SMPThread::CallFunction:
				SMPThread::execute();
				break;

			default:
				break;
		}
	}
}
