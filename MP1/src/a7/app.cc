#include "drivers/pin.hh"
#include "drivers/stm32xx.h"

#include <stdint.h>

const uint32_t *UART4_ISR = (uint32_t *)0x40010028;
const uint32_t TXFE = (1 << 23); // FIFO Empty
const uint32_t TXFNF = (1 << 7); // TX FIFO Not Full
const uint32_t TC = (1 << 6);	 // Tx Complete

void delay_long()
{
	uint32_t i = 0x100000;
	while (i--)
		;
}

void soft_breakpoint()
{
	volatile int stop = 1;
	while (stop) {
		// Attach a debugger and manually change the value at the address of `stop` in RAM from 1 to 0
	}
}

void delay_for_uart(void)
{
	int i = 255;
	while (i--)
		;
}

uint32_t uart_ready()
{
	uint32_t isr = (*UART4_ISR);
	if (isr & TC)
		return 1;
	else
		return 0;
}

void write(const char *str)
{
	while (*str) {
		UART4->TDR = *str++;
		delay_for_uart();
	}
}

int main()
{
	// Test UART
	UART4->TDR = 'X';
	delay_for_uart();
	UART4->TDR = 'Y';
	delay_for_uart();
	UART4->TDR = 'Z';
	delay_for_uart();
	UART4->TDR = 'z';
	delay_for_uart();
	UART4->TDR = 'z';
	delay_for_uart();
	UART4->TDR = '\r';
	delay_for_uart();
	UART4->TDR = '\n';
	delay_for_uart();

	Pin red_LED2{GPIO::I, 8, PinMode::Output};
	Pin green_LED2{GPIO::I, 9, PinMode::Output};
	Pin red_LED1{GPIO::Z, 6, PinMode::Output};
	Pin green_LED1{GPIO::Z, 7, PinMode::Output};

	green_LED1.high();
	green_LED1.low();

	green_LED2.high();
	green_LED2.low();

	red_LED1.high();
	red_LED1.low();

	red_LED2.high();
	red_LED2.low();

	// RCC->MC_AHB4ENSETR |= RCC_MC_AHB4ENSETR_GPIOIEN;
	// RCC->MC_AHB5ENSETR |= RCC_MC_AHB5ENSETR_GPIOZEN;

	// LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
	// LL_GPIO_SetPinOutputType(GPIOI, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
	// LL_GPIO_SetPinSpeed(GPIOI, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_MEDIUM);
	// LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
	// LL_GPIO_SetPinOutputType(GPIOI, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
	// LL_GPIO_SetPinSpeed(GPIOI, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_MEDIUM);

	// LL_GPIO_SetOutputPin(GPIOI, LL_GPIO_PIN_8);
	// LL_GPIO_ResetOutputPin(GPIOI, LL_GPIO_PIN_8);

	// LL_GPIO_SetOutputPin(GPIOI, LL_GPIO_PIN_9);
	// LL_GPIO_ResetOutputPin(GPIOI, LL_GPIO_PIN_9);

	// LL_GPIO_SetOutputPin(GPIOZ, LL_GPIO_PIN_6);
	// LL_GPIO_ResetOutputPin(GPIOZ, LL_GPIO_PIN_6);

	// LL_GPIO_SetOutputPin(GPIOZ, LL_GPIO_PIN_7);
	// LL_GPIO_ResetOutputPin(GPIOZ, LL_GPIO_PIN_7);

	// Test function calls (tests the stack)
	const char *s = "Hello world from bare-metal!\r\n";
	write(s);

	const char *s2 = "And hi to you too!\r\n";
	while (*s2 != '\0') {
		UART4->TDR = *s2;
		s2++;
		delay_for_uart();
	}

	while (1) {
		// LL_GPIO_SetOutputPin(GPIOI, LL_GPIO_PIN_8);
		red_LED1.low();
		delay_long();
		red_LED1.high();
		// LL_GPIO_ResetOutputPin(GPIOI, LL_GPIO_PIN_8);

		// LL_GPIO_SetOutputPin(GPIOI, LL_GPIO_PIN_9);
		red_LED2.low();
		delay_long();
		red_LED2.high();
		// LL_GPIO_ResetOutputPin(GPIOI, LL_GPIO_PIN_9);

		// LL_GPIO_SetOutputPin(GPIOZ, LL_GPIO_PIN_6);
		green_LED1.low();
		delay_long();
		green_LED1.high();
		// LL_GPIO_ResetOutputPin(GPIOZ, LL_GPIO_PIN_6);

		// LL_GPIO_SetOutputPin(GPIOZ, LL_GPIO_PIN_7);
		green_LED2.low();
		delay_long();
		green_LED2.high();
		// LL_GPIO_ResetOutputPin(GPIOZ, LL_GPIO_PIN_7);
	};

	return 0;
}

void SystemInit(void)
{
	return;
}
