#include "BufferedUSART2.h"

#include "conf/wifi_uart_conf.hh"
#include "drivers/interrupt.hh"
#include "drivers/uart.hh"
#include "drivers/uart_conf.hh"

#include <stm32mp1xx.h>
#include <stm32mp1xx_ll_usart.h>

#include <console/pr_dbg.hh>

static mdrivlib::Uart<WifiUartConfig> commMain;
LockFreeFifoSpsc<uint8_t, 32 * 1024> BufferedUSART2::queue;
std::atomic_bool BufferedUSART2::overrunDetected;

#define USART_PERIPH UART5
#define USART_IRQ UART5_IRQn
#define USART_IRQ_PRIO 2

void BufferedUSART2::init() {
	initPeripheral();
}

void BufferedUSART2::deinit() {
	LL_USART_DisableIT_RXFT(USART_PERIPH);
	LL_USART_DisableIT_IDLE(USART_PERIPH);
}

bool BufferedUSART2::setBaudrate(uint32_t baudRate) {
	return commMain.set_baudrate(baudRate);
}

void BufferedUSART2::initPeripheral() {
	commMain.init();

	// CR3.RXFTCFG can only be programmed when UE=0.
	LL_USART_Disable(USART_PERIPH);
	LL_USART_SetRXFIFOThreshold(USART_PERIPH, LL_USART_FIFOTHRESHOLD_1_2);
	LL_USART_Enable(USART_PERIPH);

	mdrivlib::Interrupt::register_and_start_isr(USART_IRQ, USART_IRQ_PRIO, 0, []() {
		// Clear ORE first in case new data comes in during the IRQ handler.
		if (LL_USART_IsActiveFlag_ORE(USART_PERIPH)) {
			LL_USART_ClearFlag_ORE(USART_PERIPH);
			overrunDetected = true;
		}
		// Not necessary to clear these, but makes debugging ISR register easier:
		LL_USART_ClearFlag_FE(USART_PERIPH);
		LL_USART_ClearFlag_NE(USART_PERIPH);
		LL_USART_ClearFlag_PE(USART_PERIPH);
		LL_USART_ClearFlag_IDLE(USART_PERIPH);

		// Drain the FIFO unconditionally
		while (LL_USART_IsActiveFlag_RXNE_RXFNE(USART_PERIPH)) {
			auto val = USART_PERIPH->RDR;
			if (!queue.put(val)) {
				queue.reset();
				overrunDetected = true;
				break;
			}
		}
	});

	// read RX from hardware to clear RXNE flag
	[[maybe_unused]] auto _ = USART_PERIPH->RDR;

	// Trigger IRQ on FIFO-threshold (1/2 = 4 bytes), plus IDLE to flush the
	// last 1-3 bytes of a burst. RXNE/RXFNE stays off so we aren't IRQ'd per byte.
	LL_USART_EnableIT_RXFT(USART_PERIPH);
	LL_USART_EnableIT_IDLE(USART_PERIPH);

	LL_USART_DisableIT_CM(USART_PERIPH);
	LL_USART_DisableIT_CTS(USART_PERIPH);
	LL_USART_DisableIT_EOB(USART_PERIPH);
	LL_USART_DisableIT_ERROR(USART_PERIPH);
	LL_USART_DisableIT_LBD(USART_PERIPH);
	LL_USART_DisableIT_PE(USART_PERIPH);
	LL_USART_DisableIT_RTO(USART_PERIPH);
	LL_USART_DisableIT_RXFF(USART_PERIPH);
	LL_USART_DisableIT_RXNE_RXFNE(USART_PERIPH);
	LL_USART_DisableIT_TC(USART_PERIPH);
	LL_USART_DisableIT_TCBGT(USART_PERIPH);
	LL_USART_DisableIT_TXE_TXFNF(USART_PERIPH);
	LL_USART_DisableIT_TXFE(USART_PERIPH);
	LL_USART_DisableIT_TXFT(USART_PERIPH);
	LL_USART_DisableIT_WKUP(USART_PERIPH);
}

void BufferedUSART2::transmit(uint8_t val) {
	commMain.transmit(val);
}

std::optional<uint8_t> BufferedUSART2::receive() {
	return queue.get();
}
