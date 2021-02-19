#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
struct Debug {
	using Pin0 = FPin<GPIO::A, 9, PinMode::Output>;
	using Pin1 = FPin<GPIO::A, 10, PinMode::Output>;
	using Pin2 = FPin<GPIO::A, 11, PinMode::Output>;
	using Pin3 = FPin<GPIO::A, 12, PinMode::Output>;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
};
