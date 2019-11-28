#pragma once
#include <stm32f7xx.h>
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "adc_builtin_driver.hh"
#include "touch.hh"
#include "filter.hh"
#include "pin.hh"

#include <array>

const int kOverSampleAmt = 4;

//Todo: put Button and CVJack in their own files
struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};


struct CVJack {
    CVJack(IAdcChanBase& adc_channel) : adc_channel_(adc_channel) {}
    // CVJack(IAdcChanBase& adc_channel) 
    // : adc_periph_num_(adc_channel.get_periph_num()),
    //   adc_channel_rank_(adc_channel.get_rank()) {}

    void read() {
        oversampler_.add_val(adc_channel_.get_val());
    }
    // void read() {
    //     oversampler_.add_val(AdcPeriph<adc_periph_num_>::get_channel_val(adc_channel_num_));
    // }

    uint16_t get() {return oversampler_.val();}

private:
    IAdcChanBase& adc_channel_;
    // const uint8_t adc_periph_num_;
    // uint8_t adc_channel_rank_;
    Oversampler<uint16_t, kOverSampleAmt> oversampler_;
};

struct JackSense {
    JackSense(Pin pin) : pin_(pin) {}
    bool is_plugged() {return plugged_;}

private:
    Pin pin_;
    bool plugged_ = false;
};

//Hardware class
//Represents peripherals and I/O that connects to control hardware (e.g. ADCs, GPIO pins, etc..)
struct Hardware {
    //Note: These are created on the stack, then Pin() ctor and add_channel are called, copying the values to/from stack.
    //      It's not clear, but there might be several copies happening (all are destroyed, but it makes initialization slower than necessary.
    //Todo: Compare to using rvalue references to move, and compare timing when optimized

    static inline AdcChan<AdcPeriphNum::ADC_1> freq1cv_adc {AdcChanNum::Chan10, {LL_GPIO_PIN_0, GPIOC, PinMode::ANALOG}};
    static inline AdcChan<AdcPeriphNum::ADC_1> res1cv_adc {AdcChanNum::Chan11, {LL_GPIO_PIN_1, GPIOC, PinMode::ANALOG}};
    static inline AdcChan<AdcPeriphNum::ADC_1> freq2cv_adc {AdcChanNum::Chan12, {LL_GPIO_PIN_2, GPIOC, PinMode::ANALOG}};
    static inline AdcChan<AdcPeriphNum::ADC_1> res2cv_adc {AdcChanNum::Chan13, {LL_GPIO_PIN_3, GPIOC, PinMode::ANALOG}};

    Pin freq2_sense_pin {LL_GPIO_PIN_14, GPIOC, PinMode::INPUT, PinPull::UP};
    Pin res2_sense_pin {LL_GPIO_PIN_4, GPIOC, PinMode::INPUT, PinPull::UP};
    Pin in1_sense_pin {LL_GPIO_PIN_13, GPIOC, PinMode::INPUT, PinPull::UP};
    Pin in2_sense_pin {LL_GPIO_PIN_15, GPIOC, PinMode::INPUT, PinPull::UP};

    //Add TIM pins here:
    //TimPwm<TIMx::TIM_8>
    //freq1_led {TimChanNum::Chan4, LL_GPIO_PIN_9, LL_GPIO_C, GPIO_AF3_TIM8};
};


//Controls class reads raw hardware, does fast conditioning (oversampling/debouncing)
//and stores values into objects representing each hardware object (e.g. CVJack, JackSense, Rotary, Button...)
struct Controls : private Hardware
{
    static inline CVJack freq1CV { freq1cv_adc };
    static inline CVJack res1CV { res1cv_adc };
    static inline CVJack freq2CV { freq2cv_adc };
    static inline CVJack res2CV { res2cv_adc };

    JackSense freq2_sense {freq2_sense_pin};
    JackSense res2_sense {res2_sense_pin};
    JackSense in1_sense {in1_sense_pin};
    JackSense in2_sense {in2_sense_pin};

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;

    Controls();
    static void read(); //Note: must be static so it can be called from IRQHandler
};
