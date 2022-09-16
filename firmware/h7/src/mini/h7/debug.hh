#pragma once
#include "drivers/pin.hh"
struct PinStub {
	static void high() {}
	static void low() {}
};

struct Debug {
	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::A, 9, mdrivlib::PinMode::Output>;
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::A, 10, mdrivlib::PinMode::Output>;
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::A, 11, mdrivlib::PinMode::Output>;
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::A, 12, mdrivlib::PinMode::Output>;
	using Pin4 = PinStub;
	using Pin5 = PinStub;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
};

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
