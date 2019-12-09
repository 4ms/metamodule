#pragma once
#include <stm32f7xx.h>
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "adc_builtin_driver.hh"
#include "touch.hh"
#include "filter.hh"
#include "pin.hh"

#include <array>

const int kOverSampleAmt = 8;

//Todo: put Button and CVJack in their own files
struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};

template <AdcPeripheral p(), AdcChanNum c> 
struct CVJack : AdcChan<p, c, uint32_t> {

    // void read_TESTME() { oversampler_.add_val(AdcPeriph<p>::get_val(c)); }
    void read() { oversampler_.add_val(this->get_val()); }

    uint16_t get() { return oversampler_.val(); }
private:
    Oversampler<uint16_t, kOverSampleAmt> oversampler_;
};

template <GPIO port, uint8_t pin> 
using JackSense = PinL<port, pin, PinPolarity::INVERTED>;

//Todo: create a Read-only class that returns its value when read, 
//and disallows assignment: operator=()=delete;
//and is initialized to an rvalue (move assignment?)


//SpecialPinAssignments class
//Initializes pins used in peripherals
struct SpecialPinAssignments {

    PinL<GPIO::C, 0> freq1cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 1> res1cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 2> freq2cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 3> res2cv_pin {PinMode::ANALOG};


    //Add TIM pins here:
    //TimPwm<TIMx::TIM_8>
    //freq1_led {TimChanNum::Chan4, LL_GPIO_PIN_9, LL_GPIO_C, GPIO_AF3_TIM8};
};

//Controls class 
//Reads raw user input hardware,
//Performs fast conditioning (oversampling/debouncing),
//and stores conditioned values
struct Controls : private SpecialPinAssignments
{
    static inline CVJack <ADC_1, AdcChanNum::_10> freq1_cv;
    static inline CVJack <ADC_1, AdcChanNum::_11> res1_cv;
    static inline CVJack <ADC_1, AdcChanNum::_12> freq2_cv;
    static inline CVJack <ADC_1, AdcChanNum::_13> res2_cv;

    static inline JackSense<GPIO::C, 14> freq2_sense {PinMode::INPUT, PinPull::UP};
    static inline JackSense<GPIO::C, 4>  res2_sense {PinMode::INPUT, PinPull::UP};
    static inline JackSense<GPIO::C, 13> in1_sense {PinMode::INPUT, PinPull::UP};
    static inline JackSense<GPIO::C, 15> in2_sense {PinMode::INPUT, PinPull::UP};

    static inline TouchCtl pads;
    static inline int32_t rotary_turn[2];  //-1, 0, 1
    static inline Button rotary_button[2]; //0, 1

    Controls();
    static void read(); //Note: must be static so it can be called from IRQHandler
    
    void begin() {
        pads.begin();
    }
};
