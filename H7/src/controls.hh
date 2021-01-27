#pragma once
#include "conf/control_conf.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "util/filter.hh"

struct GPIO_expander_conf {
	uint32_t addr;
	Pin int_pin;
};

template<I2C_TypeDef *const I2C>
struct GPIOExpander {
	GPIOExpander(GPIO_expander_conf &conf);
};

struct Controls {
	AnalogIn<AdcSpi_MAX11666<2>, 4, Oversampler<16>> cvadc{spi_adc_conf};

	GPIOExpander<I2C1> sense{.addr = 0x00, .int_pin = {GPIO : D, 11}};
	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	Controls();
	void read();
	void start();

private:
	Timekeeper read_controls_task;
};
