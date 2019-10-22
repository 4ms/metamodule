#include "debug.hh"

Debug::Debug() {
  pins_[0].init(GPIO_MODE_OUTPUT_PP);

  // __HAL_RCC_GPIOD_CLK_ENABLE();

  // GPIO_InitTypeDef gpio;
  // gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  // gpio.Mode = GPIO_MODE_OUTPUT_PP;
  // gpio.Pull = GPIO_NOPULL;

  // gpio.Pin = GPIO_PIN_5;
  // HAL_GPIO_Init(GPIOD, &gpio);

}

void Debug::set(int pin, bool value) {
  if (value)
    pins_[pin].high();
  else
    pins_[pin].low();
}
