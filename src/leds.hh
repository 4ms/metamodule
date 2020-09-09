#pragma once
#include "colors.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"
#include "tim_pwm.hh"

class NoPwmLed : public TimPwmChannel {
public:
	NoPwmLed() {}
	void set_output_level(uint32_t val) const {}
};

class DACLed : public TimPwmChannel {
public:
	DACLed(uint8_t dac_chan)
		: dac_chan_(dac_chan)
	{
	}
	void set_output_level(uint32_t val) const {}

private:
	uint8_t dac_chan_;
};

using PwmRgbLed = RgbLed<TimPwmChannel>;

struct LedDriverDefs {
	const static inline I2C_TypeDef *LEDDRIVER_I2C = I2C1;
	//use System::
	//const static inline LEDDRIVER_I2C_CLK_ENABLE __HAL_RCC_I2C1_CLK_ENABLE

	//use Pin
	//const static inline LEDDRIVER_I2C_GPIO_CLOCK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
	// const static inline uint8_t LEDDRIVER_I2C_GPIO_AF = GPIO_AF4_I2C1;
	// const static inline auto LEDDRIVER_I2C_GPIO = GPIOB;
	// const static inline auto LEDDRIVER_I2C_SCL_PIN = GPIO_PIN_8;
	// const static inline auto LEDDRIVER_I2C_SDA_PIN = GPIO_PIN_9;

	//use System::
	//		const static inline LEDDRIVER_I2C_DMA_CLK_ENABLE __HAL_RCC_DMA1_CLK_ENABLE;
	const static inline auto LEDDRIVER_I2C_DMA = DMA1;
	const static inline auto LEDDRIVER_I2C_DMA_INSTANCE_TX = DMA1_Stream6;
	const static inline auto I2C_DMA_CHANNEL_TX = DMA_CHANNEL_1;
	const static inline auto I2C_DMA_TX_IRQn = DMA1_Stream6_IRQn;

	//?? Use a callback
	//const static inline auto I2C_DMA_TX_IRQHandler = DMA1_Stream6_IRQHandler;
	// const static inline auto I2C_EV_IRQHandler = I2C1_EV_IRQHandler;
	// const static inline auto I2C_ER_IRQHandler = I2C1_ER_IRQHandler;
	const static inline auto I2C_EV_IRQn = I2C1_EV_IRQn;
	const static inline auto I2C_ER_IRQn = I2C1_ER_IRQn;

	const static inline uint32_t I2C1_SPEED = 800000;

	const static inline uint32_t PCA9685_MODE1 = 0x00;
	const static inline uint32_t PCA9685_MODE2 = 0x01;
	const static inline uint32_t PCA9685_LED0 = 0x06;
	const static inline uint32_t PRE_SCALE_MODE = 0xFE;
	const static inline uint32_t PCA9685_I2C_BASE_ADDRESS = 0b10000000;
};

class LedCtl {
public:
	LedCtl()
	{
	}

	//Todo: only update if glowing or fading
	void update()
	{
		freq[0].refresh();
		res[0].refresh();
		freq[1].refresh();
		res[1].refresh();
		mode[0].refresh();
		mode[1].refresh();
		mode[2].refresh();
		mode[3].refresh();
		mode[4].refresh();
	}

public:
	PwmRgbLed freq[2] = {
		{{TIM8, TimChannelNum::_4},
		 {TIM8, TimChannelNum::_3},
		 {TIM2, TimChannelNum::_2}},
		{NoLedElement,
		 {TIM3, TimChannelNum::_1},
		 {TIM8, TimChannelNum::_1N}}};

	PwmRgbLed res[2] = {
		{{TIM1, TimChannelNum::_4},
		 {TIM1, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_2}},

		{NoLedElement,
		 {TIM3, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_4}}};

	PwmRgbLed mode[5]{
		{NoLedElement, //DAC0 PA4
		 NoLedElement,
		 NoLedElement}, //DAC1 PA5

		{{TIM2, TimChannelNum::_3},
		 NoLedElement,
		 {TIM2, TimChannelNum::_4}},

		{{TIM2, TimChannelNum::_1},
		 NoLedElement,
		 {TIM5, TimChannelNum::_2}},

		{{TIM4, TimChannelNum::_3},
		 NoLedElement,
		 {TIM4, TimChannelNum::_4}},

		{{TIM4, TimChannelNum::_1},
		 NoLedElement,
		 {TIM4, TimChannelNum::_2}},
	};

private:
	NoPwmLed NoLedElement;
};

