#include "conf/control_conf.hh"
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "m4/system_clocks.hh"
#include "params.hh"
#include "shared_bus.hh"

using namespace MetaModule;
void main(void)
{
	target::corem4::SystemClocks start_clocks;

	Debug::Pin3::high();
	Debug::Pin2::high();
	while (HWSemaphore::is_locked<SharedBusLock>()) {
		Debug::Pin2::low();
	}
	Debug::Pin3::low();

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;

	extern char *_control_data_start; // defined by linker
	Params *params = reinterpret_cast<Params *>(&_control_data_start);

	Controls controls{potadc, cvadc, *params}; //, gpio_expander};

	controls.start();
	// SharedBusQueue<leds.LEDUpdateRateHz> i2cqueue{leds, controls};

	while (1) {
		// if (SharedBus::i2c.is_ready()) {
		Debug::Pin2::high();
		// i2cqueue.update();
		Debug::Pin2::low();
		// }
	}
}

void recover_from_task_fault()
{
	main();
}

