#pragma once
#include "conf/hsem_conf.hh"
#include "conf/rcc_conf.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/secondary_core_control.hh"
#include "drivers/stm32xx.h"
#include "drivers/system_clocks.hh"
#include "uimg_loader.hh"

namespace MetaModule
{

struct AppStartup {
	AppStartup() {
		using namespace mdrivlib;

		RCC_Enable::HSEM_::set();

		HWSemaphore<MainCoreReady>::disable_channel_ISR();
		HWSemaphore<MainCoreReady>::lock();

		Copro::reset();
		SystemClocks::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		SecondaryCore::start();

		UimgLoader::load();

		L1C_CleanDCacheAll();
		__DSB();
		__ISB();
		Copro::start();
	}
};

} // namespace MetaModule
