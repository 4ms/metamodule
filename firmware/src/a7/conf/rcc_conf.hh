#pragma once

#include "drivers/stm32xx.h"

const RCC_OscInitTypeDef rcc_osc_conf = {
	.OscillatorType = RCC_OSCILLATORTYPE_HSE,
	.HSEState = RCC_HSE_ON,
	// .HSIDivValue
	.PLL =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL12SOURCE_HSE,
			.PLLM = 3,
			.PLLN = 81,
			.PLLP = 1,
			.PLLQ = 1,
			.PLLR = 1,
			//.PLLRGE =
			.PLLFRACV = 2048,
			.PLLMODE = RCC_PLL_FRACTIONAL, // Todo: what is this?
										   // .MOD_PER, etc = , //This is only for spread-spectrum, right?
		},
	.PLL2 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL12SOURCE_HSE,
			.PLLM = 3,
			.PLLN = 66,
			.PLLP = 2,
			.PLLQ = 1,
			.PLLR = 1,
			//.PLLRGE =
			.PLLFRACV = 5120,
			.PLLMODE = RCC_PLL_FRACTIONAL, // Todo: what is this?
		},
	.PLL3 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL3SOURCE_HSE,
			.PLLM = 2,
			.PLLN = 34,
			.PLLP = 2,
			.PLLQ = 17,
			.PLLR = 37,
			.PLLRGE = RCC_PLL3IFRANGE_1,
			.PLLFRACV = 6660,
			.PLLMODE = RCC_PLL_FRACTIONAL, // Todo: what is this?
		},
	.PLL4 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 4,
			.PLLN = 99,
			.PLLP = 6,
			.PLLQ = 8,
			.PLLR = 8,
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 0,
			.PLLMODE = RCC_PLL_INTEGER, // Todo: what is this?
		},
};

const RCC_ClkInitTypeDef rcc_clk_conf = {
	// .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
	// 			 RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1,
	// .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
	// .SYSCLKDivider = RCC_SYSCLK_DIV1,
	// .AHBCLKDivider = RCC_HCLK_DIV2,
	// .APB3CLKDivider = RCC_APB3_DIV2,
	// .APB1CLKDivider = RCC_APB1_DIV2,
	// .APB2CLKDivider = RCC_APB2_DIV2,
	// .APB4CLKDivider = RCC_APB4_DIV2,
};

const RCC_PeriphCLKInitTypeDef rcc_periph_clk_conf = {
	.PeriphClockSelection = RCC_PERIPHCLK_I2C12 | RCC_PERIPHCLK_SPI23,
	.I2c12ClockSelection = RCC_I2C12CLKSOURCE_HSI,
	.Spi23ClockSelection = RCC_SPI23CLKSOURCE_PER,
};

// .PeriphClockSelection = RCC_PERIPHCLK_UART4 | RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_SPI2 |
// 						RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_SPI6 | RCC_PERIPHCLK_SAI1 | RCC_PERIPHCLK_QSPI |
// 						RCC_PERIPHCLK_FMC,
// .PLL2 =
// 	{
// 		.PLL2M = 1,
// 		.PLL2N = 14,
// 		.PLL2P = 25,
// 		.PLL2Q = 2,
// 		.PLL2R = 1, // FMC: 224MHz
// 		.PLL2RGE = RCC_PLL2VCIRANGE_3,
// 		.PLL2VCOSEL = RCC_PLL2VCOMEDIUM,
// 		.PLL2FRACN = 0,
// 	},
// .PLL3 =
// 	{
// 		.PLL3M = 1,
// 		.PLL3N = 49,
// 		.PLL3P = 64, // SAI1: 12.287994MHz
// 		.PLL3Q = 5,	 // SPI6: 157.2MHz
// 		.PLL3R = 17, // I2C123: 46.3MHz
// 		.PLL3RGE = RCC_PLL3VCIRANGE_3,
// 		.PLL3VCOSEL = RCC_PLL3VCOWIDE,
// 		.PLL3FRACN = 1245,
// 	},
// .FmcClockSelection = RCC_FMCCLKSOURCE_PLL2,
// .QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK,
// .Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL3,
// .Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL,
// .Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1,
// .Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2,
// .I2c123ClockSelection = RCC_I2C123CLKSOURCE_PLL3,
// .Spi6ClockSelection = RCC_SPI6CLKSOURCE_PLL3,
