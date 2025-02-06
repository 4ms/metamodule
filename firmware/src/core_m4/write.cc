#include "uart_log.hh"

extern "C" int _write(int fd, char *ptr, int len) {
	// if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
	MetaModule::UartLog::write_stdout(ptr, len);
	return len;
	// } else
	// 	return -1;
}
