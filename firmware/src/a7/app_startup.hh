#pragma once
#include "a7/conf/rcc_conf.hh"
#include "drivers/arch.hh"
// #include "conf/hsem_conf.hh"
// #include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"


namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		target::RCC_Enable::HSEM_::set();
		// HWSemaphore<M7_ready>::disable_channel_ISR();
		// HWSemaphore<M7_ready>::lock();

		// target::corem7::SystemStartup::wait_for_cm4_sleep();

		init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf, 500);

		// target::corem7::SystemStartup::tell_cm4_to_wakeup();
	}

	static void init_clocks(const RCC_OscInitTypeDef &osc_def,
							const RCC_ClkInitTypeDef &clk_def,
							const RCC_PeriphCLKInitTypeDef &pclk_def,
							const uint32_t systick_freq_hz = 1000)
	{
		// HAL_RCC_DeInit();

		RCC->MPCKSELR = 0;
		while ((RCC->MPCKSELR & RCC_MPCKSELR_MPUSRCRDY_Msk) == 0)
			;

		RCC_OscInitTypeDef osc_def_ = osc_def;
		HAL_RCC_OscConfig(&osc_def_);

		RCC_ClkInitTypeDef clk_def_ = clk_def;
		HAL_RCC_ClockConfig(&clk_def_);

		RCC_PeriphCLKInitTypeDef pclk_def_ = pclk_def;
		HAL_RCCEx_PeriphCLKConfig(&pclk_def_);
	}
};
} // namespace MetaModule
