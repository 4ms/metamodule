#pragma once
#include "conf/hsem_conf.hh"
#include "console/console_buffer_reader.hh"
#include "console/console_routing.hh"
#include "console/uart_log.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include <cstdio>

namespace MetaModule
{

// TX uses DMA: process() copies into the tx buffer and starts a DMA transfer
// If the DMA ever errors out, we permanently fall back to pushing bytes into
// the UART TX FIFO directly
//
// Typing 'c' into the console enables per-core colored output; 'm' disables it
class UartConsoleDrain {
public:
	UartConsoleDrain(std::array<ConcurrentBuffer *, ConsoleBufferReader::NumBuffers> buffers)
		: reader{buffers} {
		UartLog::init();
		init_dma();
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

		if (dma_running) {
			const auto flags = DMA1->LISR;

			if (flags & DMA_LISR_TEIF1) {
				// Bus error reading the bounce buffer or writing TDR: give up dma for good
				stop_dma();
				dma_ok = false;
				unlock();
				// Deliberately not pr_err(): must be visible at any log level
				printf("<console: UART TX DMA error (LISR=0x%08x), using FIFO fallback>\n", (unsigned)flags);

			} else if (flags & (DMA_LISR_FEIF1 | DMA_LISR_DMEIF1)) {
				// Underrun: the memory bus wasn't granted before UART7 asked for its next byte.
				tx_pos = tx_len - DMA1_Stream1->NDTR;
				stop_dma();
				unlock();

			} else if (flags & DMA_LISR_TCIF1) {
				stop_dma();
				tx_pos = tx_len = 0;
				unlock();

			} else if ((HAL_GetTick() - dma_start_tm) >= DmaTimeoutMs) {
				// The stream stopped without raising any flag, unknown reasons.
				// FIXME: why does this happen?
				// Pick up from wherever it got to.
				tx_pos = tx_len - DMA1_Stream1->NDTR;
				stop_dma();
				unlock();
				printf("<console: UART TX DMA unknown error (LISR=0x%08x), using FIFO>\n", (unsigned)flags);
				dma_stalls++;

			} else {
				return; // still transferring
			}
		}

		// Fetch the next chunk if none is pending
		if (tx_pos >= tx_len) {
			tx_pos = 0;
			tx_len = reader.next_chunk(bounce);
			if (tx_len == 0)
				return;
		}

		// Lock the UART semaphore while we transmit (held until xfer completes)
		if (mdrivlib::HWSemaphore<UartLock>::lock(M4LockId) != mdrivlib::HWSemaphoreFlag::LockedOk)
			return;

		if (dma_ok) {
			start_dma(&bounce[tx_pos], tx_len - tx_pos);
		} else {
			while (tx_pos < tx_len && (uart->ISR & USART_ISR_TXE_TXFNF))
				uart->TDR = bounce[tx_pos++];
			unlock();
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

	void init_dma() {
		mdrivlib::core_m4::RCC_Enable::DMA1_::set();
		mdrivlib::core_m4::RCC_Enable::DMAMUX_::set();

		// DMAMUX1 channels 0..7 feed DMA1 streams 0..7
		DMAMUX1_Channel1->CCR = DMA_REQUEST_UART7_TX;

		DMA1_Stream1->CR = 0;
		while (DMA1_Stream1->CR & DMA_SxCR_EN)
			;
		clear_dma_flags();

		DMA1_Stream1->PAR = reinterpret_cast<uint32_t>(&UartLog::uart_regs()->TDR);
		// Byte-wise, memory-increment, memory-to-peripheral
		DMA1_Stream1->CR = DMA_SxCR_MINC | DMA_SxCR_DIR_0;

		// Enable FIFO to smooth out memory bus delays
		DMA1_Stream1->FCR = DMA_SxFCR_DMDIS | DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1;

		UartLog::uart_regs()->CR3 |= USART_CR3_DMAT;
	}

	void start_dma(const uint8_t *ptr, size_t len) {
		DMA1_Stream1->M0AR = dma_address(ptr);
		DMA1_Stream1->NDTR = len;
		clear_dma_flags();
		DMA1_Stream1->CR |= DMA_SxCR_EN;
		dma_running = true;
		dma_start_tm = HAL_GetTick();
	}

	void stop_dma() {
		DMA1_Stream1->CR &= ~DMA_SxCR_EN;
		while (DMA1_Stream1->CR & DMA_SxCR_EN)
			;
		clear_dma_flags();
		dma_running = false;
	}

	static void clear_dma_flags() {
		DMA1->LIFCR = DMA_LIFCR_CTCIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CTEIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1;
	}

	// The M4 sees 0x10000000, but DMA sees 0x30000000 (maybe? TODO: this works but is it right?)
	static uint32_t dma_address(const void *p) {
		auto addr = reinterpret_cast<uint32_t>(p);
		if (addr >= 0x1000'0000 && addr < 0x1006'0000)
			return addr + 0x2000'0000;
		return addr;
	}

	static void unlock() {
		mdrivlib::HWSemaphore<UartLock>::unlock(M4LockId);
	}

	static constexpr uint32_t M4LockId = UartLockM4Drain;

	// A full bounce buffer is ~23ms at 115200 baud
	static constexpr uint32_t DmaTimeoutMs = 250;

	ConsoleBufferReader reader;
	std::array<uint8_t, 256> bounce;
	size_t tx_pos = 0;
	size_t tx_len = 0;
	uint32_t dma_start_tm = 0;
	uint32_t dma_stalls = 0; // transfers that stopped without raising a flag
	bool usb_was_active = false;
	bool dma_running = false;
	bool dma_ok = true;
};

} // namespace MetaModule
