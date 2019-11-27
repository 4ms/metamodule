#pragma once

#include "pin.hh"
const uint8_t kNumDebugPins = 1;

struct Debug {
//   Debug();
  static void set(int pin, bool value);

private:
	static inline Pin pins_[kNumDebugPins] = {
		{GPIO_PIN_2, GPIOD, OUTPUT},
	};
};
