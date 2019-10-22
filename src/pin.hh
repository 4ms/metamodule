#pragma once
#include <stm32f7xx.h>

enum PinPolarity {NORMAL, INVERTED};

template<PinPolarity polarity>
class Pin {
public:
    uint16_t pin;
    GPIO_TypeDef *port;
    uint8_t af;

    Pin() {}
    Pin(uint16_t pin_, GPIO_TypeDef *port_) : pin(pin_), port(port_) {}
    Pin(uint16_t pin_, GPIO_TypeDef *port_, uint8_t af_) : pin(pin_), port(port_), af(af_) {}

    void init(uint32_t mode, uint32_t pull, uint32_t speed) {
        init_rcc();
        GPIO_InitTypeDef g;
        g.Mode = mode;
        g.Alternate = af;
        g.Pull = pull;
        g.Speed = speed;
        g.Pin = pin;
        HAL_GPIO_Init(port, &g);
    }
    void init(uint32_t mode, uint32_t pull) {
        init_rcc();
        GPIO_InitTypeDef g;
        g.Mode = mode;
        g.Alternate = af;
        g.Pull = pull;
        g.Speed = GPIO_SPEED_FREQ_HIGH;
        g.Pin = pin;
        HAL_GPIO_Init(port, &g);
    }
    void init(uint32_t mode) {
        init_rcc();
        GPIO_InitTypeDef g;
        g.Mode = mode;
        g.Alternate = af;
        g.Pull = GPIO_NOPULL;
        g.Speed = GPIO_SPEED_FREQ_HIGH;
        g.Pin = pin;
        HAL_GPIO_Init(port, &g);
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
