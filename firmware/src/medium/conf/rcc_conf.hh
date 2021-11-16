#pragma once

#include "drivers/stm32xx.h"

const RCC_OscInitTypeDef rcc_osc_conf = {
	.OscillatorType = RCC_OSCILLATORTYPE_HSE,
	.HSEState = RCC_HSE_ON,
	// .HSIDivValue
	//FixME: PLL2 is ignored because it's in use (MPU clock), and the HAL_RCC_OscConfig() exits with an error.
	//Also, PLL3 is in use (MCU clock), so it would exit with an error there too. PLL4 never gets set.
	.PLL =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL12SOURCE_HSE,
			.PLLM = 3,
			.PLLN = 81,
			.PLLP = 1,
			.PLLQ = 1,
			.PLLR = 1,
			.PLLFRACV = 2048,
			.PLLMODE = RCC_PLL_FRACTIONAL,
		},
	// .PLL2 =
	// 	{
	// 		.PLLState = RCC_PLL_ON,
	// 		.PLLSource = RCC_PLL12SOURCE_HSE,
	// 		.PLLM = 3,
	// 		.PLLN = 66,
	// 		.PLLP = 2,
	// 		.PLLQ = 1,
	// 		.PLLR = 1,
	// 		.PLLFRACV = 5120,
	// 		.PLLMODE = RCC_PLL_FRACTIONAL,
	// 	},
	// .PLL3 =
	// 	{
	// 		.PLLState = RCC_PLL_ON,
	// 		.PLLSource = RCC_PLL3SOURCE_HSE,
	// 		.PLLM = 2,
	// 		.PLLN = 34,
	// 		.PLLP = 2,
	// 		.PLLQ = 17,
	// 		.PLLR = 37,
	// 		.PLLRGE = RCC_PLL3IFRANGE_1,
	// 		.PLLFRACV = 6685,
	// 		.PLLMODE = RCC_PLL_FRACTIONAL,
	// 	},
	// .PLL4 =
	// 	{
	// 		.PLLState = RCC_PLL_ON,
	// 		.PLLSource = RCC_PLL4SOURCE_HSE,
	// 		.PLLM = 4,
	// 		.PLLN = 99,
	// 		.PLLP = 6,
	// 		.PLLQ = 115,
	// 		.PLLR = 9,
	// 		.PLLRGE = RCC_PLL4IFRANGE_1,
	// 		.PLLFRACV = 0,
	// 		.PLLMODE = RCC_PLL_INTEGER,
	// 	},
};

const RCC_ClkInitTypeDef rcc_clk_conf = {
	.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ | RCC_CLOCKTYPE_PCLK1 |
				 RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 | RCC_CLOCKTYPE_PCLK5,
	.MPUInit =
		{
			.MPU_Clock = RCC_MPUSOURCE_PLL1,
			.MPU_Div = RCC_MPU_DIV2,
		},
	.AXISSInit =
		{
			.AXI_Clock = RCC_AXISSOURCE_PLL2,
			.AXI_Div = RCC_MPU_DIV_OFF,
		},
	.MCUInit =
		{
			.MCU_Clock = RCC_MCUSSOURCE_PLL3,
			.MCU_Div = RCC_MCU_DIV1,
		},
	.APB4_Div = RCC_APB4_DIV2,
	.APB5_Div = RCC_APB5_DIV4,
	.APB1_Div = RCC_APB1_DIV2,
	.APB2_Div = RCC_APB2_DIV2,
	.APB3_Div = RCC_APB3_DIV2,
};

const RCC_PeriphCLKInitTypeDef rcc_periph_clk_conf = {
	.PeriphClockSelection = RCC_PERIPHCLK_I2C12 | RCC_PERIPHCLK_SAI3 | RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_SPI23 |
							RCC_PERIPHCLK_SPI45 | RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_SDMMC12 | RCC_PERIPHCLK_LTDC,
	.PLL4 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 4,
			.PLLN = 99,
			.PLLP = 6,
			.PLLQ = 115,
			.PLLR = 9,
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 0,
			.PLLMODE = RCC_PLL_INTEGER,
		},
	.I2c12ClockSelection = RCC_I2C12CLKSOURCE_HSI,
	.Sai3ClockSelection = RCC_SAI3CLKSOURCE_PLL3_Q,
	.Spi1ClockSelection = RCC_SPI1CLKSOURCE_PLL4,
	.Spi23ClockSelection = RCC_SPI23CLKSOURCE_PLL4,
	.Spi45ClockSelection = RCC_SPI45CLKSOURCE_PCLK2,
	.Sdmmc12ClockSelection =
		RCC_SDMMC12CLKSOURCE_HSI, // See MP15x Errata: 2.3.5 Incorrect reset of glitch-free kernel clock switch
	.AdcClockSelection = RCC_ADCCLKSOURCE_PLL4, // PLL4R: 66MHz vs PER vs PLL3

};
