#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "patch_player.hh"
#include "shared_memory.hh"

extern "C" void aux_core_main()
{
	using namespace MetaModule;

	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	auto patch_player = SharedMemory::read_address_of<PatchPlayer *>(SharedMemory::PatchPlayerLocation);

	while (true) {
		{
			__DSB();
			__WFI();
			auto irqnum = GIC_AcknowledgePending();
			GIC_EndInterrupt(irqnum);
			if (irqnum == 0) {
				Debug::Pin3::high();
			}
		}
		{
			__DSB();
			__WFI();
			auto irq_num = GIC_AcknowledgePending();
			GIC_EndInterrupt(irq_num);
			if (irq_num == 0) {
				Debug::Pin3::low();
			}
		}
	}
}
