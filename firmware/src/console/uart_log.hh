#pragma once
#include "concurrent_buffer.hh"
#include "conf/console_uart_conf.hh"
#include "drivers/lazy_uart.hh"
#include "drivers/uart_conf.hh"

namespace MetaModule
{

struct UartLog {
	static inline mdrivlib::LazyUart<LogUartConfig> log_uart;

	enum class Port { Uart, USB, File };

	static constexpr size_t NumCores = 2;

	static inline std::array<ConcurrentBuffer *, NumCores> log_usb = {nullptr, nullptr};
	static inline std::array<Port, NumCores> port{Port::Uart, Port::Uart};

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);

	static void puts(const char *ptr);

	static void write_uart(const char *ptr, size_t len);
	static void write_usb(const char *ptr, size_t len);
	static void write_stdout(const char *ptr, size_t len);

	static void use_usb(ConcurrentBuffer *usb_buffer);
	static void use_uart();
};
} // namespace MetaModule
