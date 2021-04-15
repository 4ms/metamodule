#include "drivers/pin.hh"
#include "drivers/stm32xx.h"

#include <stdint.h>

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

// uint32_t uart_ready()
// {
// 	uint32_t isr = (*UART4_ISR);
// 	if (isr & TC)
// 		return 1;
// 	else
// 		return 0;
// }

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
		red_LED1.low();
		delay_long();
		red_LED1.high();

		red_LED2.low();
		delay_long();
		red_LED2.high();

		green_LED1.low();
		delay_long();
		green_LED1.high();

		green_LED2.low();
		delay_long();
		green_LED2.high();
	}

	return 0;
}

void SystemInit(void)
{
	return;
}
