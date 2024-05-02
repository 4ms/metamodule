#pragma once
#include "conf/console_uart_conf.hh"
#include "drivers/lazy_uart.hh"
#include "drivers/uart_conf.hh"

namespace MetaModule
{

struct UartLog {
	static inline mdrivlib::LazyUart<LogUartConfig> log_uart;

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);
};
} // namespace MetaModule
