#pragma once

#include "drivers/stm32xx.h"

//FIXME: This isn't used, remove it once we're sure
const RCC_OscInitTypeDef rcc_osc_conf = {
	.OscillatorType = RCC_OSCILLATORTYPE_HSE,
	.HSEState = RCC_HSE_ON,
	.PLL =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL12SOURCE_HSE,
			.PLLM = 3,
			.PLLN = 100,
			.PLLP = 1,
			.PLLQ = 2,
			.PLLR = 2,
			.PLLFRACV = 0,
			.PLLMODE = RCC_PLL_INTEGER,
		},
	.PLL2 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL12SOURCE_HSE,
			.PLLM = 3,
			.PLLN = 66,
			.PLLP = 2,
			.PLLQ = 2,
			.PLLR = 1,
			.PLLFRACV = 4096,
			.PLLMODE = RCC_PLL_FRACTIONAL,
		},
};

const RCC_ClkInitTypeDef rcc_clk_conf = {
	.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ | RCC_CLOCKTYPE_PCLK1 |
				 RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 | RCC_CLOCKTYPE_PCLK5,
	.MPUInit =
		{
			.MPU_Clock = RCC_MPUSOURCE_PLL1,
			.MPU_Div = RCC_MPU_DIV_OFF,
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
	//104: 63.883Hz
	//105: 63.275Hz
	//112: 59.32Hz
	//TODO: setup PLL3?
	.PLL3 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 2,
			.PLLN = 52,
			.PLLP = 3,
			.PLLQ = 6,
			.PLLR = 2,
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 0,
			.PLLMODE = RCC_PLL_INTEGER,
		},
	.PLL4 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 4,
			.PLLN = 99,
			.PLLP = 6,
			.PLLQ = 112,
			.PLLR = 9,
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 0,
			.PLLMODE = RCC_PLL_INTEGER,
		},
	.I2c12ClockSelection = RCC_I2C12CLKSOURCE_HSI,
	.I2c35ClockSelection = RCC_I2C35CLKSOURCE_HSI,
	.I2c46ClockSelection = RCC_I2C46CLKSOURCE_HSI,
	.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL3_Q,
	.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLL3_Q,
	.Spi45ClockSelection = RCC_SPI45CLKSOURCE_PCLK2,
	.Sdmmc12ClockSelection =
		RCC_SDMMC12CLKSOURCE_HSI, // See MP15x Errata: 2.3.5 Incorrect reset of glitch-free kernel clock switch
	.AdcClockSelection = RCC_ADCCLKSOURCE_PLL4, // PLL4R: 66MHz vs PER vs PLL3

};
