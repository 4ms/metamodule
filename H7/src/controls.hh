#pragma once
#include "conf/adc_i2c_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/adc_i2c_max11645.hh"
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

	// Todo: Would be nice to use deduction to get rid of the SpiConfig<> template params
	using AdcSpiChip = AdcSpi_MAX11666<SpiConfig<spi_adc_conf_periphnum, spi_adc_conf_numchips>>;
	static const inline unsigned NumAdcChannels = 4;
	AnalogIn<AdcSpiChip, NumAdcChannels, Oversampler<16>> cvadc{spi_adc_conf};

	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	Controls(MuxedADC &potadc);
	void read();
	void start();

private:
	Timekeeper read_controls_task;
};
