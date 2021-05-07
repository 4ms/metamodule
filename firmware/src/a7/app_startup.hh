#pragma once
#include "a7/conf/rcc_conf.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		Debug::Pin0::low();
		Debug::Pin1::low();

		target::RCC_Enable::HSEM_::set();
		HWSemaphore<M7_ready>::disable_channel_ISR();
		Debug::Pin0::high();
		HWSemaphore<M7_ready>::lock();

		Debug::Pin1::high();
		HWSemaphore<15>::lock();

		init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf, 500);

		// Allow MCU to boot
		RCC->MP_GCR = RCC->MP_GCR | RCC_MP_GCR_BOOT_MCU;

		// Do an unlock which triggers an Interrupt on the MCU, waking it up.
		HWSemaphore<15>::unlock();
		Debug::Pin1::low();
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
