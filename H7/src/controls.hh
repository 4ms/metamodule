#pragma once
#include "conf/adc_spi_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "muxed_adc.hh"
using namespace mdrivlib;

struct Params {
	float cvjacks[4] = {0.f, 0.f, 0.f, 0.f};
	float patchcv = 0.f;
	float knobs[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

	Toggler gate_ins[2];
	Toggler clock_in;
	Toggler jack_senses[15];

	Toggler buttons[2];
	Toggler rotary_button;

	int32_t rotary_motion = 0;
	int32_t rotary_pushed_motion = 0;

	void init()
	{
		cvjacks[0] = 0.f;
		cvjacks[1] = 0.f;
		cvjacks[2] = 0.f;
		cvjacks[3] = 0.f;
		knobs[0] = 0.f;
		knobs[1] = 0.f;
		knobs[2] = 0.f;
		knobs[3] = 0.f;
		knobs[4] = 0.f;
		knobs[5] = 0.f;
		knobs[6] = 0.f;
		knobs[7] = 0.f;
		patchcv = 0.f;
		rotary_motion = 0;
		rotary_pushed_motion = 0;
		clock_in.register_rising_edge();
		clock_in.is_just_pressed();
		clock_in.set_state(0);
		gate_ins[0].register_rising_edge();
		gate_ins[0].is_just_pressed();
		gate_ins[0].set_state(0);
		gate_ins[1].register_rising_edge();
		gate_ins[1].is_just_pressed();
		gate_ins[1].set_state(0);
		for (int i = 0; i < 15; i++) {
			jack_senses[i].register_rising_edge();
			jack_senses[i].is_just_pressed();
			jack_senses[i].set_state(0);
		}
	}

	// has an HSEM id?
	void lock_for_read()
	{
		while (write_lock)
			;
		read_lock = false;
	}
	void unlock_for_read()
	{
		read_lock = true;
	}

	void lock_for_write()
	{
		while (read_lock)
			;
		write_lock = true;
	}

	void unlock_for_write()
	{
		write_lock = false;
	}

	bool _is_locked()
	{
		return write_lock || read_lock;
	}

private:
	volatile bool write_lock = false;
	volatile bool read_lock = false;
};

struct Controls {

	MuxedADC &potadc;
	CVAdcChipT &cvadc;
	ControlData &dest;

	RotaryEncoder<RotaryHalfStep> rotary = {GPIO::C, 8, GPIO::C, 7};
	DebouncedPin<GPIO::C, 10, PinPolarity::Inverted> button0;
	DebouncedPin<GPIO::C, 11, PinPolarity::Inverted> button1;
	DebouncedPin<GPIO::C, 6, PinPolarity::Inverted> rotary_button;
	DebouncedPin<GPIO::G, 6, PinPolarity::Normal> gate_in0;
	DebouncedPin<GPIO::G, 7, PinPolarity::Normal> gate_in1;
	DebouncedPin<GPIO::D, 12, PinPolarity::Normal> clock_in;

	FPin<GPIO::D, 13, PinMode::Output> clock_out;

	Controls(MuxedADC &potadc, CVAdcChipT &cvadc, ControlData &dest);

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

