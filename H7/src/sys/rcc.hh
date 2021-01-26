#pragma once
#include "conf/rcc_conf.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

//#define DEBUG_MODE_DISABLE_I_CACHE
//#define DEBUG_MODE_DISABLE_D_CACHE

struct SystemClocks {
	SystemClocks()
	{
		System::SetVectorTable(0x08000000);

		System::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

		SCB_InvalidateDCache();

		// Debug Mode (all caches disabled):
#ifdef DEBUG_MODE_DISABLE_I_CACHE
		SCB_DisableICache();
#else
		// Code execution from flash over AXIM bus (0x08000000) using I-Cache:
		SCB_EnableICache();
#endif

#ifdef DEBUG_MODE_DISABLE_D_CACHE
		SCB_DisableDCache();
#else
		SCB_EnableDCache();
#endif

		HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
		HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
		HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
		HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
		HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	}
};

