#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {

#if defined(STM32H7)
	using Pin0 = FPin<GPIO::A, 9, PinMode::Output>;
	using Pin1 = FPin<GPIO::A, 10, PinMode::Output>;
	using Pin2 = FPin<GPIO::A, 11, PinMode::Output>;
	using Pin3 = FPin<GPIO::A, 12, PinMode::Output>;

#elif defined(STM32MP1)
	using Pin0 = FPin<GPIO::D, 5, PinMode::Output>;
	using Pin1 = FPin<GPIO::D, 6, PinMode::Output>;
	using Pin2 = FPin<GPIO::E, 15, PinMode::Output>;
	using Pin3 = FPin<GPIO::D, 4, PinMode::Output>;

	using red_LED1 = FPin<GPIO::Z, 6, PinMode::Output>;
	using red_LED2 = FPin<GPIO::I, 8, PinMode::Output>;
	using green_LED1 = FPin<GPIO::Z, 7, PinMode::Output>;
	using green_LED2 = FPin<GPIO::I, 9, PinMode::Output>;

	static inline red_LED1 red_LED1_init;
	static inline red_LED2 red_LED2_init;
	static inline green_LED1 green_LED1_init;
	static inline green_LED2 green_LED2_init;
#endif

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
};

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
