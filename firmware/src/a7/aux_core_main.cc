#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/smp.hh"
#include "patch_player.hh"
#include "shared_memory.hh"
#include "smp_api.hh"

extern "C" void aux_core_main()
{
	using namespace MetaModule;
	using namespace mdrivlib;

	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	auto patch_player = SharedMemory::read_address_of<PatchPlayer *>(SharedMemory::PatchPlayerLocation);

	while (true) {
		using namespace SMPRegister;

		__DSB();
		__WFI();
		auto irqnum = GIC_AcknowledgePending();
		GIC_EndInterrupt(irqnum);
		uint32_t command = irqnum;

		// Process a module command
		if (command == SMPCommand::UpdateModule) {
			Debug::Pin3::high();
			auto module_idx = SMPControl::read<ModuleID>();
			patch_player->modules[module_idx]->update();

			// signal we're done
			SMPControl::write<DoneZero>(0);
			// MainCore::send_sgi(SMPCommand::UpdateModule);
			Debug::Pin3::low();
		}

		// Update a param command
		if (command == SMPCommand::SetParam) {
			auto module_idx = SMPControl::read<ModuleID>();
			auto param_id = SMPControl::read<ParamID>();
			auto u32val = SMPControl::read<ParamVal>();
			auto val = *(reinterpret_cast<float *>(&u32val));
			patch_player->modules[module_idx]->set_param(param_id, val);
			// signal we're done
			SMPControl::write<DoneZero>(0);
		}

		// Run a function
		if (command == SMPThread::CallFunction) {
			SMPThread::execute();
		}
	}
}
