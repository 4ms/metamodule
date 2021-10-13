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

//controls conf:
using mdrivlib::AdcChannelConf;
using mdrivlib::AdcPeriphConf;

struct PotAdcConf : AdcPeriphConf {
	static constexpr auto adc_periph_num = mdrivlib::AdcPeriphNum::_1;
	static constexpr auto oversample = true;
	static constexpr auto oversampling_ratio = 1024;
	static constexpr auto oversampling_right_bitshift = 10;
	static constexpr auto use_dma = true;
	static constexpr auto dma_periph_num = DMA_2;
	static constexpr auto stream_num = 7;
	static constexpr auto request_num = DMA_REQUEST_ADC1;
	static constexpr auto dma_priority = Low;
	static constexpr auto use_dma_fifo = false;
	static constexpr auto use_dma_irq = false;
	static constexpr auto clock_div = mdrivlib::PLL_Div2;
};

enum Pots : uint32_t { PotA, PotB, PotC, PotD, PotE, PotF, PotX, PotY, PotZ, PotL, PotR, PotQ };

constexpr auto PotConfs = std::to_array({
	AdcChannelConf{{GPIO::B, 1}, mdrivlib::AdcChanNum::_5, PotA}, //, mdrivlib::AdcSamplingTime::_32Cycles},
	AdcChannelConf{{GPIO::C, 3}, mdrivlib::AdcChanNum::_13, PotB},
	AdcChannelConf{{GPIO::A, 3}, mdrivlib::AdcChanNum::_15, PotC},
});
/////////////

using mdrivlib::DebouncedPin;
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref, DoubleAuxStreamBlock &auxsignal_blocks_ref);

	static constexpr size_t NumPotAdcs = sizeof(PotConfs) / sizeof(AdcChannelConf);
	/*non cacheable, in static buffer?*/ static inline std::array<uint16_t, NumPotAdcs> pot_vals;

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
	InterpParam<float, StreamConf::Audio::BlockSize> _knobs[PanelDef::NumPot];

	bool _rotary_moved_while_pressed = false;

	template<int block_num>
	void start_param_block();
};
} // namespace MetaModule
