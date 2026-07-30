#pragma once
#include "conf/hsem_conf.hh"
#include "console/console_buffer_reader.hh"
#include "console/console_routing.hh"
#include "console/uart_log.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{

// Write the console buffers to the UART, as needed. Runs on the M4 in the main
// context.
//
// Typing 'c' into the console enables per-core colored output; 'm' disables it
//
// Future UART-DMA upgrade: everything up to the FIFO top-up is TX-agnostic.
// When idle, start a DMA transfer of bounce[tx_pos..tx_len) instead of writing
// TDR here, and poll DMA completion (or use its interrupt) instead of checking
// TXE_TXFNF. (DMA1/2 stream + DMAMUX request for UART7_TX, mem-to-periph,
// byte-wise; the bounce buffer is already DMA-friendly M4-local RAM.)
class UartConsoleDrain {
public:
	UartConsoleDrain(std::array<ConcurrentBuffer *, ConsoleBufferReader::NumBuffers> buffers)
		: reader{buffers} {
		UartLog::init();
	}

	void set_color(bool enabled) {
		reader.set_color(enabled);
	}

	void process() {
		if (ConsoleRouting::usb_console_active) {
			usb_was_active = true;
			return;
		}
		if (usb_was_active) {
			usb_was_active = false;
			// The USB console already displayed everything up to this point
			reader.resync();
		}

		auto uart = UartLog::uart_regs();

		poll_rx(uart);

		while (true) {
			if (tx_pos >= tx_len) {
				tx_pos = 0;
				tx_len = reader.next_chunk(bounce);
				if (tx_len == 0)
					return;
			}

			// Don't interleave with a core doing direct (unbuffered) UART writes.
			// Those only happen during early boot, so contention is rare: just
			// try again on the next process() call.
			if (mdrivlib::HWSemaphore<UartLock>::lock(M4LockId) != mdrivlib::HWSemaphoreFlag::LockedOk)
				return;

			while (tx_pos < tx_len && (uart->ISR & USART_ISR_TXE_TXFNF))
				uart->TDR = bounce[tx_pos++];

			mdrivlib::HWSemaphore<UartLock>::unlock(M4LockId);

			if (tx_pos < tx_len)
				return; // TX FIFO full: continue on the next call
		}
	}

private:
	void poll_rx(USART_TypeDef *uart) {
		if (uart->ISR & USART_ISR_ORE)
			uart->ICR = USART_ICR_ORECF;

		while (uart->ISR & USART_ISR_RXNE_RXFNE) {
			char c = uart->RDR;
			if (c == 'c')
				reader.set_color(true);
			else if (c == 'm')
				reader.set_color(false);
		}
	}

	static constexpr uint32_t M4LockId = 2; // same process id UartLog's direct writes use on the M4

	ConsoleBufferReader reader;
	std::array<uint8_t, 256> bounce;
	size_t tx_pos = 0;
	size_t tx_len = 0;
	bool usb_was_active = false;
};

} // namespace MetaModule
