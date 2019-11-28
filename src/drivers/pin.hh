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
        init_rcc();
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

private:
    void init_rcc() {
        #ifdef GPIOA
        if (port_==GPIOA && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
        #endif
        #ifdef GPIOB
        if (port_==GPIOB && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
        #endif
        #ifdef GPIOC
        if (port_==GPIOC && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
        #endif
        #ifdef GPIOD
        if (port_==GPIOD && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
        #endif
        #ifdef GPIOE
        if (port_==GPIOE && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
        #endif
        #ifdef GPIOF
        if (port_==GPIOF && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
        #endif
        #ifdef GPIOG
        if (port_==GPIOG && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
        #endif
        #ifdef GPIOH
        if (port_==GPIOH && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
        #endif
        #ifdef GPIOI
        if (port_==GPIOI && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
        #endif
        #ifdef GPIOJ
        if (port_==GPIOJ && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
        #endif
        #ifdef GPIOK
        if (port_==GPIOK && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN)) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
        #endif
    }

};

using Pin = PinWithPolarity<PinPolarity::NORMAL>;
using PinInverted = PinWithPolarity<PinPolarity::INVERTED>;
