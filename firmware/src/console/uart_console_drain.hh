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

// Write the console buffers to the UART, as needed. Runs on the M4 in the main
// context.
//
// TX uses DMA: process() assembles a chunk into the bounce buffer and starts a
// DMA transfer.
// If the DMA reports a transfer error, we permanently fall back feeding UART->TDR
// fifo directly.
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
			if (DMA1->LISR & DMA_LISR_TEIF1) {
				// Bus error reading the bounce buffer or writing TDR: give up
				// on DMA for good, drain via the TX FIFO from now on
				auto flags = DMA1->LISR;
				clear_dma_flags();
				dma_running = false;
				dma_ok = false;
				unlock();
				// Report through the same UART we drain, using printf so it's always visible
				printf("<console: UART TX DMA error (LISR=0x%08x), using FIFO fallback>\n", (unsigned)flags);
			} else if (DMA1->LISR & DMA_LISR_TCIF1) {
				clear_dma_flags();
				dma_running = false;
				dma_stalls = 0;
				tx_pos = tx_len = 0;
				unlock();
			} else if (dma_stalled()) {
				// FEIF with no progress: try to recover, give up if it
				// keeps happening
				abort_dma();
				dma_running = false;
				unlock();
				if (++dma_stalls >= MaxDmaStalls) {
					dma_ok = false;
					printf("<console: UART TX DMA stalled %u times, using FIFO fallback>\n", (unsigned)dma_stalls);
				}
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

		// Exclude cores doing direct UART writes while we transmit.
		// Those only happen during early boot
		if (mdrivlib::HWSemaphore<UartLock>::lock(M4LockId) != mdrivlib::HWSemaphoreFlag::LockedOk)
			return;

		if (dma_ok) {
			start_dma(&bounce[tx_pos], tx_len - tx_pos);
			// hold the lock until the transfer completes
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
		// Byte-wise, memory-increment, memory-to-peripheral, direct mode.
		// Bit 20 (TRBUFF, reserved in RM0436 but implemented): alternate
		// REQ/ACK protocol, required on UART streams or else the stream can
		// lock up when another stream transfers concurrently (MP15 errata
		// "DMA stream locked when transferring data to/from USART/UART")
		constexpr uint32_t DMA_SxCR_TRBUFF = 1u << 20;
		DMA1_Stream1->CR = DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_TRBUFF;
		DMA1_Stream1->FCR = 0;

		UartLog::uart_regs()->CR3 |= USART_CR3_DMAT;
	}

	void start_dma(const uint8_t *ptr, size_t len) {
		DMA1_Stream1->M0AR = dma_address(ptr);
		DMA1_Stream1->NDTR = len;
		clear_dma_flags();
		last_ndtr = len;
		last_progress_tm = HAL_GetTick();
		DMA1_Stream1->CR |= DMA_SxCR_EN;
		dma_running = true;
	}

	bool dma_stalled() {
		if (!(DMA1->LISR & DMA_LISR_FEIF1))
			return false;
		auto ndtr = DMA1_Stream1->NDTR;
		auto now = HAL_GetTick();
		if (ndtr != last_ndtr) {
			last_ndtr = ndtr;
			last_progress_tm = now;
			return false;
		}
		return (now - last_progress_tm) > StallTimeoutMs;
	}

	// Stop the stream and adjust tx_pos so the next transfer resumes where
	// this one stopped. The byte preloaded into the DMA FIFO (direct mode) is
	// counted by NDTR as sent but may be discarded, so up to one character of
	// output can be lost
	void abort_dma() {
		DMA1_Stream1->CR &= ~DMA_SxCR_EN;
		while (DMA1_Stream1->CR & DMA_SxCR_EN)
			;
		tx_pos = tx_len - DMA1_Stream1->NDTR;
		clear_dma_flags();
	}

	static void clear_dma_flags() {
		DMA1->LIFCR = DMA_LIFCR_CTCIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CTEIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1;
	}

	// The M4 sees MCU SRAM (code/stack, where this object lives) at the
	// 0x10000000 alias, but the other bus masters -- including DMA1 -- address
	// the same RAM at 0x30000000. Translate for the DMA.
	static uint32_t dma_address(const void *p) {
		auto addr = reinterpret_cast<uint32_t>(p);
		if (addr >= 0x1000'0000 && addr < 0x1006'0000)
			return addr + 0x2000'0000;
		return addr;
	}

	static void unlock() {
		mdrivlib::HWSemaphore<UartLock>::unlock(M4LockId);
	}

	static constexpr uint32_t M4LockId = 2; // same process id UartLog's direct writes use on the M4

	// A 256-byte chunk takes ~22ms at 115200 baud, set the stall timeout to ~4x that
	static constexpr uint32_t StallTimeoutMs = 100;
	static constexpr uint32_t MaxDmaStalls = 8; // consecutive, reset by any completed transfer

	ConsoleBufferReader reader;
	std::array<uint8_t, 256> bounce;
	size_t tx_pos = 0;
	size_t tx_len = 0;
	uint32_t last_ndtr = 0;
	uint32_t last_progress_tm = 0;
	uint32_t dma_stalls = 0;
	bool usb_was_active = false;
	bool dma_running = false;
	bool dma_ok = true;
};

} // namespace MetaModule
