#include "debug.hh"

Debug::Debug() {
}

void Debug::set(int pin, bool value) {
  if (value)
    pins_[pin].high();
  else
    pins_[pin].low();
}
