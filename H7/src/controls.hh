#pragma once
#include "conf/adc_i2c_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/adc_i2c_max11645.hh"
#include "drivers/adc_spi_max11666.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "muxed_adc.hh"
#include "util/filter.hh"

struct Controls {

	MuxedADC &potadc;
	CVAdcChipT &cvadc;

	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	// Controls(MuxedADC &potadc);
	Controls(MuxedADC &potadc, CVAdcChipT &cvadc);
	void read();
	void start();

private:
	Timekeeper read_controls_task;
};
