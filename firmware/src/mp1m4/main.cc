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
	Debug::Pin2::low();
	Debug::green_LED2::low();

	target::RCC_Enable::HSEM_::set();
	Debug::Pin2::high();
	HWSemaphore<M4_ready>::lock();

	Debug::Pin2::low();
	while (HWSemaphore<M7_ready>::is_locked())
		;

	Debug::green_LED2::high();
};

void main()
{
	app_startup();

	target::SystemClocks init_system_clocks{};

	// Simulate startup time
	for (int i = 0; i < 3000000; i++) {
	}

	HWSemaphore<M4_ready>::unlock();
	Debug::green_LED2::low();

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
