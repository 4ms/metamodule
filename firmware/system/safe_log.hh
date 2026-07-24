#pragma once
#include "console/uart_log.hh"
#include <cstdint>

namespace MetaModule
{

// Formats into a stack buffer and writes directly to the console, bypassing
// newlib stdio entirely. printf() can call malloc(), so this is required
// anywhere that runs underneath malloc (e.g. _sbrk) or reports a heap failure.
struct SafeLog {
	char buf[224];
	unsigned pos = 0;

	void ch(char c) {
		if (pos < sizeof(buf))
			buf[pos++] = c;
	}

	void str(const char *s) {
		while (*s)
			ch(*s++);
	}

	void u64(uint64_t v, unsigned base = 10) {
		char tmp[24];
		unsigned n = 0;
		do {
			unsigned digit = v % base;
			tmp[n++] = digit < 10 ? char('0' + digit) : char('a' + digit - 10);
			v /= base;
		} while (v && n < sizeof(tmp));
		while (n)
			ch(tmp[--n]);
	}

	void i64(int64_t v) {
		if (v < 0) {
			ch('-');
			u64(uint64_t(-v));
		} else {
			ch('+');
			u64(uint64_t(v));
		}
	}

	void hex(uintptr_t v) {
		str("0x");
		u64(v, 16);
	}

	void flush() {
		ch('\n');
		UartLog::write_stdout(buf, pos);
		pos = 0;
	}
};

} // namespace MetaModule
