#include "auxsignal.hh"
#include "conf/adc_i2c_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system_startup.hh"
#include "mp1m4/hsem_handler.hh"
#include "muxed_adc.hh"
#include "params.hh"
#include "shared_bus.hh"
#include "shared_bus_queue.hh"
#include "shared_memory.hh"

namespace MetaModule
{
static void app_startup()
{
	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
};

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	app_startup();

	SharedBus::i2c.init(i2c_conf_controls);

	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto screen_readbuf = SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenBufLocation);
	auto auxsignal_buffer = SharedMemory::read_address_of<DoubleAuxStreamBlock *>(SharedMemory::AuxSignalBlockLocation);

	// Controls
	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	Controls controls{potadc, *param_block_base, *auxsignal_buffer};

	// SharedBus
	SharedBusQueue i2cqueue{controls};
	SharedBus::i2c.enable_IT(i2c_conf_controls.priority1, i2c_conf_controls.priority2);

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);
	controls.start();

	while (true) {
		if (SharedBus::i2c.is_ready()) {
			Debug::red_LED2::high();
			i2cqueue.update();
			Debug::red_LED2::low();
		}
		__NOP();
		// __WFI();
	}
}

void recover_from_task_fault()
{
	while (true)
		;
}
