#pragma once
#include "printf.h"

namespace
{

template<typename... Ts>
static void pr_dbg(Ts... args) {
	printf_(args...);
}

} // namespace
