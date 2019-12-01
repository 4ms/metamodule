#pragma once
#include <stm32f7xx.h>
#include "system.hh"
#include "colors.hh"

//Todo Re-do this with LL

// #define _debugconst_ const
#define _debugconst_

//Todo: use local static like ADC, to prevent user from constructding TimPwm's with same TIMx multiple times
//
//It'll be much easier without HAL, since we just pass a TIM_TypeDef * around
//
//Problem with current implementation:
//class xyz { TIM_HandleTypeDef th; 
//              myfunc() { TimPwm timer1{TIM1}; th = timer1.get_htim(); }
// };  
// th will be a ref to a deleted object when myfunc() exits!
//
class TimPwm {
friend class TimPwmLed;
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

    // static TIM_HandleTypeDef PeriphInstance(TIM_TypeDef *TIM) {return ;}

private:
    TIM_HandleTypeDef& get_htim() {return htim_;}
    TIM_HandleTypeDef htim_;
};

enum class TimPwmOutType {Norm, N};

class TimPwmLed {
protected:
    TimPwmLed() : htim_(nohtim_) {}
public:
    TimPwmLed(  TimPwm& timpwm, 
                const uint32_t channel, 
                const uint16_t pin, 
                GPIO_TypeDef * const port, 
                const uint8_t af, 
                TimPwmOutType out_n = TimPwmOutType::Norm)
    : htim_(timpwm.get_htim()), 
      channel_(channel), 
      pin_(pin, port, PinMode::ALT, PinPull::NONE, PinSpeed::MEDIUM, af) 
    {
        init_();
    }

    TimPwmLed(  TIM_HandleTypeDef& htim, 
                const uint32_t channel, 
                const uint16_t pin, 
                GPIO_TypeDef * const port, 
                const uint8_t af, 
                TimPwmOutType out_n = TimPwmOutType::Norm)
    : htim_(htim), 
      channel_(channel), 
      pin_(pin, port, PinMode::ALT, PinPull::NONE, PinSpeed::MEDIUM, af) 
    {
        init_();
    }

    //Todo: finish this type of initialization (passing TIMx and getting a local static Instance)
    // TimPwmLed(TIM_TypeDef *TIM, const uint32_t channel, const uint16_t pin, GPIO_TypeDef * const port, const uint8_t af)
    // : htim_(TimPwm::PeriphInstance(TIM)), channel_(channel), pin_(pin, port, PinMode::ALT, PinPull::NONE, PinSpeed::MEDIUM, af) {
    //     init_();
    // }

    void set_brightness(uint32_t val) _debugconst_ {
        __HAL_TIM_SET_COMPARE(&htim_, channel_, val);
    }

    private: void init_() {
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

private:
    Pin pin_;
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
        // if (solid_color_ != Colors::off) c = solid_color_;
        // c = c.blend(glow_color_, osc_.Process());
        // c = c.blend(flash_color_, flash_phase_);
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
