#include "tim.hh"
#include "system.hh"

void TIMPeriph::init_periph(TIM_TypeDef *TIM,
							uint32_t period,
							uint16_t prescaler,
							uint32_t clock_division)
{
	System::enable_tim_rcc(TIM);
	LL_TIM_InitTypeDef timinit = {.Prescaler = prescaler,
								  .CounterMode = LL_TIM_COUNTERMODE_UP,
								  .Autoreload = period,
								  .ClockDivision = clock_division,
								  .RepetitionCounter = 0};
	LL_TIM_Init(TIM, &timinit);
	LL_TIM_DisableARRPreload(TIM);
}

void TIMPeriph::init_periph_once(TIM_TypeDef *TIM,
								 uint32_t period,
								 uint16_t prescaler,
								 uint32_t clock_division)
{
	static bool did_init[System::kTimPeriphMax] = {false};

	uint8_t tim_i = System::tim_periph_to_num(TIM);

	if (tim_i == 0 || did_init[tim_i - 1])
		return; // Todo: use assert() if ok with the exception implications of using assert

	init_periph(TIM, period, prescaler, clock_division);

	did_init[tim_i - 1] = true;
}

