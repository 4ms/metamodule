#pragma once
#include "printf.h"

namespace
{

template<typename T>
static void pr_dbg(T arg) {
	printf_("%s", arg);
}

template<typename... Ts>
static void pr_dbg(Ts... args) {
	printf_(args...);
}

} // namespace
