// Early debug console over USART1, providing the app-side hooks the ca35 boot
// and exception code (startup_ca35.s, vectors.S, esr_decode.cc) expect:
// putchar_s / early_puts / early_puthex64, plus a strong early_print_el that
// overrides the weak no-op in startup_ca35.s and brings up the UART before the
// first print.
#include <stdint.h>

// Console UART base addresses (APB, 0x40xx_xxxx range).
#define USART1_BASE 0x40330000UL

// Register addresses come from the CMSIS headers for STM32MP257Cxx
// Pin muxing matches the board device tree in the tf-a-stm32mp25 repo (fdts/stm32mp257f-ev1.dts).
#define USART_BASE USART1_BASE
#define UART_RCC_USARTxCFGR 0x4420077CUL // RCC->USART1CFGR
#define UART_FLEXGEN_CHAN 19u			 // ck_ker_usart1
#define UART_GPIO_BASE 0x44250000UL		 // GPIOB
#define UART_RCC_GPIOxCFGR 0x44200530UL	 // RCC->GPIOBCFGR
#define UART_TX_PIN 8u					 // PB8, USART1_TX
#define UART_TX_AF 6u
#define UART_RX_PIN 10u // PB10, USART1_RX
#define UART_RX_AF 6u

typedef struct {
	volatile uint32_t CR1;	 // 0x00
	volatile uint32_t CR2;	 // 0x04
	volatile uint32_t CR3;	 // 0x08
	volatile uint32_t BRR;	 // 0x0C
	volatile uint32_t GTPR;	 // 0x10
	volatile uint32_t RTOR;	 // 0x14
	volatile uint32_t RQR;	 // 0x18
	volatile uint32_t ISR;	 // 0x1C
	volatile uint32_t ICR;	 // 0x20
	volatile uint32_t RDR;	 // 0x24
	volatile uint32_t TDR;	 // 0x28
	volatile uint32_t PRESC; // 0x2C
} stm32_usart_t;

#define USART ((stm32_usart_t *)USART_BASE)

#define USART_CR1_UE (1u << 0)	// USART enable
#define USART_CR1_RE (1u << 2)	// Receiver enable
#define USART_CR1_TE (1u << 3)	// Transmitter enable
#define USART_ISR_TXE (1u << 7) // Transmit data register empty

// The USART kernel clock is driven from HSI (64 MHz) via its RCC flexgen
// channel, so the resulting baud rate does not depend on any PLL that TF-A may
// or may not have configured.
#define UART_KERNEL_CLK_HZ 64000000u // HSI
#define UART_BAUD 115200u
// BRR for oversampling-by-16 (default) is simply fck / baud, rounded.
#define UART_BRR ((UART_KERNEL_CLK_HZ + UART_BAUD / 2u) / UART_BAUD)

#define RCC_PERIPH_EN (1u << 1) // GPIOxEN / USARTxEN enable bit in RCC->xCFGR

// RCC flexgen register-array bases (channel N is at base + N*4).
#define RCC_XBARxCFGR_BASE 0x44201018UL
#define RCC_PREDIVxCFGR_BASE 0x44201118UL
#define RCC_FINDIVxCFGR_BASE 0x44201224UL
#define RCC_FINDIVSR1 0x44201324UL
#define XBAR_EN (1u << 6)
#define XBAR_STS (1u << 7) // 1 = source switch ongoing
#define FINDIV_EN (1u << 6)
#define XBAR_SRC_HSI 5u

static inline volatile uint32_t *reg32(uint64_t addr) {
	return (volatile uint32_t *)(uintptr_t)addr;
}

// Route a flexgen channel to HSI with /1 pre- and final-dividers, so the
// channel outputs 64 MHz. Waits are bounded so a stuck status bit can never
// hang the boot.
static void flexgen_to_hsi(unsigned chan) {
	volatile uint32_t *xbar = reg32(RCC_XBARxCFGR_BASE + chan * 4u);
	volatile uint32_t *prediv = reg32(RCC_PREDIVxCFGR_BASE + chan * 4u);
	volatile uint32_t *findiv = reg32(RCC_FINDIVxCFGR_BASE + chan * 4u);
	volatile uint32_t *findivsr1 = reg32(RCC_FINDIVSR1);
	unsigned timeout;

	*prediv = 0; // pre-divider = /1
	*xbar = XBAR_EN | XBAR_SRC_HSI;
	for (timeout = 1000000u; (*xbar & XBAR_STS) && timeout; timeout--)
		;
	*findiv = FINDIV_EN | 0u; // final divider = /1
	for (timeout = 1000000u; (*findivsr1 & (1u << chan)) && timeout; timeout--)
		;
}

