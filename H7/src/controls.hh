#pragma once
#include "conf/adc_i2c_conf.hh"
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

// Handles 2-channel I2C ADC MAX11645)
// Channel 0 is connected to an 8x1 switch, with a pot on each input
// and 3 GPIO pins selecting one.
// Channel 1 is connected to Patch CV
class MuxedADC {
public:
	MuxedADC(const MuxedADC_Config &conf)
		: chan_sel{{conf.SEL0.gpio, conf.SEL0.pin, PinMode::Output},
				   {conf.SEL1.gpio, conf.SEL1.pin, PinMode::Output},
				   {conf.SEL2.gpio, conf.SEL2.pin, PinMode::Output}}
	{}

	void select_channel0_source(unsigned chan)
	{
		chan_sel[0].set_to(chan & 0b001);
		chan_sel[1].set_to(chan & 0b010);
		chan_sel[2].set_to(chan & 0b100);
	}

	void initiate_read() {}
	uint32_t get_val(int chan)
	{
		return 0;
	}

private:
	Pin chan_sel[3];
};

struct Controls {

	AnalogIn<AdcSpi_MAX11666<2>, 4, Oversampler<16>> cvadc{spi_adc_conf};
	MuxedADC potadc{muxed_adc_conf};

	GPIOExpander<16> sense{gpio_expander_conf};

	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	Controls(I2CPeriph &i2c);
	void read();
	void start();

	I2CPeriph &i2c;

private:
	Timekeeper read_controls_task;
};
