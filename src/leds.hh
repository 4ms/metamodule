#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "system.hh"

struct Color {
    struct Adjustment {
        uint8_t r, g, b;
    };

    explicit constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}

    uint8_t red() { return r_; }
    uint8_t green() { return g_; }
    uint8_t blue() { return b_; }

    const Color operator+(Color const that) const {
        return Color(__UQADD8(r_, that.r_),
                    __UQADD8(g_, that.g_),
                    __UQADD8(b_, that.b_));
    }

    constexpr Color blend(Color const that) const {
        return Color((r_>>1) + (that.r_>>1),
                     (g_>>1) + (that.g_>>1),
                     (b_>>1) + (that.b_>>1));
    }

    // constexpr const Color blend(Color const that, uint8_t const phase) const {
    //     return Color(Signal::crossfade(r_, that.r_, phase),
    //                 Signal::crossfade(g_, that.g_, phase),
    //                 Signal::crossfade(b_, that.b_, phase));
    // }

    constexpr const bool operator!=(Color const that) {
        return this->r_ != that.r_ || this->g_ != that.g_ || this->b_ != that.b_;
    }

    constexpr const Color adjust(Adjustment const adj) const {
        // uint16_t ra = r_ * adj.r;
        // uint16_t rg = g_ * adj.g;
        // uint16_t rb = b_ * adj.b;
        // return Color(ra >> 7, rg >> 7, rb >> 7);
        return Color((r_ * adj.r) >> 7,
                     (g_ * adj.g) >> 7,
                     (b_ * adj.b) >> 7);
    } 

private:
    uint8_t r_, g_, b_;
};

class TimPwmLed {
public:
    TimPwmLed(TIM_TypeDef *TIM, uint32_t channel, uint16_t pin, GPIO_TypeDef *port, uint8_t af) 
    : channel_(channel), pin_(pin, port, af) {
        System::enable_tim_rcc(TIM);

        htim_.Instance = TIM;
        htim_.Init.Prescaler = 1;
        htim_.Init.Period = 256;
        htim_.Init.ClockDivision = 0;
        htim_.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim_.Init.RepetitionCounter = 0;
        htim_.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
        HAL_TIM_PWM_Init(&htim_);

        TIM_OC_InitTypeDef tim_oc;
        tim_oc.OCMode = TIM_OCMODE_PWM1;
        tim_oc.OCPolarity = TIM_OCPOLARITY_LOW;
        tim_oc.OCFastMode = TIM_OCFAST_DISABLE;
        tim_oc.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        tim_oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
        tim_oc.OCIdleState = TIM_OCIDLESTATE_RESET;
        tim_oc.Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(&htim_, &tim_oc, channel_);
        HAL_TIM_PWM_Start(&htim_, channel_);
    }

    void set_brightness(uint32_t val) {
        __HAL_TIM_SET_COMPARE(&htim_, channel_, val);
    }

private:
    Pin<NORMAL> pin_;
    TIM_HandleTypeDef htim_;
    uint32_t channel_;
};

struct RgbLed {
    RgbLed(TimPwmLed r_LED, TimPwmLed g_LED, TimPwmLed b_LED) 
    : r_(r_LED), g_(g_LED), b_(b_LED) {}

    void set_color(Color col) {
        r_.set_brightness(col.red());
        g_.set_brightness(col.green());
        b_.set_brightness(col.blue());
    }
    void set_color(Color col, uint8_t brightness) {
        r_.set_brightness((col.red() * brightness)>>8);
        g_.set_brightness((col.green() * brightness)>>8);
        b_.set_brightness((col.blue() * brightness)>>8);
    }
private:
    TimPwmLed r_, g_, b_;
};

struct RbLed {
    RbLed(TimPwmLed r_LED, TimPwmLed b_LED) 
    : r_(r_LED), b_(b_LED) {}

    void set_color(Color col) {
        r_.set_brightness(col.red());
        b_.set_brightness(col.blue());
    }
    void set_color(Color col, uint8_t brightness) {
        r_.set_brightness((col.red() * brightness)>>8);
        b_.set_brightness((col.blue() * brightness)>>8);
    }
private:
    TimPwmLed r_, b_;
};

struct GbLed {
    GbLed(TimPwmLed g_LED, TimPwmLed b_LED) 
    : g_(g_LED), b_(b_LED) {}

    void set_color(Color col) {
        g_.set_brightness(col.green());
        b_.set_brightness(col.blue());
    }
    void set_color(Color col, uint8_t brightness) {
        g_.set_brightness((col.green() * brightness)>>8);
        b_.set_brightness((col.blue() * brightness)>>8);
    }
private:
    TimPwmLed g_, b_;
};


class LedCtl {
public:
    LedCtl() {}

    RgbLed ledFreq1 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_9, GPIOC, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_2, GPIO_PIN_8, GPIOC, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_3, GPIOB, GPIO_AF1_TIM1}};

    RgbLed ledRes1 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_11, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_2, GPIO_PIN_10, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_5, GPIOB, GPIO_AF1_TIM1}};

    GbLed ledFreq2 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOA, GPIO_AF1_TIM1}};

    GbLed ledRes2 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOB, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOB, GPIO_AF1_TIM1}};

    RbLed ledMode[5] {
        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOB, GPIO_AF1_TIM1},
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOB, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_8, GPIOB, GPIO_AF1_TIM1},
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_9, GPIOB, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOA, GPIO_AF1_TIM1},
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOA, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_2, GPIOA, GPIO_AF1_TIM1},
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_3, GPIOA, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_4, GPIOA, GPIO_AF1_TIM1},
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_5, GPIOA, GPIO_AF1_TIM1}},
    };
};

