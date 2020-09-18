#pragma once
#include "system.hh"
#include <functional>

class Timekeeper {
public:
	Timekeeper(TIM_TypeDef *TIMx, uint32_t period_us, std::function<void(void)> func, uint32_t priority1 = 1, uint32_t priority2 = 1);

	Timekeeper();
	void init(TIM_TypeDef *TIMx, uint32_t period_us, std::function<void(void)> func, uint32_t priority1 = 1, uint32_t priority2 = 1);

	void set_timing(uint32_t period_us, uint32_t priority1 = 1, uint32_t priority2 = 1);
	void register_task(std::function<void(void)> func);

	void start();
	void stop();

private:
	TIM_TypeDef *timx;
	IRQn_Type irqn;
	std::function<void(void)> task_func;

	bool tim_update_IT_is_set()
	{
		return (timx->SR & TIM_IT_UPDATE) == TIM_IT_UPDATE;
	}
	bool tim_update_IT_is_source()
	{
		return (timx->DIER & TIM_IT_UPDATE) == TIM_IT_UPDATE;
	}
	void tim_update_IT_clear()
	{
		timx->SR &= ~(TIM_IT_UPDATE);
	}
};

