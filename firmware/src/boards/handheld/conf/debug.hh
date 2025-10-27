#pragma once
#include "drivers/pin.hh"

struct Debug {
	struct NoPin {
		void high() {
		}
		void low() {
		}
	};

	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::D, 7, mdrivlib::PinMode::Output>; //Third pin
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::E, 5, mdrivlib::PinMode::Output>; //Fourth pin

	using Pin2 = NoPin;
	using Pin3 = NoPin;
	using Pin4 = NoPin;
	using Pin5 = NoPin;
	using Pin6 = NoPin;
	using Pin7 = NoPin;

	using green_LED1 = NoPin;
	using blue_LED1 = NoPin;
	using red_LED1 = NoPin;

	static inline red_LED1 red_LED1_init;
	static inline blue_LED1 blue_LED1_init;
	static inline green_LED1 green_LED1_init;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;

	static inline Pin4 pin_4_init;
	static inline Pin5 pin_5_init;
	static inline Pin6 pin_6_init;
	static inline Pin7 pin_7_init;
};

template<unsigned PinN>
struct DebugN;

template<>
struct DebugN<0> {
	using Pin = Debug::Pin0;
};
template<>
struct DebugN<1> {
	using Pin = Debug::Pin1;
};
template<>
struct DebugN<2> {
	using Pin = Debug::Pin2;
};
template<>
struct DebugN<3> {
	using Pin = Debug::Pin3;
};

#ifndef __clang__
#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
#else
#define GCC_OPTIMIZE_OFF
#endif
