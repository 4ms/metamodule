#pragma once
#include "adc_builtin_driver.hh"
#include "debounced_switch.hh"
#include "filter.hh"
#include "pin.hh"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_gpio.h"
#include "touch.hh"
#include <array>
#include <stm32f7xx.h>

const int kOverSampleAmt = 8;

//Todo: put Button and CVJack in their own files

template<AdcPeripheral p(), AdcChanNum c>
struct CVJack : AdcChan<p, c, uint32_t> {
	// void read_TESTME() { oversampler_.add_val(AdcPeriph<p>::get_val(c)); }
	void read()
	{
		oversampler_.add_val(this->get_val());
	}

	uint16_t get()
	{
		return oversampler_.val();
	}

private:
	Oversampler<uint16_t, kOverSampleAmt> oversampler_;
};

template<GPIO port, uint8_t pin>
using JackSense = PinL<port, pin, PinPolarity::Inverted>;

//Todo: create a Read-only class that returns its value when read,
//and disallows assignment: operator=()=delete;
//and is initialized to an rvalue (move assignment?)

//SpecialPinAssignments class
//Initializes pins used in peripherals
struct SpecialPinAssignments {

	PinL<GPIO::C, 0> freq1cv_pin{PinMode::Analog};
	PinL<GPIO::C, 1> res1cv_pin{PinMode::Analog};
	PinL<GPIO::C, 2> freq2cv_pin{PinMode::Analog};
	PinL<GPIO::C, 3> res2cv_pin{PinMode::Analog};

	PinL<GPIO::C, 9> freq1_red_pin{PinMode::Alt, LL_GPIO_AF_3};
	PinL<GPIO::C, 8> freq1_green_pin{PinMode::Alt, LL_GPIO_AF_3};
	PinL<GPIO::B, 3> freq1_blue_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::A, 11> res1_red_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::A, 10> res1_green_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::B, 5> res1_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::A, 6> freq2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::A, 7> freq2_green_pin{PinMode::Alt, LL_GPIO_AF_3};
	PinL<GPIO::B, 0> res2_green_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::B, 1> res2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::A, 2> mode1_red_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::A, 3> mode1_blue_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::A, 0> mode2_red_pin{PinMode::Alt, LL_GPIO_AF_1};
	PinL<GPIO::A, 1> mode2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::B, 8> mode3_red_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::B, 9> mode3_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::B, 6> mode4_red_pin{PinMode::Alt, LL_GPIO_AF_2};
	PinL<GPIO::B, 7> mode4_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
};

//Controls class
//Reads raw user input hardware,
//Performs fast conditioning (oversampling/debouncing),
//and stores conditioned values
struct Controls : private SpecialPinAssignments {
	static inline CVJack<ADC_1, AdcChanNum::_10> freq1_cv;
	static inline CVJack<ADC_1, AdcChanNum::_11> res1_cv;
	static inline CVJack<ADC_1, AdcChanNum::_12> freq2_cv;
	static inline CVJack<ADC_1, AdcChanNum::_13> res2_cv;

	static inline JackSense<GPIO::C, 14> freq2_sense{PinMode::Input, PinPull::Up};
	static inline JackSense<GPIO::C, 4> res2_sense{PinMode::Input, PinPull::Up};
	static inline JackSense<GPIO::C, 13> in1_sense{PinMode::Input, PinPull::Up};
	static inline JackSense<GPIO::C, 15> in2_sense{PinMode::Input, PinPull::Up};

	static inline TouchCtl pads;
	static inline int32_t rotary_turn[2];
	static inline DebouncedSwitch rotary_button[2] = {
		{GPIO::D, 2},
		{GPIO::B, 14}};

	Controls();
	static void read();

	void begin();
};
