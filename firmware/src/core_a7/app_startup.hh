#pragma once
#include "conf/hsem_conf.hh"
#include "conf/rcc_conf.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/secondary_core_control.hh"
#include "drivers/stm32xx.h"
#include "uimg_header.hh"
#include "drivers/system_clocks.hh"

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

		// DEBUG
		auto *a7_img = reinterpret_cast<BootImageDef::ImageHeader*>(0xC2000000);
		printf("A7 image magic: 0x%08x\n", a7_img->ih_magic);
		printf("A7 image size: 0x%08x\n", a7_img->ih_size);

		L1C_CleanDCacheAll();
		__DSB();
		__ISB();
		Copro::start();
	}
};

} // namespace MetaModule
