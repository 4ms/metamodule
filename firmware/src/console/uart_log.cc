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

static uint32_t get_core_id() {
	uint32_t current_core = 0;

#ifdef CORE_CA7
	current_core = std::min<uint32_t>(__get_MPIDR() & 0xFF, UartLog::NumCores - 1);
#endif

	return current_core;
}

void UartLog::use_usb(ConcurrentBuffer *usb_buffer) {
	log_usb[get_core_id()] = usb_buffer;
	port = UartLog::Port::USB;
}

void UartLog::use_uart() {
	port = UartLog::Port::Uart;
}

// extern "C" void _putchar(char c) {
// }

void UartLog::write_uart(char *ptr, size_t len) {
	for (auto idx = 0u; idx < len; idx++) {
		UartLog::putchar(*ptr++);
	}
}

void UartLog::write_usb(char *ptr, size_t len) {
	auto core = get_core_id();

	//TODO: make this interrupt-safe
	log_usb[core]->writer_ref_count++;

	auto offset = log_usb[core]->current_write_pos;
	log_usb[core]->current_write_pos += len;
	log_usb[core]->buffer.write({(uint8_t *)ptr, len}, offset);

	log_usb[core]->writer_ref_count--;
}

extern "C" int _write(int file, char *ptr, int len) {
	if (UartLog::port == UartLog::Port::Uart) {
		UartLog::write_uart(ptr, len);

	} else if (UartLog::port == UartLog::Port::USB) {
		if (UartLog::log_usb[get_core_id()])
			UartLog::write_usb(ptr, len);
	}

	return len;
}

} // namespace MetaModule
