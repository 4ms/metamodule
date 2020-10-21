#pragma once

#include "drivers/pin.hh"

struct Debug {
	static void set_0(bool value)
	{
		pin0.set_to(value);
	}
	static void set_1(bool value)
	{
		pin1.set_to(value);
	}
	static void set_2(bool value)
	{
		pin2.set_to(value);
	}
	static void set_3(bool value)
	{
		pin3.set_to(value);
	}
	
	static void toggle_0() { pin0.toggle(); }
	static void toggle_1() { pin1.toggle(); }
	static void toggle_2() { pin2.toggle(); }
	static void toggle_3() { pin3.toggle(); }

private:
	static inline Pin pin0{GPIO::G, 14, PinMode::Output};
	static inline Pin pin1{GPIO::G, 9, PinMode::Output};
	static inline Pin pin2{GPIO::D, 3, PinMode::Output};
	static inline Pin pin3{GPIO::D, 4, PinMode::Output};
};
