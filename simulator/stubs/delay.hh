#include <cstdint>
#include <time.h>

inline uint64_t get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
}

inline void delay_ms(uint32_t ms) {
	uint64_t tickstart = get_time();
	uint64_t wait = ms + 1;
	while ((get_time() - tickstart) < wait)
		;
}
