#pragma once
#include <stm32f7xx.h>
#include "stm32f7xx_ll_bus.h"

//Todo: refactor for LL intead of HAL
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

    static constexpr void enable_gpio_rcc(GPIO_TypeDef* port) {
    	if (port==nullptr) return;
        #ifdef GPIOA
        if (port==GPIOA && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
        #endif
        #ifdef GPIOB
        if (port==GPIOB && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
        #endif
        #ifdef GPIOC
        if (port==GPIOC && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
        #endif
        #ifdef GPIOD
        if (port==GPIOD && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
        #endif
        #ifdef GPIOE
        if (port==GPIOE && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
        #endif
        #ifdef GPIOF
        if (port==GPIOF && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
        #endif
        #ifdef GPIOG
        if (port==GPIOG && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
        #endif
        #ifdef GPIOH
        if (port==GPIOH && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
        #endif
        #ifdef GPIOI
        if (port==GPIOI && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
        #endif
        #ifdef GPIOJ
        if (port==GPIOJ && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
        #endif
        #ifdef GPIOK
        if (port==GPIOK && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
        #endif
    }
	static void enable_tim_rcc(TIM_TypeDef *TIM) {
		#ifdef TIM1
		if (TIM==TIM1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
		#endif
		#ifdef TIM2
		if (TIM==TIM2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		#endif
		#ifdef TIM3
		if (TIM==TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		#endif
		#ifdef TIM4
		if (TIM==TIM4) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
		#endif
		#ifdef TIM5
		if (TIM==TIM5) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
		#endif
		#ifdef TIM6
		if (TIM==TIM6) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
		#endif
		#ifdef TIM7
		if (TIM==TIM7) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
		#endif
		#ifdef TIM8
		if (TIM==TIM8) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
		#endif
		#ifdef TIM9
		if (TIM==TIM9) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
		#endif
		#ifdef TIM10
		if (TIM==TIM10) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM10);
		#endif
		#ifdef TIM11
		if (TIM==TIM11) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM11);
		#endif
		#ifdef TIM12
		if (TIM==TIM12) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
		#endif
		#ifdef TIM13
		if (TIM==TIM13) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
		#endif
		#ifdef TIM14
		if (TIM==TIM14) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
		#endif
		#ifdef TIM15
		if (TIM==TIM15) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
		#endif
		#ifdef TIM16
		if (TIM==TIM16) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
		#endif
		#ifdef TIM17
		if (TIM==TIM17) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
		#endif
	}

	static inline constexpr uint8_t kTimPeriphMax = 17;

	static uint8_t tim_periph_to_num(TIM_TypeDef *TIM) {
		if (TIM==nullptr) return 0;
	    #ifdef TIM1
	    else if (TIM==TIM1) return 1;
	    #endif
	    #ifdef TIM2
	    else if (TIM==TIM2) return 2;
	    #endif
	    #ifdef TIM3
	    else if (TIM==TIM3) return 3;
	    #endif
	    #ifdef TIM4
	    else if (TIM==TIM4) return 4;
	    #endif
	    #ifdef TIM5
	    else if (TIM==TIM5) return 5;
	    #endif
	    #ifdef TIM6
	    else if (TIM==TIM6) return 6;
	    #endif
	    #ifdef TIM7
	    else if (TIM==TIM7) return 7;
	    #endif
	    #ifdef TIM8
	    else if (TIM==TIM8) return 8;
	    #endif
	    #ifdef TIM9
	    else if (TIM==TIM9) return 9;
	    #endif
	    #ifdef TIM10
	    else if (TIM==TIM10) return 10;
	    #endif
	    #ifdef TIM11
	    else if (TIM==TIM11) return 11;
	    #endif
	    #ifdef TIM12
	    else if (TIM==TIM12) return 12;
	    #endif
	    #ifdef TIM13
	    else if (TIM==TIM13) return 13;
	    #endif
	    #ifdef TIM14
	    else if (TIM==TIM14) return 14;
	    #endif
	    #ifdef TIM15
	    else if (TIM==TIM15) return 15;
	    #endif
	    #ifdef TIM16
	    else if (TIM==TIM16) return 16;
	    #endif
	    #ifdef TIM17
	    else if (TIM==TIM17) return 17;
	    #endif
	    else return 0;
	}
};
