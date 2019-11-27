#include "debug.hh"

void Debug::set(int pin, bool value) {
  if (value)
    pins_[pin].high();
  else
    pins_[pin].low();
}