// Put one GPIO pin into alternate-function mode with the given AF number,
// push-pull, high speed, no pull (matching the board device tree).
static void gpio_config_af(uint64_t gpio_base, unsigned pin, unsigned af) {
	volatile uint32_t *moder = reg32(gpio_base + 0x00);
	volatile uint32_t *otyper = reg32(gpio_base + 0x04);
	volatile uint32_t *ospeedr = reg32(gpio_base + 0x08);
	volatile uint32_t *pupdr = reg32(gpio_base + 0x0C);
	volatile uint32_t *afr = reg32(gpio_base + 0x20); // AFR[0]=0x20, AFR[1]=0x24
	unsigned s2 = pin * 2u;
	unsigned s4 = (pin & 7u) * 4u;

	*moder = (*moder & ~(3u << s2)) | (2u << s2);	  // alternate-function mode
	*otyper &= ~(1u << pin);						  // push-pull
	*ospeedr = (*ospeedr & ~(3u << s2)) | (2u << s2); // high speed
	*pupdr &= ~(3u << s2);							  // no pull
	afr[pin >> 3] = (afr[pin >> 3] & ~(0xFu << s4)) | ((af & 0xFu) << s4);
}

// Bring up the selected console UART: kernel clock, pin mux, peripheral clock,
// baud rate, TX/RX enable. This is done unconditionally for whichever UART was
// selected (USART2 is the ST-LINK console default) so the console works
// regardless of which UART, if any, TF-A was built to initialize. Safe to call
// more than once.
void init_uart(void) {
	// 1. Kernel (baud) clock from HSI.
	flexgen_to_hsi(UART_FLEXGEN_CHAN);

	// 2. Enable the GPIO port and mux the TX/RX pins.
	*reg32(UART_RCC_GPIOxCFGR) |= RCC_PERIPH_EN;
	gpio_config_af(UART_GPIO_BASE, UART_TX_PIN, UART_TX_AF);
	gpio_config_af(UART_GPIO_BASE, UART_RX_PIN, UART_RX_AF);

	// 3. Enable the USART peripheral bus clock (needed for register access).
	*reg32(UART_RCC_USARTxCFGR) |= RCC_PERIPH_EN;

	// 4. Configure for 115200 8N1 and enable transmitter + receiver.
	USART->CR1 = 0; // disable before configuring
	USART->CR2 = 0; // 1 stop bit
	USART->CR3 = 0; // no hardware flow control
	USART->PRESC = 0;
	USART->BRR = UART_BRR;
	USART->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void putchar_s(char c) {
	// Wait until the transmit data register is empty, but bound the wait so a
	// mis-configured UART can never hang the boot.
	unsigned timeout = 1000000u;
	while (!(USART->ISR & USART_ISR_TXE) && --timeout)
		;

	USART->TDR = (uint32_t)c;
}

void early_puts(const char *s) {
	while (*s) {
		if (*s == '\n')
			putchar_s('\r');
		putchar_s(*s++);
	}
}

void early_puthex64(uint64_t v) {
	static const char hex[] = "0123456789abcdef";
	int found_nonzero = 0;
	for (int i = 60; i >= 0; i -= 4) {
		char c = hex[(v >> i) & 0xF];
		if (c > '0' || found_nonzero) {
			putchar_s(c);
			found_nonzero = 1;
		}
	}
}

void early_print_el(void) {
	// early_print_el() is the first thing every startup.s calls, so use it to
	// bring up the console UART before anything is printed.
	init_uart();

	uint64_t el;
	asm("mrs %0, CurrentEL" : "=r"(el));
	early_puts("EL");
	putchar_s(((el >> 2) & 3) + '0');
	early_puts("\n");
}
