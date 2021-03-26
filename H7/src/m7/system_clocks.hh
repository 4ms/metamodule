#pragma once
#include "conf/hsem_conf.hh"
#include "conf/rcc_conf.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

// #define DEBUG_MODE_DISABLE_I_CACHE
// #define DEBUG_MODE_DISABLE_D_CACHE

namespace mdrivlib
{
namespace stm32h7x5
{
namespace corem7
{
struct SystemStartup {
	static void wait_for_cm4_sleep()
	{
		int32_t timeout = 0xFFFF;
		// while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
		while (target::RCC_Clocks::D2CKREADY::read()) {
			if (timeout-- == 0)
				break;
		}
		if (timeout <= 0)
			__BKPT(); // Handle error
	}

	static void init_caches()
	{
		SCB_InvalidateDCache();

#ifdef DEBUG_MODE_DISABLE_I_CACHE
		SCB_DisableICache();
#else
		SCB_EnableICache();
#endif

#ifdef DEBUG_MODE_DISABLE_D_CACHE
		SCB_DisableDCache();
#else
		SCB_EnableDCache();
#endif
	}
};
} // namespace corem7
} // namespace stm32h7x5
} // namespace mdrivlib

namespace MetaModule
{
struct SystemClocks {
	SystemClocks()
	{
		target::RCC_Control::HSEM_::set();
		HWSemaphore<SharedBusLock>::lock();

		target::corem7::SystemStartup::wait_for_cm4_sleep();

		System::SetVectorTable(0x08000000);
		System::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf, 500);
		NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

		target::corem7::SystemStartup::init_caches();

		HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
		HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
		HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
		HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

		HWSemaphore<15>::lock();
		HWSemaphore<15>::unlock();
	}
};
} // namespace MetaModule
