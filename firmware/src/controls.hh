#pragma once
#include "conf/adc_spi_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/i2c.hh"
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
	Controls(MuxedADC &potadc, CVAdcChipT &cvadc, DoubleBufParamBlock &param_blocks_ref, GPIOExpander &gpio_expander);

	MuxedADC &potadc;
	CVAdcChipT &cvadc;
	GPIOExpander &jacksense_reader;

	RotaryEncoder<RotaryHalfStep> rotary = {
		MMControlPins::rotA.gpio,
		MMControlPins::rotA.pin,
		MMControlPins::rotB.gpio,
		MMControlPins::rotB.pin,
	};
	DebouncedPin<MMControlPins::but0.gpio, MMControlPins::but0.pin, PinPolarity::Inverted> button0;
	DebouncedPin<MMControlPins::but1.gpio, MMControlPins::but1.pin, PinPolarity::Inverted> button1;
	DebouncedPin<MMControlPins::rotS.gpio, MMControlPins::rotS.pin, PinPolarity::Inverted> rotary_button;

	// Todo: std::tuple<GateIn1Type, GateIn2Type, ClockInType> gate_ins;
	// gate_in<0>.update();
	DebouncedPin<MMControlPins::clkin.gpio, MMControlPins::clkin.pin, PinPolarity::Normal> clock_in;
	DebouncedPin<MMControlPins::gate1.gpio, MMControlPins::gate1.pin, PinPolarity::Normal> gate_in1;
	DebouncedPin<MMControlPins::gate2.gpio, MMControlPins::gate2.pin, PinPolarity::Normal> gate_in2;

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

	void store_jacksense_reading(uint16_t reading)
	{
		latest_jacksense_reading = reading;
	}
	uint32_t get_jacksense_reading()
	{
		return latest_jacksense_reading;
	}

private:
	Timekeeper read_controls_task;
	Timekeeper read_cvadc_task;

	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	bool _buffer_full = true;
	bool _first_param = true;

	uint32_t latest_patchcv_reading;
	uint16_t latest_jacksense_reading;
	uint32_t latest_pot_reading[NumPot];
	const uint8_t _pot_map[NumPot] = {1, 4, 0, 5, 3, 6, 7, 2};
	InterpParam<float, StreamConf::Audio::BlockSize> _knobs[NumPot];

	bool _rotary_moved_while_pressed = false;
};
} // namespace MetaModule
