#pragma once
#include "conf/control_conf.hh"
#include "drivers/adc_i2c_max11645.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "util/filter.hh"

struct Controls {
	AnalogIn<AdcSpi_MAX11666<2>, 4, Oversampler<16>> cvadc{spi_adc_conf};

	GPIOExpander<16> sense{gpio_expander_conf};
	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	Controls(I2CPeriph &i2c);
	void read();
	void start();

private:
	Timekeeper read_controls_task;
	I2CPeriph &_i2c;
};
