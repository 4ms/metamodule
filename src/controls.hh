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


//Todo: create a Read-only class that returns its value when read, 
//and disallows assignment
//and is initialized to an rvalue (move assignment?)

template <AdcPeriphNum p, AdcChanNum c> 
struct CVJack : AdcChan<p,c, uint32_t> {

    void read_TESTME() { oversampler_.add_val(AdcPeriph<p>::get_val(c)); }
    void read() { oversampler_.add_val(this->get_val()); }

    uint16_t get() { return oversampler_.val(); }
private:
    Oversampler<uint16_t, kOverSampleAmt> oversampler_;
};

template <ADC_TypeDef* p(), AdcChanNum c> 
struct CVJackP : AdcChanP<p,c, uint32_t> {

};

// using JackSense<port, pin> = PinL<port, pin, PinPolarity::INVERTED>;

// template<GPIO port, uint8_t pin> 
// struct JackSense : PinL {
//     JackSense(PinL sensepin) : pin_(sensepin) {}
//     bool is_plugged() {return pin_.is_on();}

// private:
//     PinL<port, pin, PinPolarity::INVERTED> pin_;
// };

//Hardware class
//Represents peripherals and I/O that connects to control hardware (e.g. ADCs, GPIO pins, etc..)
struct Hardware {

    PinL<GPIO::C, 0> freq1cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 1> res1cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 2> freq2cv_pin {PinMode::ANALOG};
    PinL<GPIO::C, 3> res2cv_pin {PinMode::ANALOG};

    PinL<GPIO::C, 14> freq2_sense_pin {PinMode::INPUT, PinPull::UP};
    PinL<GPIO::C, 4>  res2_sense_pin {PinMode::INPUT, PinPull::UP};
    PinL<GPIO::C, 13> in1_sense_pin {PinMode::INPUT, PinPull::UP};
    PinL<GPIO::C, 15> in2_sense_pin {PinMode::INPUT, PinPull::UP};

    //Add TIM pins here:
    //TimPwm<TIMx::TIM_8>
    //freq1_led {TimChanNum::Chan4, LL_GPIO_PIN_9, LL_GPIO_C, GPIO_AF3_TIM8};
};


//Controls class reads raw hardware, does fast conditioning (oversampling/debouncing)
//and stores values into objects representing each hardware object (e.g. CVJack, JackSense, Rotary, Button...)
struct Controls : private Hardware
{
    static inline CVJack <AdcPeriphNum::ADC_1, AdcChanNum::_10> freq1CV;
    static inline CVJack <AdcPeriphNum::ADC_1, AdcChanNum::_11> res1CV;
    static inline CVJack <AdcPeriphNum::ADC_1, AdcChanNum::_12> freq2CV;
    static inline CVJack <AdcPeriphNum::ADC_1, AdcChanNum::_13> res2CV;

    static inline CVJackP <ADC_1P, AdcChanNum::_9> testCV;

    // static inline JackSense freq2_sense {freq2_sense_pin};
    // static inline JackSense res2_sense {res2_sense_pin};
    // static inline JackSense in1_sense {in1_sense_pin};
    // static inline JackSense in2_sense {in2_sense_pin};

    static inline TouchCtl pads;
    static inline int32_t rotary_turn[2];  //-1, 0, 1
    static inline Button rotary_button[2]; //0, 1

    Controls();
    static void read(); //Note: must be static so it can be called from IRQHandler
    
    void begin() {
        pads.begin();
    }
};
