#pragma once
#include "stm32f7xx.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_bus.h"

enum class PinPolarity { NORMAL, INVERTED };
enum class PinMode {INPUT, OUTPUT, ANALOG, ALT};
enum class PinPull {UP, DOWN, NONE};
enum class PinSpeed {LOW, MEDIUM, HIGH, VERY_HIGH};

//GPIO Pin driver
template<PinPolarity polarity=PinPolarity::NORMAL>
class PinWithPolarity {
public :
    PinWithPolarity() {}
    PinWithPolarity(const uint16_t pin, GPIO_TypeDef * const port, const enum PinMode mode, const enum PinPull pull = PinPull::NONE, const enum PinSpeed speed = PinSpeed::MEDIUM, const uint8_t af = 0)
    : pin_(pin), port_(port)
    {
        System::enable_gpio_rcc(port_);
        auto mode_ = mode == PinMode::INPUT  ? LL_GPIO_MODE_INPUT :
                     mode == PinMode::OUTPUT ? LL_GPIO_MODE_OUTPUT :
                     mode == PinMode::ANALOG ? LL_GPIO_MODE_ANALOG :
                     mode == PinMode::ALT    ? LL_GPIO_MODE_ALTERNATE :
                                               LL_GPIO_MODE_OUTPUT;
        auto pull_ = pull == PinPull::UP    ? GPIO_PULLUP :
                     pull == PinPull::DOWN  ? GPIO_PULLDOWN :
                                              GPIO_NOPULL;
        auto speed_ = speed == PinSpeed::LOW        ? GPIO_SPEED_FREQ_LOW :
                      speed == PinSpeed::MEDIUM     ? GPIO_SPEED_FREQ_MEDIUM :
                      speed == PinSpeed::HIGH       ? GPIO_SPEED_FREQ_HIGH :
                      speed == PinSpeed::VERY_HIGH  ? GPIO_SPEED_FREQ_VERY_HIGH :
                                                      GPIO_SPEED_FREQ_MEDIUM;
        LL_GPIO_SetPinMode(port_, pin_, mode_);
        LL_GPIO_SetPinPull(port_, pin_, pull_);
        LL_GPIO_SetPinSpeed(port_, pin_, speed_);
        // if (mode_==PinMode::OUTPUT)
        LL_GPIO_SetPinOutputType(port_, pin_, LL_GPIO_OUTPUT_PUSHPULL); //OD not supported by class
        if (mode==PinMode::ALT) {
            if (pin_ >= LL_GPIO_PIN_8)
                LL_GPIO_SetAFPin_8_15(port_, pin_, af);
            else
                LL_GPIO_SetAFPin_0_7(port_, pin_, af);
        }
    }

private:
    uint16_t pin_;
    GPIO_TypeDef* port_;

public:
    void high() {port_->BSRR = pin_;}
    void low() {port_->BSRR = (uint32_t)pin_ << 16;}
    void on() {if (polarity==PinPolarity::INVERTED) low(); else high();}
    void off() {if (polarity==PinPolarity::INVERTED) high(); else low();}
    void set(uint32_t v) {if (v) on(); else off();}

    bool read_raw() {return ((port_->IDR) & pin_) ? true : false;}
    uint8_t is_on() {return (polarity==PinPolarity::INVERTED) ? !read_raw() : read_raw();}
};

using Pin = PinWithPolarity<PinPolarity::NORMAL>;
using PinInverted = PinWithPolarity<PinPolarity::INVERTED>;
