/* 
 * pin.hh
 *
 * Based on: GPIO.hpp by Peter Züger (12.08.2017)
 * (https://gitlab.com/peterzuger/let)
 * Adapted to use ST's LL drivers by Dan Green.
 * Portions are copyright (c) 2019 Peter Züger
 * Portions are copyright (c) 2019 Dan Green <danngreen1@gmail.com>
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
enum class PinPolarity { NORMAL, INVERTED };
enum class PinMode { INPUT, OUTPUT, ANALOG, ALT };
enum class PinPull { UP, DOWN, NONE };
enum class PinSpeed { LOW, MEDIUM, HIGH, VERY_HIGH };
enum class PinOType { PUSHPULL, OPENDRAIN };

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

// template <auto port>

template<GPIO port, uint8_t pin> //Todo: does auto pin work? Might save an asm extend to use uint32_t
class PinL {
    static_assert((pin <= 15) && (pin >= 0), "GPIO Pin pin out of range [0 ... 15]");

    auto GPIOPort(GPIO port_) {
        return reinterpret_cast<GPIO_TypeDef *>(port_);
    }

    PinL() = default;

    PinL(PinMode m){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
    }

    PinL(PinMode m, PinOType o){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        OutputType(o);
    }

    PinL(PinMode m, PinPull pp){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        PullUpDown(pp);
    }

    PinL(PinMode m, uint8_t af, PinPull pp=PinPull::NONE){
        System::enable_gpio_rcc(GPIOPort(port));
        mode(m);
        AlternateFunction(af);
        PullUpDown(pp);
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
            set();
        else
            clear();
    }
    bool read(){
        return (GPIOPort(port)->IDR & pin ? true : false);
        // return memory<std::uint32_t>(P+R::IDR) & BIT(p);
    }

    void set(){
        GPIOPort(port)->BSRR = 1 << pin;
        // memory<std::uint32_t>(P+R::BSRR) = BIT(p);
    }

    void clear(){
        GPIOPort(port)->BSRR = 1<<(pin+16);
        // memory<std::uint16_t>(P+R::BSRR+2) = BIT(p);
    }

    void toggle(){
        GPIOPort(port)->ODR ^= 1<<pin;
        // memory<std::uint32_t>(P+R::ODR) ^= BIT(p);
    }

    void mode(PinMode m){
        // memory<std::uint32_t>(P+R::MODER) &= ~(0b11 << (p*2));

        // switch(m){
        // case PinMode::Input:
        //     memory<std::uint32_t>(P+R::MODER) |= (B::Input << (p*2));
        //     break;

        // case PinMode::Output:
        //     memory<std::uint32_t>(P+R::MODER) |= (B::Output << (p*2));
        //     break;

        // case PinMode::Alternate:
        //     memory<std::uint32_t>(P+R::MODER) |= (B::Alternate << (p*2));
        //     break;

        // case PinMode::Analog:
        //     memory<std::uint32_t>(P+R::MODER) |= (B::Analog << (p*2));
        //     break;

        // default:
        //     break;
        // }
    }

    void OutputType(PinOType o){
        // if(o == PinOType::OpenDrain)
        //     memory<std::uint32_t>(P+R::OTYPER) |= BIT(p);
        // else
        //     memory<std::uint32_t>(P+R::OTYPER) &= ~BIT(p);
    }

    void OutputSpeed(PinSpeed o){
        // memory<std::uint32_t>(P+R::OSPEEDR) &= ~(0b11 << (p*2));

        // switch(o){
        // case PinSpeed::Slow:
        //     memory<std::uint32_t>(P+R::OSPEEDR) |= (B::Slow << (p*2));
        //     break;

        // case PinSpeed::Medium:
        //     memory<std::uint32_t>(P+R::OSPEEDR) |= (B::Medium << (p*2));
        //     break;

        // case PinSpeed::Fast:
        //     memory<std::uint32_t>(P+R::OSPEEDR) |= (B::Fast << (p*2));
        //     break;

        // case PinSpeed::High:
        //     memory<std::uint32_t>(P+R::OSPEEDR) |= (B::High << (p*2));
        //     break;

        // default:
        //     break;
        // }
    }

    void PullUpDown(PinPull m){
        // memory<std::uint32_t>(P+R::PUPDR) &= ~(0b11 << (p*2));

        // switch(m){
        // case PinPull::NOPULL:
        //     memory<std::uint32_t>(P+R::PUPDR) |= (B::NoPull << (p*2));
        //     break;

        // case PinPull::PULLUP:
        //     memory<std::uint32_t>(P+R::PUPDR) |= (B::Pullup << (p*2));
        //     break;

        // case PinPull::PULLDOWN:
        //     memory<std::uint32_t>(P+R::PUPDR) |= (B::Pulldown << (p*2));
        //     break;

        // default:
        //     break;
        // }
    }

    void AlternateFunction(const uint8_t f){
        // if(p < 8){
        //     memory<std::uint32_t>(P+R::AFRL) &= ~(0xF << (p*4));
        //     memory<std::uint32_t>(P+R::AFRL) |= (f << (p*4));
        // }else{
        //     memory<std::uint32_t>(P+R::AFRH) &= ~(0xF << ((p-8)*4));
        //     memory<std::uint32_t>(P+R::AFRH) |= (f << ((p-8)*4));
        // }
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
