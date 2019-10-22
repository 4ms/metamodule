#include "debug.hh"

Debug::Debug() {
  pins_[0].init(GPIO_MODE_OUTPUT_PP);
}

void Debug::set(int pin, bool value) {
  if (value)
    pins_[pin].high();
  else
    pins_[pin].low();
}
