#pragma once
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

struct Debug {
	using Pin0 = FPin<GPIO::A, 9>;
	using Pin1 = FPin<GPIO::A, 10>;
	using Pin2 = FPin<GPIO::A, 11>;
	using Pin3 = FPin<GPIO::A, 12>;

	static inline Pin0 pin_0_init;
	static inline Pin1 pin_1_init;
	static inline Pin2 pin_2_init;
	static inline Pin3 pin_3_init;

	// static void set_0(bool value)
	// {
	// 	pin0.set_to(value);
	// }
	// static void set_1(bool value)
	// {
	// 	pin1.set_to(value);
	// }
	// static void set_2(bool value)
	// {
	// 	pin2.set_to(value);
	// }
	// static void set_3(bool value)
	// {
	// 	pin3.set_to(value);
	// }

	// static void toggle_0()
	// {
	// 	pin0.toggle();
	// }
	// static void toggle_1()
	// {
	// 	pin1.toggle();
	// }
	// static void toggle_2()
	// {
	// 	pin2.toggle();
	// }
	// static void toggle_3()
	// {
	// 	pin3.toggle();
	// }

	// private:
	// static inline Pin pin0{GPIO::A, 9, PinMode::Output};
	// static inline Pin pin1{GPIO::A, 10, PinMode::Output};
	// static inline Pin pin2{GPIO::A, 11, PinMode::Output};
	// static inline Pin pin3{GPIO::A, 12, PinMode::Output};
};
