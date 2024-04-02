#pragma once
#include <cstdint>

namespace MathTools
{
#if defined(__GNUC__) &&                                                                                               \
	((defined(__ARM_ARCH_7A__) && (__ARM_ARCH_7A__ == 1)) || (defined(__ARM_ARCH_7M__) && (__ARM_ARCH_7M__ == 1)) ||   \
	 (defined(__ARM_ARCH_7EM__) && (__ARM_ARCH_7EM__ == 1)) ||                                                         \
	 (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ == 1)))

static inline int32_t signed_saturate(int32_t val, uint32_t sat) {
	asm("ssat %0, %1, %2" : "=r"(val) : "I"(sat), "r"(val));
	return val;
}

static inline int32_t unsigned_saturate(int32_t val, uint32_t sat) {
	asm("usat %0, %1, %2" : "=r"(val) : "I"(sat), "r"(val));
	return val;
}

#else

static inline int32_t signed_saturate(int32_t val, uint32_t sat) {
	if ((sat >= 1U) && (sat <= 32U)) {
		const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
		const int32_t min = -1 - max;
		if (val > max) {
			return max;
		} else if (val < min) {
			return min;
		}
	}
	return val;
}

static inline int32_t unsigned_saturate(int32_t val, uint32_t sat) {
	if (sat <= 31U) {
		const uint32_t max = ((1U << sat) - 1U);
		if (val > (int32_t)max) {
			return max;
		} else if (val < 0) {
			return 0U;
		}
	}
	return (uint32_t)val;
}

#endif

} // namespace MathTools
