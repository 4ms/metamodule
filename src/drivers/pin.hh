/* 
 * pin.hh
 *
 * Inspried by GPIO.hpp by Peter Züger (12.08.2017) https://gitlab.com/peterzuger/let
 * Portions may be copyright (c) 2019 Peter Züger
 * Remaining code is copyright (c) 2019 Dan Green <danngreen1@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "system.hh"
#include "stm32f7xx.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_bus.h"

enum class PinPolarity { 
    Normal, 
    Inverted 
};

enum class PinMode : uint32_t { 
    Input = LL_GPIO_MODE_INPUT, 
    Output = LL_GPIO_MODE_OUTPUT,
    Analog = LL_GPIO_MODE_ANALOG, 
    Alt = LL_GPIO_MODE_ALTERNATE 
};

enum class PinPull : uint32_t { 
    Up = LL_GPIO_PULL_UP,
    Down = LL_GPIO_PULL_DOWN,
    None = LL_GPIO_PULL_NO
};

enum class PinSpeed : uint32_t { 
    Low = LL_GPIO_SPEED_FREQ_LOW, 
    Medium = LL_GPIO_SPEED_FREQ_MEDIUM, 
    High = LL_GPIO_SPEED_FREQ_HIGH, 
    VeryHigh = LL_GPIO_SPEED_FREQ_VERY_HIGH 
};

enum class PinOType : uint32_t { 
    PushPull = LL_GPIO_OUTPUT_PUSHPULL, 
    OpenDrain = LL_GPIO_OUTPUT_OPENDRAIN
};

enum class GPIO : uint32_t {
    A = GPIOA_BASE, 
    B = GPIOB_BASE, 
    C = GPIOC_BASE, 
    D = GPIOD_BASE, 
    E = GPIOE_BASE,
    F = GPIOF_BASE,
    G = GPIOG_BASE,
    H = GPIOH_BASE,
    #ifdef GPIOI_BASE
    I = GPIOI_BASE,
    #endif
    #ifdef GPIOJ_BASE
    J = GPIOJ_BASE,
    #endif
    #ifdef GPIOK_BASE
    K = GPIOK_BASE,
    #endif
};

template<GPIO port, uint8_t pin, PinPolarity polarity=PinPolarity::Normal> 
struct PinL {
    static_assert((pin <= 15) && (pin >= 0), "GPIO pin number must be in the range 0 - 15");

    auto GPIOPort(GPIO port_) {
        return reinterpret_cast<GPIO_TypeDef *>(port_);
    }
    template<class X>
    auto LL(X p) {
        return static_cast<uint32_t>(p);
    }

    PinL() = default;

    constexpr PinL(PinMode m) {
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
    }

    constexpr PinL(PinMode m, PinOType o) {
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        out_type(o);
    }

    constexpr PinL(PinMode m, PinPull pp) {
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        pull(pp);
    }

    constexpr PinL(PinMode m, uint8_t af, PinPull pp=PinPull::None) {
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        alt_func(af);
        pull(pp);
    }

    operator bool() {
        return read();
    }

    PinL& operator=(bool val) {
        write(val);
        return *this;
    }

    void write(bool val) {
        if(val)
            high();
        else
            low();
    }
    bool read() {
        return LL_GPIO_IsInputPinSet(GPIOPort(port), 1<<pin);
    }
    bool is_on() {
        return (polarity==PinPolarity::Inverted) ? !read() : read();
    }

    void high() {
        LL_GPIO_SetOutputPin(GPIOPort(port), 1<<pin);
    }
    void low() {
        LL_GPIO_ResetOutputPin(GPIOPort(port), 1<<pin);
    }
    void toggle() {
        LL_GPIO_TogglePin(GPIOPort(port), 1<<pin);
    }
    void on() {
        if (polarity==PinPolarity::Inverted) low(); else high();
    }
    void off() {
        if (polarity==PinPolarity::Inverted) high(); else low();
    }
    void set_to(uint32_t v) {
        if (v) on(); else off();
    }
    void set_to(bool v) {
        if (v) on(); else off();
    }

    void mode(PinMode m){
        LL_GPIO_SetPinMode(GPIOPort(port), 1<<pin, LL(m));
    }
    void out_type(PinOType o){
        LL_GPIO_SetPinOutputType(GPIOPort(port), 1<<pin, LL(o));
    }
    void out_speed(PinSpeed s){
        LL_GPIO_SetPinSpeed(GPIOPort(port), 1<<pin, LL(s));
    }
    void pull(PinPull p){
        LL_GPIO_SetPinPull(GPIOPort(port), 1<<pin, LL(p));
    }
    void alt_func(const uint8_t af){
       if (pin >= LL_GPIO_PIN_8)
            LL_GPIO_SetAFPin_8_15(GPIOPort(port), 1<<pin, af);
        else
            LL_GPIO_SetAFPin_0_7(GPIOPort(port), 1<<pin, af);
    }
};   
