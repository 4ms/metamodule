#pragma once
#include "auxsignal.hh"
#include "conf/auxstream_conf.hh"
#include "conf/control_conf.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "muxed_adc.hh"
#include "params.hh"
#include "util/interp_param.hh"

namespace MetaModule
{

using mdrivlib::DebouncedPin;
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref, DoubleAuxStreamBlock &auxsignal_blocks_ref);

	static constexpr size_t NumPotAdcs = sizeof(PotConfs) / sizeof(AdcChannelConf);
	std::array<uint16_t, NumPotAdcs> pot_vals;
	mdrivlib::AdcDmaPeriph<PotAdcConf> pot_adc{pot_vals, PotConfs};

	MultiGPIOReader jacksense_reader;

	mdrivlib::RotaryEncoder<mdrivlib::RotaryHalfStep> rotary = {
		MMControlPins::rotA.gpio,
		MMControlPins::rotA.pin,
		MMControlPins::rotB.gpio,
		MMControlPins::rotB.pin,
	};

	DebouncedPin<MMControlPins::rotS.gpio, MMControlPins::rotS.pin, PinPolarity::Inverted> rotary_button;
	DebouncedPin<MMControlPins::but0.gpio, MMControlPins::but0.pin, PinPolarity::Inverted> button0;

	DebouncedPin<MMControlPins::gate_in_1.gpio, MMControlPins::gate_in_1.pin, PinPolarity::Normal> gate_in_1;
	DebouncedPin<MMControlPins::gate_in_2.gpio, MMControlPins::gate_in_2.pin, PinPolarity::Normal> gate_in_2;

	void update_debouncers();
	void start();
	void update_params();

	void store_jacksense_reading(uint16_t reading);
	uint32_t get_jacksense_reading();
	uint32_t get_pot_reading(uint32_t pot_id);
	uint32_t get_patchcv_reading();

private:
	mdrivlib::Timekeeper read_controls_task;

	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	bool _buffer_full = true;
	bool _first_param = true;

	DoubleAuxStreamBlock &auxstream_blocks;
	mdrivlib::PinChangeInt<AuxStreamUpdateConf> auxstream_updater;
	AuxStream auxstream;

	uint16_t latest_jacksense_reading;
	static constexpr size_t NumParamUpdatesPerAdcReading = 155;
	// Todo: calc this from AdcSampTime, PotAdcConf::oversampling_ratio, and ADC periph clock (PLL_Div2... rcc...)
	// PLL Clock = PLL4 = 66MHz
	// "Div2" --> 33MHz
	// Maybe it gets /4 somewhere? ==> 8.25MHz
	// 8.25MHz / 2clks / 13 channels / 1024 OS = 309.87Hz
	// 48000 / 309.87Hz = 155.. we add 1 to be safe it doesn't overflow
	InterpParam<float, NumParamUpdatesPerAdcReading + 1> _knobs[PanelDef::NumPot];
	float f_knobs[PanelDef::NumPot];

	bool _rotary_moved_while_pressed = false;

	bool _new_adc_data_ready = false;

	template<int block_num>
	void start_param_block();
};
} // namespace MetaModule
