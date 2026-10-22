#include "console.hh"
#include "console/console_buffer_writer.hh"
#include "console/uart_log.hh"

namespace
{
void write_uart(const char *ptr, int len) {
	MetaModule::M33Console::Lock lock;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			MetaModule::M33Console::putchar('\r');
		MetaModule::M33Console::putchar(ptr[i]);
	}
}

struct IrqGuard {
	uint32_t primask = __get_PRIMASK();
	IrqGuard() {
		__disable_irq();
	}
	~IrqGuard() {
		__set_PRIMASK(primask);
	}
};

MetaModule::ConsoleBufferWriter<IrqGuard> writer;
} // namespace

// printf() etc. output (pr_err(), pr_info(), ...): to our console buffer, or the UART until there is one
extern "C" int _write(int, char *ptr, int len) {
	MetaModule::UartLog::write_stdout(ptr, len);
	return len;
}

// Also bypasses stdio (MP1's USB console uses this to echo keystrokes from the USB interrupt)
void MetaModule::UartLog::write_stdout(const char *ptr, int len) {
	// Never waits for room: the M33 is the one that drains the buffers
	if (writer.attached())
		writer.write(ptr, len, false);
	else
		write_uart(ptr, len);
}

void MetaModule::UartLog::use_buffer(ConcurrentBuffer *buffer) {
	writer.attach(buffer);
}

void MetaModule::UartLog::use_direct() {
	writer.detach();
	// In case the drain had the UART (e.g. we're reporting a fault that happened while it did)
	mdrivlib::HWSemaphore<UartLock>::unlock(UartLockM4Drain);
}
