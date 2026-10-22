#pragma once
#include "conf/hsem_conf.hh"
#include "console/console_buffer_reader.hh"
#include "console/console_routing.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include <array>

namespace MetaModule
{

// Sends all cores' console buffers to the console UART (USART1, which the A35 set up), unless the
// USB console is sending them (see console_routing.hh). MP1's UartConsoleDrain, without DMA: the
// main loop tops up the UART's FIFO. Adds a \r before each \n, as direct writes do.
// (The A35 reads the UART's RX: see core_a35/console_keys.hh)
class ConsoleDrain {
public:
	ConsoleDrain(std::array<ConcurrentBuffer *, ConsoleBufferReader::NumBuffers> buffers)
		: reader{buffers} {
	}

	void process() {
		if (ConsoleRouting::usb_console_active) {
			usb_was_active = true;
			return;
		}
		if (usb_was_active) {
			usb_was_active = false;
			// The USB console already sent everything up to here
			reader.resync();
			pos = len = 0;
		}

		if (pos >= len) {
			pos = 0;
			len = reader.next_chunk(chunk);
			if (len == 0)
				return;
		}

		// Cores still writing to the UART directly (early startup) hold this too
		using UartSem = mdrivlib::HWSemaphore<UartLock>;
		if (UartSem::lock(UartLockM4Drain) != mdrivlib::HWSemaphoreFlag::LockedOk)
			return;

		while (pos < len && (USART1->ISR & USART_ISR_TXE_TXFNF)) {
			auto c = chunk[pos];
			if (c == '\n' && !sent_cr) {
				USART1->TDR = '\r';
				sent_cr = true;
				continue;
			}
			sent_cr = false;
			USART1->TDR = c;
			pos++;
		}

		UartSem::unlock(UartLockM4Drain);
	}

private:
	ConsoleBufferReader reader;
	std::array<uint8_t, 256> chunk;
	size_t pos = 0;
	size_t len = 0;
	bool sent_cr = false;
	bool usb_was_active = false;
};

} // namespace MetaModule
