#pragma once
#include "a7/conf/rcc_conf.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/secondary_core_control.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "firmware_m4.h"
#include "firmware_m4_vectors.h"

namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		target::RCC_Enable::HSEM_::set();
		HWSemaphore<MainCoreReady>::disable_channel_ISR();
		HWSemaphore<MainCoreReady>::lock();

		init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		SecondaryCore::start();

		Copro::reset();
		Copro::load_vector_data(build_mp1corem4_vectors_bin, build_mp1corem4_vectors_bin_len);
		Copro::load_firmware_data(build_mp1corem4_firmware_bin, build_mp1corem4_firmware_bin_len);
		L1C_CleanDCacheAll();
		__DSB();
		__ISB();
		Copro::start();
	}

	static void init_clocks(const RCC_OscInitTypeDef &osc_def,
							const RCC_ClkInitTypeDef &clk_def,
							const RCC_PeriphCLKInitTypeDef &pclk_def,
							const uint32_t systick_freq_hz = 1000)
	{
		// Reset MPU clock selection, so we can change it
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
