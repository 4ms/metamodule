#pragma once

struct ConcurrentBuffer;

// MP2 version of src/console/uart_log.hh. As on MP1, each core starts out writing to the console
// UART directly, then switches to writing into its ConcurrentBuffer in shared memory, which the M33
// sends on to the UART (core_m33/console_drain.hh), or to the USB console when a computer has
// connected to it (usb/device_cdc/usb_serial_device.cc).
// (core_a35/console.cc, core_m33/write.cc)
namespace MetaModule
{

struct UartLog {
	// stdout and stderr (via newlib's _write, see src/fs/syscall)
	static void write_stdout(const char *ptr, int len);

	// Switch the calling core's console output to its buffer
	static void use_buffer(ConcurrentBuffer *buffer);

	// Back to writing to the UART directly (e.g. to report a crash)
	static void use_direct();
};

} // namespace MetaModule
