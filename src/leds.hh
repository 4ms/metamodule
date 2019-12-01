#pragma once
#include <stm32f7xx.h>
#include "tim_pwm.hh"
#include "pin.hh"
#include "colors.hh"


class LedCtl {

public:
    LedCtl() {
        //Freq1: PC9, PC8, PB3
        // Pin<NORMAL> r(OUTPUT, GPIO_PIN_9, GPIOC);
        // Pin<NORMAL> g(OUTPUT, GPIO_PIN_8, GPIOC);
        // Pin<NORMAL> b(OUTPUT, GPIO_PIN_3, GPIOB);
        // r.high(); r.low();
        // g.high(); g.low();
        // b.high(); b.low();

        //Res1: PA11, PA10, PB5
        // Pin<NORMAL> r(OUTPUT, GPIO_PIN_11, GPIOA);
        // Pin<NORMAL> g(OUTPUT, GPIO_PIN_10, GPIOA);
        // Pin<NORMAL> b(OUTPUT, GPIO_PIN_5, GPIOB);

        // Pin<NORMAL> m5r(OUTPUT, GPIO_PIN_6, GPIOB);
        // Pin<NORMAL> m5b(OUTPUT, GPIO_PIN_7, GPIOB);
        // Pin<NORMAL> m4r(OUTPUT, GPIO_PIN_8, GPIOB);
        // Pin<NORMAL> m4b(OUTPUT, GPIO_PIN_9, GPIOB);
        // Pin<NORMAL> m3r(OUTPUT, GPIO_PIN_0, GPIOA);
        // Pin<NORMAL> m3b(OUTPUT, GPIO_PIN_1, GPIOA);
        // Pin<NORMAL> m2r(OUTPUT, GPIO_PIN_2, GPIOA);
        // Pin<NORMAL> m2b(OUTPUT, GPIO_PIN_3, GPIOA);
        // Pin<NORMAL> m1r(OUTPUT, GPIO_PIN_4, GPIOA);
        // Pin<NORMAL> m1b(OUTPUT, GPIO_PIN_5, GPIOA);

        // Pin<NORMAL> freq2g(OUTPUT, GPIO_PIN_6, GPIOA);
        // Pin<NORMAL> freq2b(OUTPUT, GPIO_PIN_7, GPIOA);
        // Pin<NORMAL> res2g(OUTPUT, GPIO_PIN_0, GPIOB);
        // Pin<NORMAL> res2b(OUTPUT, GPIO_PIN_1, GPIOB);
    }

    //Todo: only update if glowing or fading
    void update() {
        freq1.refresh();
        res1.refresh();
        // freq2.refresh();
        // res2.refresh();
        // mode[0].refresh();
        // mode[1].refresh();
        // mode[2].refresh();
        // mode[3].refresh();
        // mode[4].refresh();
    }

private:
    //Todo: automatically construct these when a TimPwmLed is constructed with TIMx
    TimPwm tim1 {TIM1};
    TimPwm tim2 {TIM2};
    TimPwm tim3 {TIM3};
    TimPwm tim4 {TIM4};
    TimPwm tim5 {TIM5};
    TimPwm tim8 {TIM8};

public:
    _debugconst_ RgbLed freq1 {
        {tim8, TIM_CHANNEL_4, GPIO_PIN_9, GPIOC, GPIO_AF3_TIM8},
        {tim8, TIM_CHANNEL_3, GPIO_PIN_8, GPIOC, GPIO_AF3_TIM8},
        {tim2, TIM_CHANNEL_2, GPIO_PIN_3, GPIOB, GPIO_AF1_TIM2}};

    _debugconst_ RgbLed res1 {
        {tim1, TIM_CHANNEL_4, GPIO_PIN_11, GPIOA, GPIO_AF1_TIM1},
        {tim1, TIM_CHANNEL_3, GPIO_PIN_10, GPIOA, GPIO_AF1_TIM1},
        {tim3, TIM_CHANNEL_2, GPIO_PIN_5, GPIOB, GPIO_AF2_TIM3}};

    _debugconst_ RgbLed freq2 {
        NoLedElement,
        {tim3, TIM_CHANNEL_1, GPIO_PIN_6, GPIOA, GPIO_AF2_TIM3},
        {tim8, TIM_CHANNEL_1, GPIO_PIN_7, GPIOA, GPIO_AF3_TIM8, TimPwmOutType::N}};

    _debugconst_ RgbLed res2 {
        NoLedElement,
        {tim3, TIM_CHANNEL_3, GPIO_PIN_0, GPIOB, GPIO_AF2_TIM3},
        {tim3, TIM_CHANNEL_4, GPIO_PIN_1, GPIOB, GPIO_AF2_TIM3}};

    _debugconst_ RgbLed mode[5] {
        {{tim4, TIM_CHANNEL_1, GPIO_PIN_6, GPIOB, GPIO_AF2_TIM4},
         NoLedElement,
         {tim4, TIM_CHANNEL_2, GPIO_PIN_7, GPIOB, GPIO_AF2_TIM4}},

        {{tim4, TIM_CHANNEL_3, GPIO_PIN_8, GPIOB, GPIO_AF2_TIM4},
         NoLedElement,
         {tim4, TIM_CHANNEL_4, GPIO_PIN_9, GPIOB, GPIO_AF2_TIM4}},

        {{tim2, TIM_CHANNEL_1, GPIO_PIN_0, GPIOA, GPIO_AF1_TIM2},
         NoLedElement,
         {tim5, TIM_CHANNEL_2, GPIO_PIN_1, GPIOA, GPIO_AF2_TIM5}},

        {{tim2, TIM_CHANNEL_3, GPIO_PIN_2, GPIOA, GPIO_AF1_TIM2},
         NoLedElement,
         {tim2, TIM_CHANNEL_4, GPIO_PIN_3, GPIOA, GPIO_AF1_TIM2}},

        {NoLedElement,  //DAC0 PA4
         NoLedElement,
         NoLedElement}, //DAC1 PA5
    };

private:
    NoLed NoLedElement;
};

