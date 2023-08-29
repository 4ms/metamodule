#pragma once
#include "printf.h"

namespace
{

// Change these to enable/disable logging levels
static constexpr bool PRINT_ERROR = true;
static constexpr bool PRINT_WARN = true;
static constexpr bool PRINT_DEBUG = false;
static constexpr bool PRINT_TRACE = false;

inline void do_printf_(auto str) {
	printf_("%s", str);
}

inline void do_printf_(auto... args) {
	printf_(args...);
}

inline void pr_err(auto... args) {
	if constexpr (PRINT_ERROR)
		do_printf_(args...);
}

inline void pr_warn(auto... args) {
	if constexpr (PRINT_WARN)
		do_printf_(args...);
}

inline void pr_dbg(auto... args) {
	if constexpr (PRINT_DEBUG)
		do_printf_(args...);
}

inline void pr_trace(auto... args) {
	if constexpr (PRINT_TRACE)
		do_printf_(args...);
}

} // namespace
