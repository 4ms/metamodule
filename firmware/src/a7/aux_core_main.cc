#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/smp.hh"
#include "patch_player.hh"
#include "shared_memory.hh"

extern "C" void aux_core_main()
{
	using namespace MetaModule;

	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	auto patch_player = SharedMemory::read_address_of<PatchPlayer *>(SharedMemory::PatchPlayerLocation);

	while (true) {
		__DSB();
		__WFI();
		auto irqnum = GIC_AcknowledgePending();
		GIC_EndInterrupt(irqnum);

		// Process a module command
		if (irqnum == SGI1_IRQn) {
			// Debug::Pin3::high();

			auto module_idx = SMPControl::read();
			patch_player->modules[module_idx]->update();

			// Debug::Pin3::low();
			// Debug::Pin3::high();
			// auto sz = patch_player->modules[module_idx]->module_size();
			// mdrivlib::SystemCache::clean_dcache_by_range(patch_player->modules[module_idx].get(), sz);

			// signal we're done
			SMPControl::write(0);
			Debug::Pin3::low();
		}

		// Update a param command
		if (irqnum == SGI2_IRQn) {

			auto module_idx = SMPControl::read();
			auto param_id = SMPControl::read<29>();
			auto u32val = SMPControl::read<28>();
			auto val = *(reinterpret_cast<float *>(&u32val));
			patch_player->modules[module_idx]->set_param(param_id, val);
			// signal we're done
			SMPControl::write(0);
		}

		// Run a function
		if (irqnum == SGI3_IRQn) {
			auto thread_addr = SMPControl::read();
			auto thread_func = reinterpret_cast<std::function<void()> *>(thread_addr);
			thread_func->operator()();

			// signal we're done
			SMPControl::write(0);
			SMPControl::write<SMPThread::StatusReg>(SMPThread::NotRunning);
			Debug::Pin3::low();
		}
	}
}
