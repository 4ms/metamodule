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
			Debug::Pin3::high();

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

		// Flush Cache command
		if (irqnum == SGI2_IRQn) {
			// flush cache
			// mdrivlib::SystemCache::clean_dcache();
			// signal we're done
			SMPControl::write(0);
		}
	}
}
