#pragma once
#include "printf.h"

namespace
{

/////////////////////////////////////////////////
// Change these to enable/disable logging levels
static constexpr bool PRINT_ERROR = true;
static constexpr bool PRINT_WARN = true;
static constexpr bool PRINT_DEBUG = true;
inline constexpr bool PRINT_TRACE = false;
/////////////////////////////////////////////////

inline void _do_printf_impl(const char *str) {
	printf_("%s", str);
}

inline void _do_printf_impl(auto... args) {
	printf_(args...);
}

inline void pr_err(auto... args) {
	if constexpr (PRINT_ERROR)
		_do_printf_impl(args...);
}

inline void pr_warn(auto... args) {
	if constexpr (PRINT_WARN)
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

} // namespace
