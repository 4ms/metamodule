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

//Todo: CamelCase, not ALL CAPS
enum class PinPolarity { 
    NORMAL, 
    INVERTED 
};

enum class PinMode : uint32_t { 
    INPUT = LL_GPIO_MODE_INPUT, 
    OUTPUT = LL_GPIO_MODE_OUTPUT,
    ANALOG = LL_GPIO_MODE_ANALOG, 
    ALT = LL_GPIO_MODE_ALTERNATE 
};

enum class PinPull : uint32_t { 
    UP = LL_GPIO_PULL_UP,
    DOWN = LL_GPIO_PULL_DOWN,
    NONE = LL_GPIO_PULL_NO
};

enum class PinSpeed : uint32_t { 
    LOW = LL_GPIO_SPEED_FREQ_LOW, 
    MEDIUM = LL_GPIO_SPEED_FREQ_MEDIUM, 
    HIGH = LL_GPIO_SPEED_FREQ_HIGH, 
    VERY_HIGH = LL_GPIO_SPEED_FREQ_VERY_HIGH 
};

enum class PinOType : uint32_t { 
    PUSHPULL = LL_GPIO_OUTPUT_PUSHPULL, 
    OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN
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

//Todo: does auto pin work? Might save an asm extend to use uint32_t
template<GPIO port, uint8_t pin, PinPolarity polarity=PinPolarity::NORMAL> 
struct PinL {
    static_assert((pin <= 15) && (pin >= 0), "GPIO pin number must be in the range 0 - 15");

    volatile auto GPIOPort(GPIO port_) {
        return reinterpret_cast<GPIO_TypeDef *>(port_);
    }

    PinL() = default;

    constexpr PinL(PinMode m){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
    }

    constexpr PinL(PinMode m, PinOType o){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        out_type(o);
    }

    constexpr PinL(PinMode m, PinPull pp){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        pull(pp);
    }

    constexpr PinL(PinMode m, uint8_t af, PinPull pp=PinPull::NONE){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        alt_func(af);
        pull(pp);
    }

    operator bool(){
        return read();
    }

    PinL& operator=(bool val){
        write(val);
        return *this;
    }

    void write(bool val){
        if(val)
            high();
        else
            low();
    }
    bool read(){
        return (GPIOPort(port)->IDR & (1<<pin) ? true : false);
        // Todo: compare to:
        // return LL_GPIO_IsInputPinSet(GPIOPort(port), 1<<pin);
    }

    void high(){
        GPIOPort(port)->BSRR = 1 << pin;
        // Todo: compare to:
        // LL_GPIO_SetOutputPin(GPIOPort(port), 1<<pin);
    }

    void low(){
        GPIOPort(port)->BSRR = 1<<(pin+16);
        // Todo: compare to:
        // LL_GPIO_ResetOutputPin(GPIOPort(port), 1<<pin);
    }

    void toggle(){
        GPIOPort(port)->ODR ^= 1<<pin;
        // Todo: compare to:
        // LL_GPIO_TogglePin(GPIOPort(port), 1<<pin);
    }

    //on and off 
    void on() {if (polarity==PinPolarity::INVERTED) low(); else high();}
    void off() {if (polarity==PinPolarity::INVERTED) high(); else low();}
    void set_to(uint32_t v) {if (v) on(); else off();}

    bool is_on() {return (polarity==PinPolarity::INVERTED) ? !read() : read();}


    void mode(PinMode m){
        LL_GPIO_SetPinMode(GPIOPort(port), 1<<pin, static_cast<uint32_t>(m));
    }

    void out_type(PinOType o){
        LL_GPIO_SetPinOutputType(GPIOPort(port), 1<<pin, static_cast<uint32_t>(o));
    }

    void out_speed(PinSpeed s){
        LL_GPIO_SetPinSpeed(GPIOPort(port), 1<<pin, static_cast<uint32_t>(s));
    }

    void pull(PinPull p){
        LL_GPIO_SetPinPull(GPIOPort(port), 1<<pin, static_cast<uint32_t>(p));
    }

    void alt_func(const uint8_t af){
//        if (pin >= LL_GPIO_PIN_8)
        if (pin >= 8)
            LL_GPIO_SetAFPin_8_15(GPIOPort(port), 1<<pin, af);
        else
            LL_GPIO_SetAFPin_0_7(GPIOPort(port), 1<<pin, af);
    }
};   

//GPIO Pin driver
template<PinPolarity polarity=PinPolarity::NORMAL>
class PinPolarized {
public :
    PinPolarized() {}
    PinPolarized( uint16_t const pin, 
                    GPIO_TypeDef * const port, 
                    PinMode const mode, 
                    PinPull const pull = PinPull::NONE,
                    PinSpeed const speed = PinSpeed::MEDIUM,
                    uint8_t const af = 0
    )
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

    void high() {port_->BSRR = pin_;}
    void low() {port_->BSRR = (uint32_t)pin_ << 16;}
    void on() {if (polarity==PinPolarity::INVERTED) low(); else high();}
    void off() {if (polarity==PinPolarity::INVERTED) high(); else low();}
    void set(uint32_t v) {if (v) on(); else off();}

    bool read_raw() {return ((port_->IDR) & pin_) ? true : false;}
    uint8_t is_on() {return (polarity==PinPolarity::INVERTED) ? !read_raw() : read_raw();}

private:
    uint16_t pin_;
    GPIO_TypeDef* port_;

};

using Pin = PinPolarized<PinPolarity::NORMAL>;
using PinInverted = PinPolarized<PinPolarity::INVERTED>;
