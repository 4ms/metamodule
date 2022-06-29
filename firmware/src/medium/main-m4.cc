#include "auxsignal.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_codec_conf.hh"
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

static void signal_m4_ready_after_delay() {
	static uint32_t ctr = 0x10000;
	if (ctr == 1)
		HWSemaphore<MetaModule::M4_ready>::unlock();
	if (ctr > 0)
		ctr--;
}

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	app_startup();

	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto auxsignal_buffer = SharedMemory::read_address_of<DoubleAuxStreamBlock *>(SharedMemory::AuxSignalBlockLocation);

	SharedBus i2cbus{i2c_codec_conf};
	// I2CPeriph auxi2c{aux_i2c_conf}; //This is the Aux header for button/pot expander
	i2cbus.i2c.enable_IT(i2c_codec_conf.priority1, i2c_codec_conf.priority2);

	mdrivlib::GPIOExpander ext_gpio_expander{i2cbus.i2c, extaudio_gpio_expander_conf};
	mdrivlib::GPIOExpander main_gpio_expander{i2cbus.i2c, mainboard_gpio_expander_conf};

	Controls controls{*param_block_base, *auxsignal_buffer, main_gpio_expander, ext_gpio_expander};
	SharedBusQueue i2cqueue{main_gpio_expander, ext_gpio_expander};

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);
	controls.start();

	while (true) {
		signal_m4_ready_after_delay();

		if (SharedBus::i2c.is_ready()) {
			i2cqueue.update();
		}
		__NOP();
	}
}

void recover_from_task_fault() {
	while (true)
		;
}
