#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {

#if defined(STM32H7)
	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::A, 9, mdrivlib::PinMode::Output>;
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::A, 10, mdrivlib::PinMode::Output>;
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::A, 11, mdrivlib::PinMode::Output>;
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::A, 12, mdrivlib::PinMode::Output>;

#elif defined(STM32MP1)
	using Pin0 = mdrivlib::FPin<mdrivlib::GPIO::D, 5, mdrivlib::PinMode::Output>;
	using Pin1 = mdrivlib::FPin<mdrivlib::GPIO::D, 6, mdrivlib::PinMode::Output>;
	using Pin2 = mdrivlib::FPin<mdrivlib::GPIO::E, 15, mdrivlib::PinMode::Output>;
	using Pin3 = mdrivlib::FPin<mdrivlib::GPIO::G, 15, mdrivlib::PinMode::Output>;

	using red_LED1 = mdrivlib::FPin<mdrivlib::GPIO::Z, 6, mdrivlib::PinMode::Output>;
	using red_LED2 = mdrivlib::FPin<mdrivlib::GPIO::I, 8, mdrivlib::PinMode::Output>;
	using green_LED1 = mdrivlib::FPin<mdrivlib::GPIO::Z, 7, mdrivlib::PinMode::Output>;
	using green_LED2 = mdrivlib::FPin<mdrivlib::GPIO::I, 9, mdrivlib::PinMode::Output>;

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
