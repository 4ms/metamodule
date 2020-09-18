#pragma once
#include "stm32f7xx_ll_tim.h"

class TIMPeriph {
public:
	static void
	init_periph(TIM_TypeDef *TIM, uint32_t period, uint16_t prescaler, uint32_t clock_division);
	static void init_periph_once(TIM_TypeDef *TIM,
								 uint32_t period = 256,
								 uint16_t prescaler = 0,
								 uint32_t clock_division = 0);
};
