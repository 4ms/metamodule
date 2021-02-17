#pragma once
#include "conf/control_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "muxed_adc.hh"

struct Controls {

	MuxedADC &potadc;
	CVAdcChipT &cvadc;

	RotaryEncoder<RotaryHalfStep> rotary = {GPIO::C, 8, GPIO::C, 7};
	DebouncedPin<GPIO::C, 10, PinPolarity::Inverted> button0;
	DebouncedPin<GPIO::C, 11, PinPolarity::Inverted> button1;
	DebouncedPin<GPIO::C, 6, PinPolarity::Inverted> rotary_button;
	DebouncedPin<GPIO::G, 6, PinPolarity::Normal> gate_in0;
	DebouncedPin<GPIO::G, 7, PinPolarity::Normal> gate_in1;
	DebouncedPin<GPIO::D, 12, PinPolarity::Normal> clock_in;

	FPin<GPIO::D, 13, PinMode::Output> clock_out;

	Controls(MuxedADC &potadc, CVAdcChipT &cvadc);

	void read();
	void start();

private:
	Timekeeper read_controls_task;
	Timekeeper read_cvadc_task;
};
