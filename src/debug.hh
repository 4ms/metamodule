#pragma once

#include "pin.hh"
const uint8_t kNumDebugPins = 1;

struct Debug {
    // using namespace GPIOPin;
  static void set_0(bool value);

private:
    static inline PinL<GPIO::D, 2> pin0 {PinMode::OUTPUT, PinPull::NONE};
};
