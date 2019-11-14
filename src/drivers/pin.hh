#pragma once
#include <stm32f7xx.h>

enum PinPolarity {NORMAL, INVERTED};
enum PinMode {INPUT, OUTPUT, ANALOG, ALT};

//todo: don't use HAL and templatize with Pin and Port. template for INPUT/OUTPUT/ALT ?
template<PinPolarity polarity>
class Pin {
public:
    uint16_t pin;
    GPIO_TypeDef *port;
    //Todo: use default values in argument list, and make pin_, pull, speed to be enums
    Pin() {}
    Pin(enum PinMode mode, uint16_t pin_, GPIO_TypeDef *port_) : pin(pin_), port(port_) {
        init(mode, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
    }
    Pin(enum PinMode mode, uint16_t pin_, GPIO_TypeDef *port_, uint8_t af) : pin(pin_), port(port_) {
        init(mode, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, af);
    }
    Pin(enum PinMode mode, uint32_t pull, uint16_t pin_, GPIO_TypeDef *port_, uint8_t af) : pin(pin_), port(port_) {
        init(mode, pull, GPIO_SPEED_FREQ_HIGH, af);
    }
    Pin(enum PinMode mode, uint32_t pull, uint16_t pin_, GPIO_TypeDef *port_, uint8_t af, uint32_t speed) : pin(pin_), port(port_) {
        init(mode, pull, speed, af);
    }

    void init(enum PinMode mode, uint32_t pull, uint32_t speed, uint8_t af) {
        init_rcc();
        GPIO_InitTypeDef g;
        g.Mode = mode == INPUT ? GPIO_MODE_INPUT :
                 mode == OUTPUT ? GPIO_MODE_OUTPUT_PP :
                 mode == ANALOG ? GPIO_MODE_ANALOG :
                 mode == ALT ? GPIO_MODE_AF_PP 
                         : GPIO_MODE_OUTPUT_PP;
        g.Alternate = af;
        g.Pull = pull;
        g.Speed = speed;
        g.Pin = pin;
        // LL_GPIO_SetPinMode(port, pin, mode);
        // LL_GPIO_SetPinAF
        HAL_GPIO_Init(port, &g);
    }
    void reinit(enum PinMode mode, uint32_t pull) {
        init(mode, pull, GPIO_SPEED_FREQ_HIGH);
    }
    void reinit(enum PinMode mode) {
        init(mode, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
    }

    void high() {port->BSRR = pin;}
    void low() {port->BSRR = (uint32_t)pin << 16;}
    void on() {if (polarity==INVERTED) low(); else high();}
    void off() {if (polarity==INVERTED) high(); else low();}
    void set(uint32_t v) {if (v) on(); else off();}

    bool read_raw() {return ((port->IDR) & pin) ? true : false;}
    uint8_t is_on() {return (polarity==INVERTED) ? !read_raw() : read_raw();}

private:
    void init_rcc() {
        #ifdef GPIOA
        if (port==GPIOA && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)) __HAL_RCC_GPIOA_CLK_ENABLE();
        #endif
        #ifdef GPIOB
        if (port==GPIOB && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)) __HAL_RCC_GPIOB_CLK_ENABLE();
        #endif
        #ifdef GPIOC
        if (port==GPIOC && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)) __HAL_RCC_GPIOC_CLK_ENABLE();
        #endif
        #ifdef GPIOD
        if (port==GPIOD && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)) __HAL_RCC_GPIOD_CLK_ENABLE();
        #endif
        #ifdef GPIOE
        if (port==GPIOE && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)) __HAL_RCC_GPIOE_CLK_ENABLE();
        #endif
        #ifdef GPIOF
        if (port==GPIOF && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)) __HAL_RCC_GPIOF_CLK_ENABLE();
        #endif
        #ifdef GPIOG
        if (port==GPIOG && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)) __HAL_RCC_GPIOG_CLK_ENABLE();
        #endif
        #ifdef GPIOH
        if (port==GPIOH && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)) __HAL_RCC_GPIOH_CLK_ENABLE();
        #endif
        #ifdef GPIOI
        if (port==GPIOI && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)) __HAL_RCC_GPIOI_CLK_ENABLE();
        #endif
        #ifdef GPIOJ
        if (port==GPIOJ && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN)) __HAL_RCC_GPIOJ_CLK_ENABLE();
        #endif
        #ifdef GPIOK
        if (port==GPIOK && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN)) __HAL_RCC_GPIOK_CLK_ENABLE();
        #endif
    }

};
