#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {

	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::F, 15, mdrivlib::PinMode::Output>;
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::G, 3, mdrivlib::PinMode::Output>;
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::G, 0, mdrivlib::PinMode::Output>;
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::C, 2, mdrivlib::PinMode::Output>;
	using Pin4 = mdrivlib::FPin<mdrivlib::GPIO::Z, 2, mdrivlib::PinMode::Output>;
	using Pin5 = mdrivlib::FPin<mdrivlib::GPIO::Z, 0, mdrivlib::PinMode::Output>;

	using red_LED1 = mdrivlib::FPin<mdrivlib::GPIO::Z, 6, mdrivlib::PinMode::Output>;
	using red_LED2 = mdrivlib::FPin<mdrivlib::GPIO::I, 8, mdrivlib::PinMode::Output>;
	using green_LED1 = mdrivlib::FPin<mdrivlib::GPIO::Z, 7, mdrivlib::PinMode::Output>;
	using green_LED2 = mdrivlib::FPin<mdrivlib::GPIO::I, 9, mdrivlib::PinMode::Output>;

	static inline red_LED1 red_LED1_init;
	static inline red_LED2 red_LED2_init;
	static inline green_LED1 green_LED1_init;
	static inline green_LED2 green_LED2_init;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;
	static inline Pin4 pin_4_init;
	static inline Pin5 pin_5_init;
};

#define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
