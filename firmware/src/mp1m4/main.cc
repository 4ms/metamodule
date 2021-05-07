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
	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<M7_ready>::is_locked())
		;

	target::SystemClocks init_system_clocks{};
};

void main()
{
	app_startup();

	// Simulate startup time
	for (int i = 0; i < 3000000; i++) {
	}

	// Tell A7 we're ready
	HWSemaphore<M4_ready>::unlock();

	while (1) {
		Debug::red_LED2::low();
		HAL_Delay(10);
		Debug::red_LED2::high();
		HAL_Delay(50);
	}
}

void recover_from_task_fault()
{
	while (1)
		;
}
