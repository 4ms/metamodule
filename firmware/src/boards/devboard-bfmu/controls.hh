#pragma once
#include "conf/adc_conf.hh"
#include "conf/control_conf.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/pin_conf.hh"
#include "metaparams.hh"
#include "params.hh"

//
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change.hh"
#include "drivers/rotary.hh"
#include "midi/midi_message.hh"
#include "midi_controls.hh"
#include "param_block.hh"
#include "usb/midi_host.hh"
#include "util/edge_detector.hh"
#include "util/interp_param.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

using mdrivlib::DebouncedPin;
using mdrivlib::GPIOExpander;
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref, MidiHost &midi_host);

	void start();
	void process();

private:
	void update_params();
	void update_debouncers();

	float get_pot_reading(uint32_t pot_id);

	void set_samplerate(unsigned sample_rate);

	template<size_t block_num>
	void start_param_block();

	void parse_midi();
	void update_midi_connected();
	void update_rotary();

	mdrivlib::PinChangeInt<FrameRatePinChangeConf> read_controls_task;

	// Digital controls: Rotary, Buttons and Gate jacks
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[0].A, ControlPins::encoders[0].B> encoder1;
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[1].A, ControlPins::encoders[1].B> encoder2;

	DebouncedPin<ControlPins::random_gate_in, PinPolarity::Inverted> random_gate_in;
	DebouncedPin<ControlPins::trig_in, PinPolarity::Inverted> trig_in;
	DebouncedPin<ControlPins::sync_in, PinPolarity::Inverted> sync_in;
	DebouncedPin<ControlPins::rec_gate_in, PinPolarity::Inverted> rec_gate_in;

	// MIDI UART
	// DAC OUTS

	// NEOPIXEL OUTS: handle with TIM periph?

	// GATE OUTS
	mdrivlib::PinF<ControlPins::clock_out, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted> clock_out;

	// PWM OUT:
	mdrivlib::PinF<ControlPins::haptic_out, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Normal> haptic_out;

	// Analog inputs (ignoring MUX for now)
	static constexpr size_t NumPotAdcs = PotConfs.size();
	std::array<uint16_t, NumPotAdcs> pot_vals{};
	mdrivlib::AdcDmaPeriph<PotAdcConf> pot_adc{pot_vals, PotConfs};

	std::array<InterpParamVariable<float>, PanelDef::NumPot> knobs;
	static constexpr uint32_t AdcReadFrequency = 580; //571
	bool _new_adc_data_ready = false;

	// MIDI
	MidiHost &_midi_host;
	LockFreeFifoSpsc<MidiMessage, 256> _midi_rx_buf;
	Midi::MessageParser _midi_parser;
	EdgeStateDetector _midi_connected_raw;
	bool _midi_connected = false;

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	bool _buffer_full = false;
	bool _first_param = true;

	uint32_t sample_rate = 48000;

	unsigned num_pot_updates = 0;
};

} // namespace MetaModule
