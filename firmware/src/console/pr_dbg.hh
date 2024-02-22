#pragma once
#include <cstdio>

namespace
{

/////////////////////////////////////////////////
// Change these to enable/disable logging levels
inline constexpr bool PRINT_ERROR = true;
inline constexpr bool PRINT_WARN = true;
inline constexpr bool PRINT_INFO = true;
inline constexpr bool PRINT_DEBUG = true;
inline constexpr bool PRINT_TRACE = true;
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

} // namespace
