#pragma once
#include <cstdarg>
#include <cstdio>

namespace MetaModule
{
struct UartLog {
	static void log(const char *format, ...) {
		va_list va;
		va_start(va, format);
		vprintf(format, va);
		va_end(va);
	}
};
} // namespace MetaModule
