#include "uart_log.hh"
#include "util/term_codes.hh"
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

void UartLog::write_uart(const char *ptr, size_t len) {
	for (auto idx = 0u; idx < len; idx++) {
		UartLog::putchar(*ptr++);
	}
}

//TODO: make this interrupt-safe
void UartLog::write_usb(const char *ptr, size_t len) {
	auto core = core_id();

	log_usb[core]->writer_ref_count++;
	std::atomic_signal_fence(std::memory_order_release);
	{
		if (log_usb[core]->use_color) {
			auto color = core_id() ? Term::Green : Term::Blue;
			log_usb[core]->write({color, strlen(color)});
		}

		log_usb[core]->write({ptr, len});

		if (log_usb[core]->use_color) {
			log_usb[core]->write({Term::Normal, strlen(Term::Normal)});
		}
	}
	std::atomic_signal_fence(std::memory_order_release);
	log_usb[core]->writer_ref_count--;
}

void UartLog::write_stdout(const char *ptr, size_t len) {
	if (UartLog::port[core_id()] == UartLog::Port::Uart) {
		UartLog::write_uart(ptr, len);

	} else if (UartLog::port[core_id()] == UartLog::Port::USB) {
		if (UartLog::log_usb[core_id()])
			UartLog::write_usb(ptr, len);
	}
}

// This is used for bypassing write() and going direct to UART
extern "C" void _putchar(char c) {
	UartLog::putchar(c);
}

} // namespace MetaModule
