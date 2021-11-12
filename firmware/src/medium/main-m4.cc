#include "auxsignal.hh"
#include "conf/hsem_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system_startup.hh"
#include "mp1m4/hsem_handler.hh"
#include "params.hh"
#include "shared_bus.hh"
#include "shared_bus_queue.hh"
#include "shared_memory.hh"

namespace MetaModule
{
static void app_startup() {
	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
};

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	app_startup();

	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto screen_readbuf = SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenBufLocation);
	auto auxsignal_buffer = SharedMemory::read_address_of<DoubleAuxStreamBlock *>(SharedMemory::AuxSignalBlockLocation);

	Controls controls{*param_block_base, *auxsignal_buffer};

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);
	controls.start();

	uint32_t ctr = 0x10000;
	while (true) {
		if (ctr == 1)
			HWSemaphore<M4_ready>::unlock();
		if (ctr > 0)
			ctr--;

		__NOP();
		// __WFI();
	}
}

void recover_from_task_fault() {
	while (true)
		;
}
