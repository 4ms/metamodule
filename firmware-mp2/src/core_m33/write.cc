#include "console.hh"

// printf() etc. output (pr_err(), pr_info(), ...): to the shared console UART
extern "C" int _write(int, char *ptr, int len) {
	MetaModule::M33Console::Lock lock;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			MetaModule::M33Console::putchar('\r');
		MetaModule::M33Console::putchar(ptr[i]);
	}
	return len;
}
