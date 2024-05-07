#pragma once
#include "stm32xx.h"

enum class Firmware { Bootloader, App };

void enable_gpio_rcc(GPIO_TypeDef *port);
void Error_Handler();
void system_init();
void reset_buses();
void reset_RCC();
