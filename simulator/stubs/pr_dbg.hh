#pragma once
#include "printf.h"

namespace
{

// Change these to enable/disable logging levels
constexpr inline bool PRINT_ERROR = true;
constexpr inline bool PRINT_WARN = true;
constexpr inline bool PRINT_DEBUG = true;
constexpr inline bool PRINT_TRACE = false;

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

