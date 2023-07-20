#pragma once
#include "conf/console_uart_conf.hh"
#include "drivers/uart.hh"
#include "drivers/uart_conf.hh"
#include "printf.h"

namespace MetaModule
{

struct UartLog {
	static inline mdrivlib::Uart<UartConfig> log_uart;

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);
};
} // namespace MetaModule
