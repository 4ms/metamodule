#pragma once

#include "pin.hh"
const uint8_t kNumDebugPins = 1;

struct Debug {
  Debug();
  void set(int pin, bool value);

private:
	Pin<NORMAL> pins_[kNumDebugPins] = {
		{GPIO_PIN_2, GPIOD, OUTPUT},
	};
};
