#pragma once
#include <stm32f7xx.h>
#include "tim_pwm.hh"
#include "pin.hh"
#include "colors.hh"


struct LedCtl {
private:
    enum TimPwmPeriphs {tim1 = 0, tim2 = 1, tim3 = 2, tim4 = 3, tim8 = 4};
    TimPwm htim[5] {TIM1, TIM2, TIM3, TIM4, TIM8};

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

public:
    _debugconst_ RgbLed freq1 {
        {htim[tim8], TIM_CHANNEL_4, GPIO_PIN_9, GPIOC, GPIO_AF3_TIM8},
        {htim[tim8], TIM_CHANNEL_3, GPIO_PIN_8, GPIOC, GPIO_AF3_TIM8},
        {htim[tim2], TIM_CHANNEL_2, GPIO_PIN_3, GPIOB, GPIO_AF1_TIM2}};

    _debugconst_ RgbLed res1 {
        {htim[tim1], TIM_CHANNEL_4, GPIO_PIN_11, GPIOA, GPIO_AF1_TIM1},
        {htim[tim1], TIM_CHANNEL_3, GPIO_PIN_10, GPIOA, GPIO_AF1_TIM1},
        {htim[tim3], TIM_CHANNEL_2, GPIO_PIN_5, GPIOB, GPIO_AF2_TIM3}};

    // _debugconst_ RgbLed freq2 {
    //     NoLedElement,
    //     {TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOA, GPIO_AF1_TIM1},
    //     {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOA, GPIO_AF1_TIM1}};

    // _debugconst_ RgbLed res2 {
    //     NoLedElement,
    //     {TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOB, GPIO_AF1_TIM1},
    //     {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOB, GPIO_AF1_TIM1}};

    // _debugconst_ RgbLed mode[5] {
    //     {{TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOB, GPIO_AF1_TIM1},
    //      NoLedElement,
    //      {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOB, GPIO_AF1_TIM1}},

    //     {{TIM1, TIM_CHANNEL_1, GPIO_PIN_8, GPIOB, GPIO_AF1_TIM1},
    //      NoLedElement,
    //      {TIM1, TIM_CHANNEL_3, GPIO_PIN_9, GPIOB, GPIO_AF1_TIM1}},

    //     {{TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOA, GPIO_AF1_TIM1},
    //      NoLedElement,
    //      {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOA, GPIO_AF1_TIM1}},

    //     {{TIM1, TIM_CHANNEL_1, GPIO_PIN_2, GPIOA, GPIO_AF1_TIM1},
    //      NoLedElement,
    //      {TIM1, TIM_CHANNEL_3, GPIO_PIN_3, GPIOA, GPIO_AF1_TIM1}},

    //     {{TIM1, TIM_CHANNEL_1, GPIO_PIN_4, GPIOA, GPIO_AF1_TIM1},
    //      NoLedElement,
    //      {TIM1, TIM_CHANNEL_3, GPIO_PIN_5, GPIOA, GPIO_AF1_TIM1}},
    // };

private:
    NoLed NoLedElement;
};

