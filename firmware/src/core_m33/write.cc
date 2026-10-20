#include "console.hh"
#include "console/uart_log.hh"

namespace
{
void write_console(const char *ptr, int len) {
	MetaModule::M33Console::Lock lock;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			MetaModule::M33Console::putchar('\r');
		MetaModule::M33Console::putchar(ptr[i]);
	}
}
} // namespace

// printf() etc. output (pr_err(), pr_info(), ...): to the shared console UART
extern "C" int _write(int, char *ptr, int len) {
	write_console(ptr, len);
	return len;
}

// Bypasses stdio (MP1's USB console uses this to echo keystrokes from the USB interrupt)
void MetaModule::UartLog::write_stdout(const char *ptr, int len) {
	write_console(ptr, len);
}
