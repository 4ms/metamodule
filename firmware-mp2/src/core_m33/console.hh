#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include <cstdint>

// M33 console: writes to the console UART (USART1) that the A35 has already set up.
// The M33 never reconfigures it.
// Hold a Lock while printing a line, so lines from the two cores don't interleave:
//    { M33Console::Lock lock; M33Console::print("..."); ... }

namespace MetaModule::M33Console
{

struct Lock {
	using UartSem = mdrivlib::HWSemaphore<UartLock>;
	Lock() {
		while (UartSem::lock(UartLockM4Direct) != mdrivlib::HWSemaphoreFlag::LockedOk)
			;
	}
	~Lock() {
		UartSem::unlock(UartLockM4Direct);
	}
};

inline void putchar(char c) {
	while (!(USART1->ISR & USART_ISR_TXE_TXFNF))
		;
	USART1->TDR = c;
}

inline void print(const char *s) {
	while (*s) {
		if (*s == '\n')
			putchar('\r');
		putchar(*s++);
	}
}

inline void print(uint32_t v) {
	char buf[11];
	int len = 0;
	do {
		buf[len++] = '0' + (v % 10);
		v /= 10;
	} while (v);
	while (len)
		putchar(buf[--len]);
}

inline void print_hex(uint32_t v) {
	for (int i = 28; i >= 0; i -= 4) {
		auto nibble = (v >> i) & 0xF;
		putchar(nibble < 10 ? '0' + nibble : 'A' + nibble - 10);
	}
}

} // namespace MetaModule::M33Console
