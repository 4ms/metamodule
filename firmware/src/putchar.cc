#include "drivers/stm32xx.h"

extern "C" void _putchar(char character) {
	UART4->TDR = character;
	while ((UART4->ISR & USART_ISR_TXFT) == 0)
		;
}
