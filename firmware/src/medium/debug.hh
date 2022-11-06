#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {

	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::E, 4, mdrivlib::PinMode::Output>;
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::D, 3, mdrivlib::PinMode::Output>;
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::B, 14, mdrivlib::PinMode::Output>;
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::E, 1, mdrivlib::PinMode::Output>;
	// using Pin4 = mdrivlib::FPin<mdrivlib::GPIO::Z, 1, mdrivlib::PinMode::Output>; // Not exposed on p5
	// using Pin5 = mdrivlib::FPin<mdrivlib::GPIO::Z, 2, mdrivlib::PinMode::Output>; // Not exposed on p5

	using red_LED1 = mdrivlib::FPin<mdrivlib::GPIO::B, 15, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;
	using blue_LED1 = mdrivlib::FPin<mdrivlib::GPIO::A, 9, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;
	using green_LED1 =
		mdrivlib::FPin<mdrivlib::GPIO::E, 14, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted>;

	static inline red_LED1 red_LED1_init;
	static inline blue_LED1 blue_LED1_init;
	static inline green_LED1 green_LED1_init;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
	// static inline Pin4 pin_4_init;
	// static inline Pin5 pin_5_init;
};

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
