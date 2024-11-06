#include "uart_log.hh"
#include <cstdarg>
#include <cstring>

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

UartLog::Port UartLog::port = UartLog::Port::Uart;

// extern "C" void _putchar(char c) {
// }

void UartLog::write_uart(char *ptr, size_t len) {
	for (auto idx = 0u; idx < len; idx++) {
		UartLog::putchar(*ptr++);
	}
}

void UartLog::write_usb(char *ptr, size_t len) {
	log_usb.writer_ref_count.fetch_add(1, std::memory_order_acquire);

	auto offset = log_usb.current_write_pos.fetch_add(len, std::memory_order_acquire);
	log_usb.buffer.write({(uint8_t *)ptr, len}, offset);

	log_usb.writer_ref_count.fetch_sub(1, std::memory_order_release);
}

extern "C" int _write(int file, char *ptr, int len) {
	if (UartLog::port == UartLog::Port::Uart) {
		UartLog::write_uart(ptr, len);

	} else if (UartLog::port == UartLog::Port::USB) {
		UartLog::write_usb(ptr, len);
	}

	return len;
}

} // namespace MetaModule
