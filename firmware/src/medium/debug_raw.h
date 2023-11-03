#include <cstdint>

//C and C++

static inline void DebugPin5High() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << 3);
}

static inline void DebugPin5Low() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << (3 + 16));
}
