#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "m4/system_clocks.hh"
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
