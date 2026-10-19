#pragma once

// MP2 version of src/console/uart_log.hh (MP1's console: per-core buffers that the M4 drains to
// the UART). On MP2 each core writes to the console UART directly (core_a35/console.cc).
namespace MetaModule
{

struct UartLog {
	// stdout and stderr (via newlib's _write, see src/fs/syscall)
	static void write_stdout(const char *ptr, int len);
};

} // namespace MetaModule
