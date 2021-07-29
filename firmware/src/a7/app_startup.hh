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
#include "drivers/system_startup.hh"
#include "firmware_m4.h"
#include "firmware_m4_vectors.h"

namespace MetaModule
{
struct AppStartup {
	AppStartup()
	{
		using namespace mdrivlib;

		RCC_Enable::HSEM_::set();

		HWSemaphore<MainCoreReady>::disable_channel_ISR();
		HWSemaphore<MainCoreReady>::lock();

		SystemStartup::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		SecondaryCore::start();

		Copro::reset();
		Copro::load_vector_data(build_mp1corem4_vectors_bin, build_mp1corem4_vectors_bin_len);
		Copro::load_firmware_data(build_mp1corem4_firmware_bin, build_mp1corem4_firmware_bin_len);
		L1C_CleanDCacheAll();
		__DSB();
		__ISB();
		Copro::start();
	}
};
} // namespace MetaModule
