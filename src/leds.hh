#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "system.hh"
// #define _debugconst_ const
#define _debugconst_

struct Color {
    //Todo: measure how much slower it is to use floats for Adjustment.r/b/g
    struct Adjustment {
        uint8_t r, g, b;
    };

    explicit constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}

    uint8_t red() const { return r_; }
    uint8_t green() const { return g_; }
    uint8_t blue() const { return b_; }

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

    constexpr const Color blend(Color const that, uint8_t const phase) const {
        return Color((r_*(256-phase) + that.r_*phase) >> 8,
                    (g_*(256-phase) + that.g_*phase) >> 8,
                    (b_*(256-phase) + that.b_*phase) >> 8);
    }

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

struct Colors {
    //greyscale
    static constexpr Color off = Color(0, 0, 0);
    static constexpr Color grey = Color(127, 127, 127);
    static constexpr Color white = Color(255, 255, 255);

    static constexpr Color red = Color(255, 0, 0);
};

class TimPwmLed {
protected:
    TimPwmLed() {}
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

    void set_brightness(uint32_t val) _debugconst_ {
        __HAL_TIM_SET_COMPARE(&htim_, channel_, val);
    }

private:
    Pin<NORMAL> pin_;
    TIM_HandleTypeDef htim_;
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
    LedCtl() {}

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

    _debugconst_ RgbLed freq1 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_9, GPIOC, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_2, GPIO_PIN_8, GPIOC, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_3, GPIOB, GPIO_AF1_TIM1}};

    _debugconst_ RgbLed res1 { 
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_11, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_2, GPIO_PIN_10, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_5, GPIOB, GPIO_AF1_TIM1}};

    _debugconst_ RgbLed freq2 { 
        NoLedElement,
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOA, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOA, GPIO_AF1_TIM1}};

    _debugconst_ RgbLed res2 { 
        NoLedElement,
        {TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOB, GPIO_AF1_TIM1},
        {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOB, GPIO_AF1_TIM1}};

    _debugconst_ RgbLed mode[5] {
        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_6, GPIOB, GPIO_AF1_TIM1},
         NoLedElement,
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_7, GPIOB, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_8, GPIOB, GPIO_AF1_TIM1},
         NoLedElement,
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_9, GPIOB, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_0, GPIOA, GPIO_AF1_TIM1},
         NoLedElement,
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_1, GPIOA, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_2, GPIOA, GPIO_AF1_TIM1},
         NoLedElement,
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_3, GPIOA, GPIO_AF1_TIM1}},

        {{TIM1, TIM_CHANNEL_1, GPIO_PIN_4, GPIOA, GPIO_AF1_TIM1},
         NoLedElement,
         {TIM1, TIM_CHANNEL_3, GPIO_PIN_5, GPIOA, GPIO_AF1_TIM1}},
    };

private:
    NoLed NoLedElement;
};

