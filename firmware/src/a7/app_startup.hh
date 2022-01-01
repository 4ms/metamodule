#pragma once
#include "conf/hsem_conf.hh"
#include "conf/rcc_conf.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/secondary_core_control.hh"
#include "drivers/stm32xx.h"
#include "drivers/system_startup.hh"

#include "drivers/copro_control.hh"
#include "firmware_m4.h"
#include "firmware_m4_vectors.h"

namespace MetaModule
{
enum class CoProMode { Enabled, Disabled };
enum class Core2Mode { Enabled, Disabled };

struct AppStartup {
	AppStartup(CoProMode copro_mode = CoProMode::Enabled, Core2Mode core2_mode = Core2Mode::Enabled) {
		using namespace mdrivlib;

		RCC_Enable::HSEM_::set();

		HWSemaphore<MainCoreReady>::disable_channel_ISR();
		HWSemaphore<MainCoreReady>::lock();

		SystemStartup::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		if (core2_mode == Core2Mode::Enabled)
			SecondaryCore::start();

		if (copro_mode == CoProMode::Enabled) {
			Copro::reset();
			Copro::load_vector_data(vectors_bin, vectors_bin_len);
			Copro::load_firmware_data(firmware_bin, firmware_bin_len);
		}

		L1C_CleanDCacheAll();
		__DSB();
		__ISB();

		if (copro_mode == CoProMode::Enabled) {
			Copro::start();
		}
	}
};

} // namespace MetaModule
