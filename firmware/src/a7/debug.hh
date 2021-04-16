#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {
	using Pin0 = FPin<GPIO::D, 5, PinMode::Output>;
	using Pin1 = FPin<GPIO::D, 6, PinMode::Output>;
	using Pin2 = FPin<GPIO::E, 15, PinMode::Output>;
	using Pin3 = FPin<GPIO::D, 4, PinMode::Output>;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
};

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
