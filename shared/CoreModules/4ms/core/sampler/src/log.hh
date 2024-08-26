#pragma once
#include <cstdio>

#define STS_PRINT_ERROR 1
#define STS_PRINT_LOG 1
#define STS_PRINT_DEBUG 1

inline void _do_printf_impl(const char *str) {
	printf("%s", str);
}

inline void _do_printf_impl(auto... args) {
	printf(args...);
}

inline void pr_err(auto... args) {
	if constexpr (STS_PRINT_ERROR)
		_do_printf_impl(args...);
}

inline void pr_log(auto... args) {
	if constexpr (STS_PRINT_LOG)
		_do_printf_impl(args...);
}

inline void pr_dbg(auto... args) {
	if constexpr (STS_PRINT_DEBUG)
		_do_printf_impl(args...);
}
