#pragma once
#include <stdint.h>

#if !defined(SIMULATOR)
//C and C++

static inline void DebugPin2High() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << 0);
}

static inline void DebugPin2Low() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << (0 + 16));
}

static inline void DebugPin1High() {
	volatile uint32_t *GPIOE_BSRR = (volatile uint32_t *)(0x50006018);
	*GPIOE_BSRR = (1 << 5);
}

static inline void DebugPin1Low() {
	volatile uint32_t *GPIOE_BSRR = (volatile uint32_t *)(0x50006018);
	*GPIOE_BSRR = (1 << (5 + 16));
}

static inline void DebugPin0High() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << 7);
}

static inline void DebugPin0Low() {
	volatile uint32_t *GPIOD_BSRR = (volatile uint32_t *)(0x50005018);
	*GPIOD_BSRR = (1 << (7 + 16));
}

#define HARDWARE_BKPT() asm volatile("bkpt")

#else
static inline void DebugPin3High() {
}

static inline void DebugPin3Low() {
}

static inline void DebugPin2High() {
}

static inline void DebugPin2Low() {
}

static inline void DebugPin1High() {
}

static inline void DebugPin1Low() {
}

static inline void DebugPin0High() {
}

static inline void DebugPin0Low() {
}

#define HARDWARE_BKPT()

#endif
