#pragma once

#include "drivers/stm32xx.h"

const RCC_OscInitTypeDef rcc_osc_conf = {
	.PLL3 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 2,
			.PLLN = 34,
			.PLLP = 2,	//208.896MHZ for MCU
			.PLLQ = 17, //=>24.576MHz for SAI
			.PLLR = 2,	//208.89624MHz for ...?
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 6685,
			.PLLMODE = RCC_PLL_FRACTIONAL,
		},
	.PLL4 =
		{
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLL4SOURCE_HSE,
			.PLLM = 4,
			.PLLN = 69,
			.PLLP = 6,
			.PLLQ = 24,
			.PLLR = 13,
			.PLLRGE = RCC_PLL4IFRANGE_1,
			.PLLFRACV = 5178,
			.PLLMODE = RCC_PLL_FRACTIONAL,
		},
};

const RCC_ClkInitTypeDef rcc_clk_conf = {
	.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 |
				 RCC_CLOCKTYPE_PCLK4 | RCC_CLOCKTYPE_PCLK5,
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
	.PeriphClockSelection = RCC_PERIPHCLK_I2C12 | RCC_PERIPHCLK_I2C35 | RCC_PERIPHCLK_SAI2 | RCC_PERIPHCLK_UART24 |
							RCC_PERIPHCLK_CKPER | RCC_PERIPHCLK_RNG1 | RCC_PERIPHCLK_STGEN | RCC_PERIPHCLK_ADC,
	.I2c12ClockSelection = RCC_I2C12CLKSOURCE_PCLK1,
	.I2c35ClockSelection = RCC_I2C35CLKSOURCE_PCLK1,
	.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLL3_Q,
	.Uart24ClockSelection = RCC_UART24CLKSOURCE_HSI,
	.CkperClockSelection = RCC_CKPERCLKSOURCE_HSI, //default
	.Rng1ClockSelection = RCC_RNG1CLKSOURCE_PLL4,
	.StgenClockSelection = RCC_STGENCLKSOURCE_HSE,
	.AdcClockSelection = RCC_ADCCLKSOURCE_PER,

};
