#pragma once
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{
struct HWSemaphoreCoreHandler : public HWSemaphoreGlobalBase {
	static void enable_global_ISR(uint32_t pri1, uint32_t pri2)
	{
		InterruptManager::registerISR(HSEM2_IRQn, pri1, pri2, [&]() {
			Debug::Pin2::high();
			handle_isr<ParamsBuf1Lock>();
			handle_isr<ParamsBuf2Lock>();
			handle_isr<ScreenFrameBuf1Lock>();
			// handle_isr<ScreenFrameBuf2Lock>();
			Debug::Pin2::low();
		});
	}
};
} // namespace MetaModule
