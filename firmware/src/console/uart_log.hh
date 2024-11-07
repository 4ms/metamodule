#pragma once
#include "concurrent_buffer.hh"
#include "conf/console_uart_conf.hh"
#include "drivers/lazy_uart.hh"
#include "drivers/uart_conf.hh"

namespace MetaModule
{

struct UartLog {
	static inline mdrivlib::LazyUart<LogUartConfig> log_uart;

	static constexpr size_t NumCores = 2;
	static inline std::array<ConcurrentBuffer *, NumCores> log_usb = {nullptr, nullptr};

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);

	static void write_uart(char *ptr, size_t len);
	static void write_usb(char *ptr, size_t len);

	enum class Port { Uart, USB };

	static Port port;
	static void use_usb(ConcurrentBuffer *usb_buffer);
	static void use_uart();
};
} // namespace MetaModule
