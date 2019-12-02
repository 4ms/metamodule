#pragma once
#include <stm32f7xx.h>
#include "system.hh"
#include "colors.hh"
#include "stm32f7xx_ll_tim.h"

enum class TimChannelNum {
    _1=LL_TIM_CHANNEL_CH1,
    _1N=LL_TIM_CHANNEL_CH1N,
    _2=LL_TIM_CHANNEL_CH2,
    _2N=LL_TIM_CHANNEL_CH2N,
    _3=LL_TIM_CHANNEL_CH3,
    _3N=LL_TIM_CHANNEL_CH3N,
    _4=LL_TIM_CHANNEL_CH4,
    _5=LL_TIM_CHANNEL_CH5,
    _6=LL_TIM_CHANNEL_CH6
};


// #define _debugconst_ const
#define _debugconst_

class TimPwmPeriph;
class TimPwmChannel;
class NoLed;


class TimPwmPeriph {
friend class TimPwmChannel;
private:
    static void init_periph_once(TIM_TypeDef *TIM, 
                                uint32_t period=256,
                                uint16_t prescaler=0, 
                                uint32_t clock_division=0)
    {
        static bool did_init[16]={false};

        uint8_t tim_i = System::tim_periph_to_num(TIM);
        if (!tim_i) return; //Todo: check exception implications of using assert

        tim_i--;
        if (!did_init[tim_i]) {
            System::enable_tim_rcc(TIM);
            LL_TIM_InitTypeDef timinit = {
                .Prescaler = prescaler,
                .CounterMode = LL_TIM_COUNTERMODE_UP,
                .Autoreload = period,
                .ClockDivision = clock_division,
                .RepetitionCounter = 0
            };
            LL_TIM_Init(TIM, &timinit); 
            LL_TIM_DisableARRPreload(TIM);

            did_init[tim_i] = true;
        }
    }
};

enum class TimPwmOutType {Norm, N};

// TimPwmChannel: output PWM on a pin
// automatically initializes the given TIM peripheral if it hasn't been initialized yet
// Usage:
// TimPwmChannel myPWMOutput {TIM1, TimChannelNum::_2, GPIO_PIN_3, GPIOA, 
class TimPwmChannel {
public:
    TimPwmChannel(  TIM_TypeDef* const TIM,
                TimChannelNum const channel,
                uint16_t const pin, 
                GPIO_TypeDef * const port, 
                uint8_t const af, 
                TimPwmOutType out_n = TimPwmOutType::Norm,
                uint32_t period=256,
                uint16_t prescaler=0, 
                uint32_t clock_division=0)
    : TIM_(TIM),
      channel_(channel)
    {
        Pin output_pin{pin, port, PinMode::ALT, PinPull::NONE, PinSpeed::MEDIUM, af};

        TimPwmPeriph::init_periph_once(TIM, period, prescaler, clock_division);

        if (channel_==TimChannelNum::_1N)
            channel_base_ = TimChannelNum::_1;
        else if (channel_== TimChannelNum::_2N)
            channel_base_ = TimChannelNum::_2;
        else if (channel_== TimChannelNum::_3N)
            channel_base_ = TimChannelNum::_3;
        else 
            channel_base_ = channel_;

        LL_TIM_OC_InitTypeDef tim_oc
         = {
            .OCMode = LL_TIM_OCMODE_PWM1,
            .OCState = out_n==TimPwmOutType::Norm ? LL_TIM_OCSTATE_ENABLE : LL_TIM_OCSTATE_DISABLE,
            .OCNState = out_n==TimPwmOutType::Norm ? LL_TIM_OCSTATE_DISABLE : LL_TIM_OCSTATE_ENABLE,
            .CompareValue = 0,
            .OCPolarity = LL_TIM_OCPOLARITY_LOW,
            .OCNPolarity = LL_TIM_OCPOLARITY_HIGH,
            .OCIdleState = LL_TIM_OCIDLESTATE_LOW,
            .OCNIdleState = LL_TIM_OCIDLESTATE_LOW,
        };

        LL_TIM_OC_Init(TIM_, static_cast<uint32_t>(channel_base_), &tim_oc);
        LL_TIM_CC_EnableChannel(TIM_, static_cast<uint32_t>(channel_));
        LL_TIM_EnableCounter(TIM_);
    }

    constexpr void set_brightness(uint32_t val) const {
        _set_timer_ccr(TIM_, channel_base_, val);
    }

protected:
    TimPwmChannel() : TIM_(nullptr) {}

private: 
    constexpr void _set_timer_ccr(TIM_TypeDef *TIMx, TimChannelNum channel, uint32_t val) const {
        switch (channel) {
            case TimChannelNum::_1: TIMx->CCR1 = val; break;
            case TimChannelNum::_2: TIMx->CCR2 = val; break;
            case TimChannelNum::_3: TIMx->CCR3 = val; break;
            case TimChannelNum::_4: TIMx->CCR4 = val; break;
            case TimChannelNum::_5: TIMx->CCR5 = val; break;
            default:            TIMx->CCR6 = val; break;
        }
    }

    TIM_TypeDef* const TIM_;
    TimChannelNum channel_;
    TimChannelNum channel_base_;
};

class NoLed : public TimPwmChannel {
public:
    NoLed() {}
    void set_brightness(uint32_t val) const {}
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
        r_.set_brightness(col.red());
        g_.set_brightness(col.green());
        b_.set_brightness(col.blue());
    }
    void set_color(Color const &col, uint8_t const brightness) const {
        r_.set_brightness((col.red() * brightness)>>8);
        g_.set_brightness((col.green() * brightness)>>8);
        b_.set_brightness((col.blue() * brightness)>>8);
    }
    void set_color(Color const &col, float const brightness) const {
        r_.set_brightness(col.red() * brightness);
        g_.set_brightness(col.green() * brightness);
        b_.set_brightness(col.blue() * brightness);
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



