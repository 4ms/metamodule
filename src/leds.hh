#pragma once
#include <stm32f7xx.h>
#include "tim_pwm.hh"
#include "pin.hh"
#include "colors.hh"


class NoLed : public TimPwmChannel {
public:
    NoLed() {}
    void set_output_level(uint32_t val) const {}
};

class DACLed : public TimPwmChannel {
public:
    DACLed(uint8_t dac_chan) : dac_chan_(dac_chan) {}
    void set_output_level(uint32_t val) const {}
private:
    uint8_t dac_chan_;
};

struct RgbLed {
    RgbLed(TimPwmChannel r_LED, TimPwmChannel g_LED, TimPwmChannel b_LED)
    : r_(r_LED), g_(g_LED), b_(b_LED) {}

    void set_background(Color const &col) {background_color_ = col;}
    void set_solid(Color const &col) {solid_color_ = col;}

    void flash(Color const &c, uint32_t const flash_freq = 100) {
        flash_color_ = c;
        flash_phase_ = 0xFFFFFFFF;
        flash_freq_ = flash_freq; // divided by update_rate?
    }

    // freq in secs
    void set_glow(Color const &c, uint32_t const freq = 0x00FFFFFF) {
        glow_color_ = c;
        osc_.set_frequency(freq); //divided by update_rate?
    }

    constexpr void set_color(Color const &col) const {
        r_.set_output_level(col.red());
        g_.set_output_level(col.green());
        b_.set_output_level(col.blue());
    }
    void set_color(Color const &col, uint8_t const brightness) const {
        r_.set_output_level((col.red() * brightness)>>8);
        g_.set_output_level((col.green() * brightness)>>8);
        b_.set_output_level((col.blue() * brightness)>>8);
    }
    void set_color(Color const &col, float const brightness) const {
        r_.set_output_level(col.red() * brightness);
        g_.set_output_level(col.green() * brightness);
        b_.set_output_level(col.blue() * brightness);
    }

    //Todo: don't waste cycles updating if nothing's changed
    void refresh() {
        Color c = background_color_;
        // if (solid_color_ != Colors::off) c = solid_color_;
        // c = c.blend(glow_color_, osc_.Process());
        // c = c.blend(flash_color_, flash_phase_);
        // c = c.adjust(color_cal_);
        set_color(c);
        if (flash_phase_ > flash_freq_) flash_phase_ -= flash_freq_;
        else flash_phase_ = 0;
    }

private:
    TimPwmChannel const r_, g_, b_;
    TriangleOscillator<89478> osc_;
    Color background_color_ = Colors::off;
    Color solid_color_ = Colors::off;
    Color flash_color_ = Colors::white;
    Color glow_color_ = Colors::red;
    uint32_t flash_freq_ = 100;
    uint32_t flash_phase_ = 0;
//    Color::Adjustment& color_cal_;
};



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
        {NoLedElement,  //DAC0 PA4
         NoLedElement,
         NoLedElement}, //DAC1 PA5

        {{TIM2, TimChannelNum::_3, GPIO_PIN_2, GPIOA, LL_GPIO_AF_1},
         NoLedElement,
         {TIM2, TimChannelNum::_4, GPIO_PIN_3, GPIOA, LL_GPIO_AF_1}},

        {{TIM2, TimChannelNum::_1, GPIO_PIN_0, GPIOA, LL_GPIO_AF_1},
         NoLedElement,
         {TIM5, TimChannelNum::_2, GPIO_PIN_1, GPIOA, LL_GPIO_AF_2}},

        {{TIM4, TimChannelNum::_3, GPIO_PIN_8, GPIOB, LL_GPIO_AF_2},
         NoLedElement,
         {TIM4, TimChannelNum::_4, GPIO_PIN_9, GPIOB, LL_GPIO_AF_2}},

        {{TIM4, TimChannelNum::_1, GPIO_PIN_6, GPIOB, LL_GPIO_AF_2},
         NoLedElement,
         {TIM4, TimChannelNum::_2, GPIO_PIN_7, GPIOB, LL_GPIO_AF_2}},
    };

private:
    NoLed NoLedElement;
};

