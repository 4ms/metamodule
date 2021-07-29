#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "drivers/system_startup.hh"
#include "m7/conf/rcc_conf.hh"

namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		using namespace mdrivlib;

		RCC_Enable::HSEM_::set();
		HWSemaphore<MainCoreReady>::disable_channel_ISR();
		HWSemaphore<MainCoreReady>::lock();

		target::corem7::SystemStartup::wait_for_cm4_sleep();

		target::System::SetVectorTable(0x08000000);
		target::System::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf, 500);
		NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

		target::corem7::SystemStartup::init_caches();

		HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
		HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
		HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
		HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

		target::corem7::SystemStartup::tell_cm4_to_wakeup();
	}
};
} // namespace MetaModule
