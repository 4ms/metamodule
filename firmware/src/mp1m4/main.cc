//#include "debug.hh"
#include "boot/system_startup_m4.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system.hh"

using namespace MetaModule;

static void app_startup()
{
	target::RCC_Enable::HSEM_::set();
	HWSemaphore<M4_ready>::lock();

	HWSemaphore<15>::enable_channel_ISR();
	target::System::enable_irq(HSEM_IT2_IRQn);
	InterruptManager::registerISR(HSEM_IT2_IRQn, 0, 0, []() {
		HWSemaphore<15>::clear_ISR();
		target::System::disable_irq(HSEM_IT2_IRQn);
	});

	// go to sleep, wait for wakeup
	__WFI();

	while (HWSemaphore<M7_ready>::is_locked())
		;
};

void main()
{
	app_startup();

	target::SystemClocks init_system_clocks{};

	for (int i = 0; i < 3000000; i++) {
	}

	// Main loop continuously locks/unlocks M4_ready, so CA7 can pick up at any time
	while (1) {
		HWSemaphore<M4_ready>::lock();
		Debug::red_LED2::low();
		for (int i = 0; i < 1000000; i++) { // 100000 = 75Hz
		}
		Debug::red_LED2::high();

		HWSemaphore<M4_ready>::unlock();
		Debug::green_LED2::low();
		for (int i = 0; i < 1000000; i++) {
		}
		Debug::green_LED2::high();

		for (int i = 0; i < 3000000; i++) {
		}
	}
}
