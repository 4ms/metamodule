#include "drivers/clocks.hh"
#include "drivers/stm32xx.h"
#include "drivers/tim_pwm.hh"
#include "globals.h"
#include "pwm_pins.hh"

void update_pwm(uint32_t pwmval, enum PwmOutputs pwmnum) {
	if (pwmnum >= NUM_PWMS)
		return;

	uint8_t channel;

	channel = pwm[pwmnum].timchan;

	if (channel == TIM_CHANNEL_1)
		pwm[pwmnum].tim.Instance->CCR1 = pwmval;

	else if (channel == TIM_CHANNEL_2)
		pwm[pwmnum].tim.Instance->CCR2 = pwmval;

	else if (channel == TIM_CHANNEL_3)
		pwm[pwmnum].tim.Instance->CCR3 = pwmval;

	else if (channel == TIM_CHANNEL_4)
		pwm[pwmnum].tim.Instance->CCR4 = pwmval;

#ifdef TIM_CHANNEL_5
	else if (channel == TIM_CHANNEL_5)
		pwm[pwmnum].tim.Instance->CCR5 = pwmval;
#endif
#ifdef TIM_CHANNEL_6
	else if (channel == TIM_CHANNEL_6)
		pwm[pwmnum].tim.Instance->CCR6 = pwmval;
#endif
}

static void init_pwm_out_pin(PWMOutput *p) {
	GPIO_InitTypeDef gpio;

	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Pull = GPIO_NOPULL;
	gpio.Pin = p->pinnum;
	gpio.Alternate = p->af;
	mdrivlib::RCC_Enable::GPIO::enable(p->gpio);
	HAL_GPIO_Init(p->gpio, &gpio);
}

void init_pwm_tim(PWMOutput *p) {
	mdrivlib::Clocks::TIM::enable(p->tim.Instance);
	TIM_OC_InitTypeDef tim_oc;

	p->tim.Init.Prescaler = 0;
	p->tim.Init.Period = p->period;
	p->tim.Init.ClockDivision = 0;
	p->tim.Init.CounterMode = TIM_COUNTERMODE_UP;
	p->tim.Init.RepetitionCounter = 0;
	p->tim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_PWM_Init(&p->tim);

	tim_oc.OCMode = TIM_OCMODE_PWM1;
	tim_oc.OCFastMode = TIM_OCFAST_DISABLE;
	tim_oc.OCPolarity = TIM_OCPOLARITY_LOW;
	tim_oc.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	tim_oc.OCIdleState = TIM_OCIDLESTATE_SET;
	tim_oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	tim_oc.Pulse = 0;

	HAL_TIM_PWM_ConfigChannel(&p->tim, &tim_oc, p->timchan);
}

void start_timers(PWMOutput *p) {
	HAL_TIM_PWM_Start(&p->tim, p->timchan);
}

void init_pwm(void) {
	for (auto &p : pwm) {
		init_pwm_out_pin(&p);
		init_pwm_tim(&p);
	}
	for (auto &p : pwm)
		start_timers(&p);
}
