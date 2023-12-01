#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {

	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::B, 10, mdrivlib::PinMode::Output>; //Control Exp pin 1 (AUX_I2C_SCL)
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::A, 14, mdrivlib::PinMode::Output>; //Control Exp pin 3 (EXTGPIO1)
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::E, 2, mdrivlib::PinMode::Output>;  //Control Exp pin 5 (EXTGPIO2)
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::G, 11, mdrivlib::PinMode::Output>; //Control Exp pin 7 (EXTGPIO3)

	using Pin4 = mdrivlib::FPin<mdrivlib::GPIO::E, 4, mdrivlib::PinMode::Output>;  //DEBUG0 pin 5 of debug header
	using Pin5 = mdrivlib::FPin<mdrivlib::GPIO::D, 3, mdrivlib::PinMode::Output>;  //DEBUG1 pin 7 of debug header
	using Pin6 = mdrivlib::FPin<mdrivlib::GPIO::B, 14, mdrivlib::PinMode::Output>; //DEBUG2 pad
	using Pin7 = mdrivlib::FPin<mdrivlib::GPIO::G, 6, mdrivlib::PinMode::Output>;  //DEBUG3 pad (p11)

	using green_LED1 =
		mdrivlib::FPin<mdrivlib::GPIO::B, 15, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;
	using blue_LED1 = mdrivlib::FPin<mdrivlib::GPIO::A, 9, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;
	using red_LED1 = mdrivlib::FPin<mdrivlib::GPIO::E, 14, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;

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

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
