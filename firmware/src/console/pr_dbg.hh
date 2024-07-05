#pragma once
#include <cstdio>

namespace
{

/////////////////////////////////////////////////
// Change these to enable/disable logging levels

// Error: unexpected conditions that may lead to program failure
inline constexpr bool PRINT_ERROR = true;

// Warnings: conditions that deserve attention but do not lead to program failure
inline constexpr bool PRINT_WARN = true;

// Info: Important or useful information that is neither a warning or error
inline constexpr bool PRINT_INFO = true;

// Debug: temporary messages used for debugging
inline constexpr bool PRINT_DEBUG = true;

// Trace: detailed log of execution
inline constexpr bool PRINT_TRACE = false;

// Dump: large amounts of verbose data
inline constexpr bool PRINT_DUMP = false;
/////////////////////////////////////////////////

inline void _do_printf_impl(const char *str) {
	printf("%s", str);
}

inline void _do_printf_impl(auto... args) {
	printf(args...);
}

inline void pr_err(auto... args) {
	if constexpr (PRINT_ERROR)
		_do_printf_impl(args...);
}

inline void pr_warn(auto... args) {
	if constexpr (PRINT_WARN)
		_do_printf_impl(args...);
}

inline void pr_info(auto... args) {
	if constexpr (PRINT_INFO)
		_do_printf_impl(args...);
}

inline void pr_dbg(auto... args) {
	if constexpr (PRINT_DEBUG)
		_do_printf_impl(args...);
}

inline void pr_trace(auto... args) {
	if constexpr (PRINT_TRACE)
		_do_printf_impl(args...);
}

inline void pr_dump(auto... args) {
	if constexpr (PRINT_DUMP)
		_do_printf_impl(args...);
}

} // namespace
