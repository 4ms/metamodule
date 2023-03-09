#pragma once
#include "drivers/uart.hh"
#include "printf.h"

namespace MetaModule
{
struct UartLog {
	static inline mdrivlib::Uart<USART6_BASE> log_uart;

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);
};
} // namespace MetaModule
