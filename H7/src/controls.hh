#pragma once
#include "conf/adc_spi_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "muxed_adc.hh"
#include "params.hh"

using namespace mdrivlib;

struct Controls {
	Controls(MuxedADC &potadc, CVAdcChipT &cvadc, Params &params, Params &dest);

	MuxedADC &potadc;
	CVAdcChipT &cvadc;
	Params &params;
	Params &dest;

	RotaryEncoder<RotaryHalfStep> rotary = {GPIO::C, 8, GPIO::C, 7};
	DebouncedPin<GPIO::C, 10, PinPolarity::Inverted> button0;
	DebouncedPin<GPIO::C, 11, PinPolarity::Inverted> button1;
	DebouncedPin<GPIO::C, 6, PinPolarity::Inverted> rotary_button;
	DebouncedPin<GPIO::G, 6, PinPolarity::Normal> gate_in0;
	DebouncedPin<GPIO::G, 7, PinPolarity::Normal> gate_in1;
	DebouncedPin<GPIO::D, 12, PinPolarity::Normal> clock_in;

	FPin<GPIO::D, 13, PinMode::Output> clock_out;

	MemoryTransfer mem_xfer;

	void read();
	void start();

	void store_pot_reading(uint32_t pot_id, uint32_t val)
	{
		latest_pot_reading[_pot_map[pot_id]] = val;
	}

	uint32_t get_pot_reading(uint32_t pot_id)
	{
		return latest_pot_reading[pot_id];
	}

	void store_patchcv_reading(uint32_t patchcv)
	{
		latest_patchcv_reading = patchcv;
	}
	uint32_t get_patchcv_reading()
	{
		return latest_patchcv_reading;
	}

private:
	Timekeeper read_controls_task;
	Timekeeper read_cvadc_task;

	uint32_t latest_patchcv_reading;
	uint32_t latest_pot_reading[8];
	const uint8_t _pot_map[8] = {1, 4, 0, 5, 3, 6, 7, 2};

	bool _rotary_moved_while_pressed = false;
};

