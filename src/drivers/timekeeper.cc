#include "timekeeper.hh"
#include "interrupt.hh"
#include "stm32xx.h"

Timekeeper::Timekeeper()
{}

void Timekeeper::init(TIM_TypeDef *TIMx,
					  uint32_t period_us,
					  std::function<void(void)> func,
					  uint32_t priority1,
					  uint32_t priority2)
{
	timx = TIMx;
	irqn = System::tim_periph_to_IRQn(timx);
	task_func = func;
	register_task(func);
	System::enable_tim_rcc(timx);
	set_timing(period_us, priority1, priority2);
}

Timekeeper::Timekeeper(TIM_TypeDef *TIMx,
					   uint32_t period_us,
					   std::function<void(void)> func,
					   uint32_t priority1,
					   uint32_t priority2)
	: timx(TIMx)
	, irqn(System::tim_periph_to_IRQn(timx))
	, task_func(func)
{
	register_task(func);
	System::enable_tim_rcc(timx);
	set_timing(period_us, priority1, priority2);
}

void Timekeeper::start()
{
	HAL_NVIC_EnableIRQ(irqn);
}

void Timekeeper::stop()
{
	HAL_NVIC_DisableIRQ(irqn);
}

void Timekeeper::set_timing(uint32_t period_us, uint32_t priority1, uint32_t priority2)
{
	uint32_t sysfreq_Hz = System::tim_periph_max_freq(timx);
	float sysfreq_us = 1000000.f / sysfreq_Hz;
	uint32_t period_clocks = period_us / sysfreq_us;

	uint32_t prescaler = 0;
	while ((period_clocks / (prescaler + 1)) > 65535) {
		prescaler++;
	}
	period_clocks = period_clocks / (prescaler + 1);

	uint32_t clock_division = 0;
	while ((prescaler / (clock_division + 1) > 255)) {
		clock_division++;
	}
	prescaler = prescaler / (clock_division + 1);

	if (clock_division > 255) {
		period_clocks = 65535;
		prescaler = 255;
		clock_division = 255;
	}

	TIM_HandleTypeDef tim;
	tim.Instance = timx;
	tim.Init.Period = period_clocks;
	tim.Init.Prescaler = prescaler;
	tim.Init.ClockDivision = clock_division;
	tim.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim.Init.RepetitionCounter = 0;
	tim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_NVIC_SetPriority(irqn, priority1, priority2);
	HAL_TIM_Base_Init(&tim);

	HAL_TIM_Base_Start_IT(&tim);
}

void Timekeeper::register_task(std::function<void(void)> func)
{
	task_func = func;
	InterruptManager::registerISR(
		irqn,
		[this]() {
			if (tim_update_IT_is_set()) {
				if (tim_update_IT_is_source()) {
					if (task_func)
						task_func();
				}
				tim_update_IT_clear();
			}
		});
}

//Todo: allows us to double-up on the IRQs that have two TIM UP (TIM1/TIM10, and TIM8/TIM13 share an ISR)
//Maybe just need a special-case in register_task:
//if (IRQn == TIM1_UP_TIM10_IRQn) {
// ...inside lamba:
// if (tim_update_IT_is_set(TIM1)) {...
// else if (tim_update_IT_is_set(TIM10)) {...
