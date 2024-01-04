#pragma once
#include "audio/auxsignal.hh"
#include "conf/auxstream_conf.hh"
#include "conf/control_conf.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "gpio_expander_reader.hh"
#include "metaparams.hh"
#include "midi_controls.hh"
#include "param_block.hh"
#include "params.hh"
#include "usb/midi_host.hh"
#include "usb/midi_message.hh"
#include "util/edge_detector.hh"
#include "util/interp_param.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

using mdrivlib::DebouncedPin;
using mdrivlib::GPIOExpander;
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref, DoubleAuxStreamBlock &auxsignal_blocks_ref, MidiHost &midi_host);

	void start();
	void process();

private:
	void update_params();
	void update_debouncers();

	float get_pot_reading(uint32_t pot_id);
	uint32_t get_patchcv_reading();
	uint32_t get_jacksense_reading();

	template<size_t block_num>
	void start_param_block();

	mdrivlib::Timekeeper read_controls_task;

	// Digital controls: Rotary, Buttons and Gate jacks
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, MMControlPins::rotA, MMControlPins::rotB> rotary;
	DebouncedPin<MMControlPins::rotS, PinPolarity::Inverted> rotary_button;
	DebouncedPin<MMControlPins::but0, PinPolarity::Inverted> button0;
	DebouncedPin<MMControlPins::gate_in_1, PinPolarity::Normal> gate_in_1;
	DebouncedPin<MMControlPins::gate_in_2, PinPolarity::Normal> gate_in_2;
	bool _rotary_moved_while_pressed = false;

	// Analog controls (pots)
	static constexpr size_t NumPotAdcs = sizeof(PotConfs) / sizeof(AdcChannelConf);
	std::array<uint16_t, NumPotAdcs> pot_vals{};
	mdrivlib::AdcDmaPeriph<PotAdcConf> pot_adc{pot_vals, PotConfs};

	static constexpr size_t NumParamUpdatesPerAdcReading = 78; // see note below
	InterpParam<float, NumParamUpdatesPerAdcReading> _knobs[PanelDef::NumPot];
	bool _new_adc_data_ready = false;

	// Jack plug sensing
	mdrivlib::I2CPeriph i2c{a7m4_shared_i2c_codec_conf};
	mdrivlib::GPIOExpander jacksense_reader{i2c, mainboard_gpio_expander_conf};
	mdrivlib::GPIOExpander extaudio_jacksense_reader{i2c, extaudio_gpio_expander_conf};
	SharedBusQueue i2cqueue{jacksense_reader, extaudio_jacksense_reader};

	// MIDI
	MidiHost &_midi_host;
	LockFreeFifoSpsc<MidiMessage, 256> _midi_rx_buf;
	Midi::MessageParser _midi_parser;
	EdgeStateDetector _midi_connected;

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	bool _buffer_full = false;
	bool _first_param = true;

	DoubleAuxStreamBlock &auxstream_blocks;
	mdrivlib::PinChangeInt<AuxStreamUpdateConf> auxstream_updater;
	AuxStream auxstream;
};

// Todo: calc NumParamUpdatesPerAdcReading from AdcSampTime, PotAdcConf::oversampling_ratio, and ADC periph clock (PLL_Div2... rcc...)
// Tested with APB clock (rcc set to PER, but don't think that matters. clock_div set to APBClk_Div1):
//  APB1 clk = 104.5MHz
//  gets divided by 2.25???  ==> 46.4MHz
//  46.4MHz / 2clks / 13 channels / 1024 OS = 1.742kHz
//  48000 / 1742Hz = 27.. we add 1 to be safe it doesn't overflow
//  Had ~30mV of noise @ 1.742kHz
// Tested with PLL4 clock (rcc set to PLL4, clock_div set to PLL_Div1)
//  PLL4 Clk: 66MHz
//  gets divided by 4 ==> 16.5MHz
//  16.5MHz / 2clks / 13 channels / 1024 OS = 619.74Hz
//  48000 / 619.74 = 77.45.. we round up so it doesn't overshoot
} // namespace MetaModule
