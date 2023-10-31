#include "uart_log.hh"
#include <cstdarg>

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
	vprintf(format, va);
	va_end(va);
}

extern "C" void _putchar(char c) {
}

extern "C" int _write(int file, char *ptr, int len) {
	// TODO: make this more efficient using UART DMA
	for (auto idx = 0; idx < len; idx++) {
		UartLog::putchar(*ptr++);
	}

	return len;
}

} // namespace MetaModule
