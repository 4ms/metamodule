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

namespace
{
static uint32_t core_id() {
	// There are two separate static instances of UartLog: one in M4's memory and one in A7's memory
	// (because this file is compiled+linked once for A7 and once for M4).
	// The A7 instance has two cores, while the M4 instance just uses core_id() == 0
#ifdef CORE_CA7
	return std::min<uint32_t>(__get_MPIDR() & 0xFF, UartLog::NumCores - 1);
#else
	return 0;
#endif
}
} // namespace

void UartLog::use_usb(ConcurrentBuffer *usb_buffer) {
	log_usb[core_id()] = usb_buffer;
	port[core_id()] = UartLog::Port::USB;
}

void UartLog::use_uart() {
	port[core_id()] = UartLog::Port::Uart;
}

extern "C" void _putchar(char c) {
	UartLog::putchar(c);
}

void UartLog::write_uart(char *ptr, size_t len) {
	for (auto idx = 0u; idx < len; idx++) {
		UartLog::putchar(*ptr++);
	}
}

void UartLog::write_usb(char *ptr, size_t len) {
	auto core = core_id();

	//TODO: make this interrupt-safe
	log_usb[core]->writer_ref_count++;

	auto offset = log_usb[core]->current_write_pos;
	log_usb[core]->current_write_pos += len;
	log_usb[core]->buffer.write({(uint8_t *)ptr, len}, offset);

	log_usb[core]->writer_ref_count--;
}

extern "C" int _write(int file, char *ptr, int len) {
	if (UartLog::port[core_id()] == UartLog::Port::Uart) {
		UartLog::write_uart(ptr, len);

	} else if (UartLog::port[core_id()] == UartLog::Port::USB) {
		if (UartLog::log_usb[core_id()])
			UartLog::write_usb(ptr, len);
	}

	return len;
}

} // namespace MetaModule
