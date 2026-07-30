#pragma once
#include "concurrent_buffer.hh"
#include "conf/console_uart_conf.hh"
#include "drivers/lazy_uart.hh"
#include "drivers/uart_conf.hh"

namespace MetaModule
{

// Console log output for all cores.
//
// Each core starts in Direct mode: printf() writes synchronously to the UART
// (blocking and shared via a hardware semaphore).
// During startup each core switches itself to Buffered mode (use_buffer()),
// printf() then just writes into the core's ConcurrentBuffer and the M4 core
// asynchronously drains all buffers to the UART, or to USB CDC if a console
// host is connected.
struct UartLog {
private:
	static inline mdrivlib::LazyUart<LogUartConfig> log_uart;

public:
	enum class Mode { Direct, Buffered };

	// There are two separate static instances of these: one in the M4's memory and
	// one in the A7's (this file is compiled+linked once for each image). The A7
	// instance has two cores; the M4 instance just uses index 0.
	static constexpr size_t NumCores = 2;

	static inline std::array<ConcurrentBuffer *, NumCores> log_buff = {nullptr, nullptr};
	static inline std::array<Mode, NumCores> mode{Mode::Direct, Mode::Direct};

	UartLog() {
		init();
	}

	static void init();

	// Raw register access for the non-blocking drain (M4)
	static USART_TypeDef *uart_regs();

	static void putchar(char c);

	static void log(const char *format, ...);

	static void puts(const char *ptr);

	static void write_uart(const char *ptr, size_t len);
	static void write_buffered(const char *ptr, size_t len);
	static void write_stdout(const char *ptr, size_t len);

	// Switch the calling core's printf() to buffered (asynchronous) mode
	static void use_buffer(ConcurrentBuffer *buffer);

	// Back to synchronous blocking UART writes (early-boot default)
	static void use_direct();
};
} // namespace MetaModule
