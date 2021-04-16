#pragma once
#include "a7/conf/rcc_conf.hh"
#include "drivers/arch.hh"
// #include "conf/hsem_conf.hh"
// #include "drivers/hsem.hh"
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
		// while (target::RCC_Clocks::D2CKREADY::read()) {
		// 	if (timeout-- == 0)
		// 		break;
		// }
		if (timeout <= 0)
			__BKPT(); // Handle error
	}

	static void tell_cm4_to_wakeup()
	{
		// Signal to Core M4 to power up (triggers an ISR on M4)
		// HWSemaphore<15>::lock();
		// HWSemaphore<15>::unlock();
	}

	static void init_caches() {}
};
} // namespace corem7
} // namespace stm32h7x5
} // namespace mdrivlib

namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		target::RCC_Enable::HSEM_::set();
		// HWSemaphore<M7_ready>::disable_channel_ISR();
		// HWSemaphore<M7_ready>::lock();

		// target::corem7::SystemStartup::wait_for_cm4_sleep();

		// System::SetVectorTable(0x08000000);
		init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf, 500);
		// NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

		// target::corem7::SystemStartup::init_caches();

		// HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
		// HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

		// target::corem7::SystemStartup::tell_cm4_to_wakeup();
	}

	static void init_clocks(const RCC_OscInitTypeDef &osc_def,
							const RCC_ClkInitTypeDef &clk_def,
							const RCC_PeriphCLKInitTypeDef &pclk_def,
							const uint32_t systick_freq_hz = 1000)
	{

		RCC_OscInitTypeDef osc_def_ = osc_def;
		HAL_RCC_OscConfig(&osc_def_);

		RCC_ClkInitTypeDef clk_def_ = clk_def;
		HAL_RCC_ClockConfig(&clk_def_);

		RCC_PeriphCLKInitTypeDef pclk_def_ = pclk_def;
		HAL_RCCEx_PeriphCLKConfig(&pclk_def_);

		// HAL_RCC_EnableCSS();

		// HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / systick_freq_hz);
		// HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	}
};
} // namespace MetaModule
