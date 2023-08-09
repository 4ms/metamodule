#pragma once

#ifdef __SSE4_2__
#include <nmmintrin.h>
#else
#define SIMDE_ENABLE_NATIVE_ALIASES
#include "VCV_adaptor/simde/simde/x86/sse4.2.h"
#endif
