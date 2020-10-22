#pragma once
#include "conf/rcc_conf.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

//#define DEBUG_MODE_DISABLE_CACHE

struct SystemClocks {
	SystemClocks()
	{
		System::SetVectorTable(0x08000000);

		__HAL_FLASH_ART_ENABLE();
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();

		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

		System::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

		SCB_InvalidateDCache();

#ifdef DEBUG_MODE_DISABLE_CACHE
		// Debug Mode (all caches disabled):
		SCB_DisableICache();
		SCB_DisableDCache();
#else
		// Code execution from flash over AXIM bus (0x08000000) using I-Cache:
		SCB_EnableICache();
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

