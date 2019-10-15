#pragma once
#include <stm32f7xx.h>

class System {

	void SetVectorTable(uint32_t reset_address)
	{ 
		SCB->VTOR = reset_address & (uint32_t)0x1FFFFF80;
	}

public:
	System() {
		SetVectorTable(0x08000000);
		HAL_Init();
		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_RCC_SYSCFG_CLK_ENABLE();

		RCC_OscInitTypeDef RCC_OscInitStruct = {0};
		RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
		RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		RCC_OscInitStruct.HSEState = RCC_HSE_ON;
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
		RCC_OscInitStruct.PLL.PLLM = 8;
		RCC_OscInitStruct.PLL.PLLN = 216;
		RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
		RCC_OscInitStruct.PLL.PLLQ = 2;
		HAL_RCC_OscConfig(&RCC_OscInitStruct);

		HAL_PWREx_EnableOverDrive();
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

		HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2S;
		PeriphClkInitStruct.PLLI2S.PLLI2SN = 96;
		PeriphClkInitStruct.PLLI2S.PLLI2SR = 4;	//2 for 96k
		PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
		PeriphClkInitStruct.PLLI2SDivQ = 1;

		PeriphClkInitStruct.I2sClockSelection = RCC_I2SCLKSOURCE_PLLI2S;
		PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

		HAL_RCC_EnableCSS();

		HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

		//Code execution from flash over ITCM bus (using ART and Prefetch)
		// SCB_DisableICache(); 
		// SCB_InvalidateDCache();
		// SCB_EnableDCache();	

		//Code execution from flash over AXIM bus using I-Cache:
		SCB_EnableICache();
		SCB_InvalidateDCache();
		SCB_EnableDCache();	

	    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

	}
};
