#include "timekeeper.hh"
#include "interrupt.hh"
#include "stm32xx.h"

Timekeeper::Timekeeper()
	: is_running(false)
{}

void Timekeeper::init(const TimekeeperConfig &config, std::function<void(void)> func)
{
	set_periph(config.TIMx);
	task_func = func;
	register_task(func);
	System::enable_tim_rcc(timx);
	set_timing(config.period_ns, config.priority1, config.priority2);
}

Timekeeper::Timekeeper(const TimekeeperConfig &config, std::function<void(void)> func)
	: timx(config.TIMx)
	, irqn(System::tim_periph_to_IRQn(timx))
	, task_func(func)
	, is_running(false)
{
	register_task(func);
	System::enable_tim_rcc(timx);
	set_timing(config.period_ns, config.priority1, config.priority2);
}

void Timekeeper::start()
{
	is_running = true;
}

void Timekeeper::stop()
{
	is_running = false;
}

void Timekeeper::set_periph(TIM_TypeDef *TIMx)
{
	timx = TIMx;
	irqn = System::tim_periph_to_IRQn(timx);
}

void Timekeeper::set_timing(uint32_t period_ns, uint32_t priority1, uint32_t priority2)
{
	uint32_t sysfreq_Hz = System::tim_periph_max_freq(timx);
	float sysfreq_ns = 1000000000.f / sysfreq_Hz;
	uint32_t period_clocks = period_ns / sysfreq_ns;

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

	HAL_NVIC_SetPriority(irqn, priority1, priority2);
	HAL_NVIC_EnableIRQ(irqn);

	TIM_HandleTypeDef tim;
	tim.Instance = timx;
	tim.Init.Period = period_clocks;
	tim.Init.Prescaler = prescaler;
	tim.Init.ClockDivision = clock_division;
	tim.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim.Init.RepetitionCounter = 0;
	tim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

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
					if (is_running && task_func) //Todo: what is the cost of std::function operator bool
						task_func();
				}
				tim_update_IT_clear();
			}
		});
}

bool Timekeeper::tim_update_IT_is_set() const
{
	return (timx->SR & TIM_IT_UPDATE) == TIM_IT_UPDATE;
}
bool Timekeeper::tim_update_IT_is_source() const
{
	return (timx->DIER & TIM_IT_UPDATE) == TIM_IT_UPDATE;
}
void Timekeeper::tim_update_IT_clear() const
{
	timx->SR &= ~(TIM_IT_UPDATE);
}

//Todo: allows us to double-up on the IRQs that have two TIM UP (TIM1/TIM10, and TIM8/TIM13 share an ISR)
//Maybe just need a special-case in register_task:
//if (IRQn == TIM1_UP_TIM10_IRQn) {
// ...inside lamba:
// if (tim_update_IT_is_set(TIM1)) {...
// else if (tim_update_IT_is_set(TIM10)) {...
