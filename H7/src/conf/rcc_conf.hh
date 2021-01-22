#pragma once

#include "drivers/stm32xx.h"

const RCC_OscInitTypeDef rcc_osc_conf = {
	.OscillatorType = RCC_OSCILLATORTYPE_HSE,
	.HSEState = RCC_HSE_ON,
	.PLL =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLLSOURCE_HSE,
			.PLLM = 8,
			.PLLN = 216,
			.PLLP = RCC_PLLP_DIV2,
			.PLLQ = 9,
		},
};

const RCC_ClkInitTypeDef rcc_clk_conf = {
	.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
	.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
	.AHBCLKDivider = RCC_SYSCLK_DIV1,
	.APB1CLKDivider = RCC_HCLK_DIV4,
	.APB2CLKDivider = RCC_HCLK_DIV2,
};

const RCC_PeriphCLKInitTypeDef rcc_periph_clk_conf = {
	.PeriphClockSelection = RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_USART6 | RCC_PERIPHCLK_SAI1 | RCC_PERIPHCLK_I2C1,
	.PLLSAI =
		{
			.PLLSAIN = 172, // mult by 172 = 172MHz
			.PLLSAIQ = 2,	// div by 2 = 86MHz
			.PLLSAIR = 2,	// div by 2 = 43MHz
			.PLLSAIP = RCC_PLLSAIP_DIV2,
		},
	.PLLSAIDivQ = 7, // div by 7 = 6.142856MHz
	.PLLSAIDivR = RCC_PLLSAIDIVR_2,
	// ???div by 128 for bit rate = 47.991kHz
	.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI,
	.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1,
	.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2,
	.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1,
};
