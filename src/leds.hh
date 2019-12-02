#pragma once
#include <stm32f7xx.h>
#include "tim_pwm.hh"
#include "pin.hh"
#include "colors.hh"


class LedCtl {

public:
    LedCtl() {    }

    //Todo: only update if glowing or fading
    void update() {
        freq1.refresh();
        res1.refresh();
        freq2.refresh();
        res2.refresh();
        mode[0].refresh();
        mode[1].refresh();
        mode[2].refresh();
        mode[3].refresh();
        mode[4].refresh();
    }

public:
    RgbLed freq1 {
        {TIM8, TimChannelNum::_4, GPIO_PIN_9, GPIOC, LL_GPIO_AF_3},
        {TIM8, TimChannelNum::_3, GPIO_PIN_8, GPIOC, LL_GPIO_AF_3},
        {TIM2, TimChannelNum::_2, GPIO_PIN_3, GPIOB, LL_GPIO_AF_1}};

    RgbLed res1 {
        {TIM1, TimChannelNum::_4, GPIO_PIN_11, GPIOA, LL_GPIO_AF_1},
        {TIM1, TimChannelNum::_3, GPIO_PIN_10, GPIOA, LL_GPIO_AF_1},
        {TIM3, TimChannelNum::_2, GPIO_PIN_5, GPIOB, LL_GPIO_AF_2}};

    RgbLed freq2 {
        NoLedElement,
        {TIM3, TimChannelNum::_1, GPIO_PIN_6, GPIOA, LL_GPIO_AF_2},
        {TIM8, TimChannelNum::_1N, GPIO_PIN_7, GPIOA, LL_GPIO_AF_3}};

    RgbLed res2 {
        NoLedElement,
        {TIM3, TimChannelNum::_3, GPIO_PIN_0, GPIOB, LL_GPIO_AF_2},
        {TIM3, TimChannelNum::_4, GPIO_PIN_1, GPIOB, LL_GPIO_AF_2}};

    RgbLed mode[5] {
        {{TIM4, TimChannelNum::_1, GPIO_PIN_6, GPIOB, LL_GPIO_AF_2},
         NoLedElement,
         {TIM4, TimChannelNum::_2, GPIO_PIN_7, GPIOB, LL_GPIO_AF_2}},

        {{TIM4, TimChannelNum::_3, GPIO_PIN_8, GPIOB, LL_GPIO_AF_2},
         NoLedElement,
         {TIM4, TimChannelNum::_4, GPIO_PIN_9, GPIOB, LL_GPIO_AF_2}},

        {{TIM2, TimChannelNum::_1, GPIO_PIN_0, GPIOA, LL_GPIO_AF_1},
         NoLedElement,
         {TIM5, TimChannelNum::_2, GPIO_PIN_1, GPIOA, LL_GPIO_AF_2}},

        {{TIM2, TimChannelNum::_3, GPIO_PIN_2, GPIOA, LL_GPIO_AF_1},
         NoLedElement,
         {TIM2, TimChannelNum::_4, GPIO_PIN_3, GPIOA, LL_GPIO_AF_1}},

        {NoLedElement,  //DAC0 PA4
         NoLedElement,
         NoLedElement}, //DAC1 PA5
    };

private:
    NoLed NoLedElement;
};

