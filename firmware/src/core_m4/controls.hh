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

	void set_samplerate(unsigned sample_rate);

	template<size_t block_num>
	void start_param_block();

	mdrivlib::PinChangeInt<FrameRatePinChangeConf> read_controls_task;

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

	InterpParamVariable<float> _knobs[PanelDef::NumPot]{};
	static constexpr uint32_t AdcReadFrequency = 580; //measured
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

	uint32_t sample_rate = 48000;

	DoubleAuxStreamBlock &auxstream_blocks;
	mdrivlib::PinChangeInt<AuxStreamUpdateConf> auxstream_updater;
	AuxStream auxstream;
};

} // namespace MetaModule
