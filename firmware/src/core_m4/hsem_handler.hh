#pragma once
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{
struct HWSemaphoreCoreHandler : public mdrivlib::HWSemaphoreGlobalBase {
	static void enable_global_ISR(uint32_t pri1, uint32_t pri2)
	{
		mdrivlib::InterruptManager::register_and_start_isr(HSEM_IT2_IRQn, pri1, pri2, [&]() {
			handle_isr<ParamsBuf1Lock>();
			handle_isr<ParamsBuf2Lock>();
			handle_isr<ScreenFrameBufLock>();
		});
	}
};

} // namespace MetaModule
