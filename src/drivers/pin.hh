#pragma once
#include <stm32f7xx.h>

enum PinPolarity {NORMAL, INVERTED};
enum PinMode {INPUT, OUTPUT, ANALOG, ALT};
enum PinPull {UP, DOWN, NONE};
enum PinSpeed {LOW, MEDIUM, HIGH, VERY_HIGH};

//todo: don't use HAL 
//todo? templatize with Pin and Port. template for INPUT/OUTPUT/ALT ?
//todo: Can the enums be in the class or namespace, so we use Pin::Pull::Up or Pin::PULLUP ?
template<PinPolarity polarity=NORMAL>
class Pin {
    
private: 
    uint16_t pin_;
    GPIO_TypeDef *port_;
    enum PinMode mode_;
    enum PinPull pull_;
    enum PinSpeed speed_;
    uint8_t af_;

public :
    Pin() {}
    Pin(uint16_t pin, GPIO_TypeDef *port, enum PinMode mode, enum PinPull pull = NONE, enum PinSpeed speed = MEDIUM, uint8_t af = 0) 
    : pin_(pin), port_(port), mode_(mode), pull_(pull), speed_(speed), af_(af)
    {
        init_rcc();
        GPIO_InitTypeDef g;
        g.Mode = mode_ == INPUT ? GPIO_MODE_INPUT :
                 mode_ == OUTPUT ? GPIO_MODE_OUTPUT_PP :
                 mode_ == ANALOG ? GPIO_MODE_ANALOG :
                 mode_ == ALT ? GPIO_MODE_AF_PP 
                            : GPIO_MODE_OUTPUT_PP;
        g.Alternate = af;
        g.Pull = pull_ == UP ? GPIO_PULLUP :
                 pull_ == DOWN ? GPIO_PULLDOWN
                              : GPIO_NOPULL;
        g.Speed = speed_ == LOW ? GPIO_SPEED_FREQ_LOW :
                  speed_ == MEDIUM ? GPIO_SPEED_FREQ_MEDIUM :
                  speed_ == HIGH ? GPIO_SPEED_FREQ_HIGH :
                  speed_ == VERY_HIGH ? GPIO_SPEED_FREQ_VERY_HIGH 
                                    : GPIO_SPEED_FREQ_MEDIUM;
        g.Pin = pin_;
        HAL_GPIO_Init(port_, &g);    
        // LL_GPIO_SetPinPinMode(port, pin, mode);
        // LL_GPIO_SetPinAF
    }

public:
    void high() {port_->BSRR = pin_;}
    void low() {port_->BSRR = (uint32_t)pin_ << 16;}
    void on() {if (polarity==INVERTED) low(); else high();}
    void off() {if (polarity==INVERTED) high(); else low();}
    void set(uint32_t v) {if (v) on(); else off();}

    bool read_raw() {return ((port_->IDR) & pin_) ? true : false;}
    uint8_t is_on() {return (polarity==INVERTED) ? !read_raw() : read_raw();}

private:
    void init_rcc() {
        #ifdef GPIOA
        if (port_==GPIOA && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)) __HAL_RCC_GPIOA_CLK_ENABLE();
        #endif
        #ifdef GPIOB
        if (port_==GPIOB && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)) __HAL_RCC_GPIOB_CLK_ENABLE();
        #endif
        #ifdef GPIOC
        if (port_==GPIOC && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)) __HAL_RCC_GPIOC_CLK_ENABLE();
        #endif
        #ifdef GPIOD
        if (port_==GPIOD && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)) __HAL_RCC_GPIOD_CLK_ENABLE();
        #endif
        #ifdef GPIOE
        if (port_==GPIOE && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)) __HAL_RCC_GPIOE_CLK_ENABLE();
        #endif
        #ifdef GPIOF
        if (port_==GPIOF && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)) __HAL_RCC_GPIOF_CLK_ENABLE();
        #endif
        #ifdef GPIOG
        if (port_==GPIOG && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)) __HAL_RCC_GPIOG_CLK_ENABLE();
        #endif
        #ifdef GPIOH
        if (port_==GPIOH && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)) __HAL_RCC_GPIOH_CLK_ENABLE();
        #endif
        #ifdef GPIOI
        if (port_==GPIOI && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)) __HAL_RCC_GPIOI_CLK_ENABLE();
        #endif
        #ifdef GPIOJ
        if (port_==GPIOJ && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN)) __HAL_RCC_GPIOJ_CLK_ENABLE();
        #endif
        #ifdef GPIOK
        if (port_==GPIOK && !READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN)) __HAL_RCC_GPIOK_CLK_ENABLE();
        #endif
    }

};
