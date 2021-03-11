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
#include "util/interp_param.hh"

using namespace mdrivlib;

namespace MetaModule
{
struct Controls {
	Controls(MuxedADC &potadc, CVAdcChipT &cvadc, ParamBlock *param_block);

	MuxedADC &potadc;
	CVAdcChipT &cvadc;

	RotaryEncoder<RotaryHalfStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedPin<GPIO::C, 10, PinPolarity::Inverted> button0;
	DebouncedPin<GPIO::C, 11, PinPolarity::Inverted> button1;
	DebouncedPin<GPIO::C, 6, PinPolarity::Inverted> rotary_button;
	// Todo: std::tuple<GateIn1Type, GateIn2Type, ClockInType> gate_ins;
	// gate_in<0>.update();
	DebouncedPin<GPIO::D, 12, PinPolarity::Normal> clock_in;
	DebouncedPin<GPIO::G, 6, PinPolarity::Normal> gate_in1;
	DebouncedPin<GPIO::G, 7, PinPolarity::Normal> gate_in2;

	FPin<GPIO::D, 13, PinMode::Output> clock_out;

	void update_debouncers();
	void start();
	void update_params();

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

	ParamBlock *param_blocks;
	ParamBlock *cur_param_block;
	Params *cur_params;

	uint32_t latest_patchcv_reading;
	uint32_t latest_pot_reading[NumPot];
	const uint8_t _pot_map[NumPot] = {1, 4, 0, 5, 3, 6, 7, 2};
	InterpParam<float, StreamConf::Audio::BlockSize> _knobs[NumPot];

	int32_t _rotary_motion = 0;
	bool _rotary_moved_while_pressed = false;
};
} // namespace MetaModule
