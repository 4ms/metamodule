#pragma once

#include "pin.hh"
#include <tuple>

struct Debug {
  static void set_0(bool value);

private:
    static inline PinL<GPIO::D, 2> pin0 {PinMode::Output, PinPull::None};
};
