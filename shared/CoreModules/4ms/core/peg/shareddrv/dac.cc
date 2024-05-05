#include "dac.h"
#include "drivers/timekeeper.hh"
#include "stm32xx.h"

#define ENVA_Pin GPIO_PIN_4
#define ENVB_Pin GPIO_PIN_5
#define ENV_GPIO_Port GPIOA

static DAC_HandleTypeDef hdac1;
static mdrivlib::Timekeeper dactmr;

void dac_out(enum DACs dac, uint16_t val) {
	if (dac == DAC_ENVA) {
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 4095 - val);
	} else if (dac == DAC_ENVB) {
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, val);
	}
}

void init_dac(uint32_t freq, void (*callbackfunc)(void)) {

	hdac1.Instance = DAC1;
	HAL_DAC_Init(&hdac1);

	__HAL_RCC_DAC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio = {0};
	gpio.Pin = ENVA_Pin | ENVB_Pin;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ENV_GPIO_Port, &gpio);

	DAC_ChannelConfTypeDef sConfig = {0};
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1);
	HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2);

	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);

	if (freq == 0)
		return;

	const mdrivlib::TimekeeperConfig conf{
		.TIMx = TIM6,
		.period_ns = 1'000'000'000 / freq,
		.priority1 = 0,
		.priority2 = 1,
	};

	dactmr.init(conf, callbackfunc);
	dactmr.start();
}

void pause_dac_timer(void) {
	dactmr.stop();
}

void resume_dac_timer(void) {
	dactmr.start();
}

// void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac) {
// 	GPIO_InitTypeDef gpio = {0};

// 	if (hdac->Instance == DAC1) {
// 		__HAL_RCC_DAC_CLK_ENABLE();
// 		__HAL_RCC_GPIOA_CLK_ENABLE();
// 		gpio.Pin = ENVA_Pin | ENVB_Pin;
// 		gpio.Mode = GPIO_MODE_ANALOG;
// 		gpio.Pull = GPIO_NOPULL;
// 		HAL_GPIO_Init(ENV_GPIO_Port, &gpio);
// 	}
// }
