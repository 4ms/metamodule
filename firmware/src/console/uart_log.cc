#include "uart_log.hh"

namespace MetaModule
{
void UartLog::init() {
	log_uart.init();
}

void UartLog::putchar(char c) {
	log_uart.putchar(c);
}

void UartLog::log(const char *format, ...) {
	va_list va;
	va_start(va, format);
	vprintf_(format, va);
	va_end(va);
}

extern "C" void _putchar(char c) {
	UartLog::putchar(c);
}
} // namespace MetaModule
