#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "system.hh"
#include "colors.hh"

//Todo Re-do this with LL

// #define _debugconst_ const
#define _debugconst_

class TimPwm {
public:
    TimPwm(TIM_TypeDef *TIM) {
        System::enable_tim_rcc(TIM);

        htim_.Instance = TIM;
        htim_.Init.Prescaler = 1;
        htim_.Init.Period = 256;
        htim_.Init.ClockDivision = 0;
        htim_.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim_.Init.RepetitionCounter = 0;
        htim_.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
        HAL_TIM_PWM_Init(&htim_);
    }

    TIM_HandleTypeDef& get_htim() {return htim_;}

private:
    TIM_HandleTypeDef htim_;
};


class TimPwmLed {
protected:
    TimPwmLed() : htim_(nohtim_) {}
public:
    TimPwmLed(TIM_HandleTypeDef& htim, uint32_t channel, uint16_t pin, GPIO_TypeDef *port, uint8_t af) 
    : channel_(channel), pin_(pin, port, ALT, NONE, MEDIUM, af), htim_(htim) {
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

    void set_brightness(uint32_t val) _debugconst_ {
        __HAL_TIM_SET_COMPARE(&htim_, channel_, val);
    }

private:
    Pin<NORMAL> pin_;
    TIM_HandleTypeDef& htim_;
    TIM_HandleTypeDef nohtim_;
    uint32_t channel_;
};

class NoLed : public TimPwmLed {
public:
    NoLed() {}
    void set_brightness(uint32_t val) {}
};

struct RgbLed {
    RgbLed(TimPwmLed r_LED, TimPwmLed g_LED, TimPwmLed b_LED) 
    : r_(r_LED), g_(g_LED), b_(b_LED) {}

    void set_background(Color col) {background_color_ = col;}
    void set_solid(Color col) {solid_color_ = col;}

    // flash_freq in Hz; max = update_rate
    void flash(Color c, uint32_t flash_freq = 100) {
        flash_color_ = c;
        flash_phase_ = 0xFFFFFFFF;
        flash_freq_ = flash_freq; // divided by update_rate?
    }

    // freq in secs
    void set_glow(Color c, uint32_t freq = 0x00FFFFFF) {
        glow_color_ = c;
        osc_.set_frequency(freq); //divided by update_rate?
    }

    void set_color(Color col) _debugconst_ {
        r_.set_brightness(col.red());
        g_.set_brightness(col.green());
        b_.set_brightness(col.blue());
    }
    void set_color(Color col, uint8_t brightness) _debugconst_ {
        r_.set_brightness((col.red() * brightness)>>8);
        g_.set_brightness((col.green() * brightness)>>8);
        b_.set_brightness((col.blue() * brightness)>>8);
    }
    void set_color(Color col, float brightness) _debugconst_ {
        r_.set_brightness(col.red() * brightness);
        g_.set_brightness(col.green() * brightness);
        b_.set_brightness(col.blue() * brightness);
    }

    //Todo: don't waste cycles updating if nothing's changed
    void refresh() {
        Color c = background_color_;
        if (solid_color_ != Colors::off) c = solid_color_;
        c = c.blend(glow_color_, osc_.Process() >> 24);
        c = c.blend(flash_color_, flash_phase_ >> 24);
        // c = c.adjust(color_cal_);
        set_color(c);
        if (flash_phase_ > flash_freq_) flash_phase_ -= flash_freq_;
        else flash_phase_ = 0;
    }

private:
    TimPwmLed r_, g_, b_;
    TriangleOscillator<89478> osc_;
    Color background_color_ = Colors::off;
    Color solid_color_ = Colors::off;
    Color flash_color_ = Colors::white;
    Color glow_color_ = Colors::red;
    uint32_t flash_freq_ = 100;
    uint32_t flash_phase_ = 0;
//    Color::Adjustment& color_cal_;
};

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
        // r.high(); r.low();
        // g.high(); g.low();
        // b.high(); b.low();

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
        // m1r.high(); m1r.low();
        // m1b.high(); m1b.low();
        // m2r.high(); m2r.low();
        // m2b.high(); m2b.low();
        // m3r.high(); m3r.low();
        // m3b.high(); m3b.low();
        // m4r.high(); m4r.low();
        // m4b.high(); m4b.low();
        // m5r.high(); m5r.low();
        // m5b.high(); m5b.low();

        // freq2g.high(); freq2g.low();
        // freq2b.high(); freq2b.low();
        // res2g.high(); res2g.low();
        // res2b.high(); res2b.low();
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
        {htim[tim8].get_htim(), TIM_CHANNEL_4, GPIO_PIN_9, GPIOC, GPIO_AF3_TIM8},
        {htim[tim8].get_htim(), TIM_CHANNEL_3, GPIO_PIN_8, GPIOC, GPIO_AF3_TIM8},
        {htim[tim2].get_htim(), TIM_CHANNEL_2, GPIO_PIN_3, GPIOB, GPIO_AF1_TIM2}};

    _debugconst_ RgbLed res1 { 
        {htim[tim1].get_htim(), TIM_CHANNEL_4, GPIO_PIN_11, GPIOA, GPIO_AF1_TIM1},
        {htim[tim1].get_htim(), TIM_CHANNEL_3, GPIO_PIN_10, GPIOA, GPIO_AF1_TIM1},
        {htim[tim3].get_htim(), TIM_CHANNEL_2, GPIO_PIN_5, GPIOB, GPIO_AF2_TIM3}};

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

