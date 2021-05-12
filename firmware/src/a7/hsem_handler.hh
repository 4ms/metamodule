#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{
struct HWSemaphoreCoreHandler : public HWSemaphoreGlobalBase {
	static void enable_global_ISR(uint32_t pri1, uint32_t pri2)
	{
		InterruptManager::registerISR(HSEM_IT1_IRQn, pri1, pri2, [&]() { handle_isr<LEDFrameBufLock>(); });
	}
};
} // namespace MetaModule
