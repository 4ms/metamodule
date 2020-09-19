#pragma once

#include "pin.hh"

struct Debug {
	static void set_0(bool value);
	static void set_1(bool value);

private:
	static inline PinL<GPIO::E, 7> pin0{PinMode::Output, PinPull::None};
	static inline PinL<GPIO::E, 8> pin1{PinMode::Output, PinPull::None};
};
