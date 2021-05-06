//#include "debug.hh"
#include "boot/system_startup_m4.hh"
#include "conf/hsem_conf.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

void main()
{
	FPin<GPIO::I, 8, PinMode::Output> red_LED2_init;
	FPin<GPIO::I, 9, PinMode::Output> green_LED2_init;

	using namespace MetaModule;

	target::RCC_Enable::HSEM_::set();
	HWSemaphore<M4_ready>::lock();

	while (1) {
		FPin<GPIO::I, 8, PinMode::Output>::low();
		for (int i = 0; i < 1000000; i++) { // 100000 = 75Hz
		}
		FPin<GPIO::I, 8, PinMode::Output>::high();

		FPin<GPIO::I, 9, PinMode::Output>::low();
		for (int i = 0; i < 1000000; i++) {
		}
		FPin<GPIO::I, 9, PinMode::Output>::high();

		for (int i = 0; i < 3000000; i++) {
		}
	}
}
