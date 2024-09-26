#pragma once
#include <cstdio>

namespace
{

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

inline void _do_printf_impl(const char *str) {
	printf("%s", str);
}

inline void _do_printf_impl(auto... args) {
	printf(args...);
}

// Error: unexpected conditions that may lead to program failure
inline void pr_err(auto... args) {
#if LOG_LEVEL > 0
	_do_printf_impl(args...);
#endif
}

// Warnings: conditions that deserve attention but do not lead to program failure
inline void pr_warn(auto... args) {
#if LOG_LEVEL > 1
	_do_printf_impl(args...);
#endif
}

// Info: Important or useful information that is neither a warning or error
inline void pr_info(auto... args) {
#if LOG_LEVEL > 2
	_do_printf_impl(args...);
#endif
}

// Debug: temporary messages used for debugging
inline void pr_dbg(auto... args) {
#if LOG_LEVEL > 3
	_do_printf_impl(args...);
#endif
}

// Trace: detailed log of execution
inline void pr_trace(auto... args) {
#if LOG_LEVEL > 4
	_do_printf_impl(args...);
#endif
}

// Dump: large amounts of verbose data
inline void pr_dump(auto... args) {
#if LOG_LEVEL > 5
	_do_printf_impl(args...);
#endif
}

} // namespace
