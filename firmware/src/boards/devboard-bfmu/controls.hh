#pragma once
#include "conf/adc_conf.hh"
#include "conf/control_conf.hh"
#include "conf/pin_conf.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change.hh"
#include "drivers/rotary.hh"
#include "drivers/uart.hh"
#include "gpio_expander_manager.hh"
#include "midi/midi_message.hh"
#include "param_block.hh"
#include "params/metaparams.hh"
#include "params/params.hh"
#include "usb/midi_host.hh"
#include "util/edge_detector.hh"
#include "util/interp_param.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

using mdrivlib::DebouncedPin;
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

	void test_pins();

	mdrivlib::PinChangeInt<FrameRatePinChangeConf> read_controls_task;

	// Digital controls: Rotary, Buttons and Gate jacks
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[0].A, ControlPins::encoders[0].B> encoder1;
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[1].A, ControlPins::encoders[1].B> encoder2;

	DebouncedPin<ControlPins::random_gate_in, PinPolarity::Inverted> random_gate_in;
	DebouncedPin<ControlPins::trig_in, PinPolarity::Inverted> trig_in;
	DebouncedPin<ControlPins::sync_in, PinPolarity::Inverted> sync_in;
	DebouncedPin<ControlPins::rec_gate_in, PinPolarity::Inverted> rec_gate_in;

	// Buttons/LEDs MUX
	GpioExpanderManager gpio_expanders;

	// MIDI UART
	mdrivlib::Uart<ControlPins::MIDI_Uart> uart_midi;

	// DAC OUTS
	// TODO

	// NEOPIXEL OUTS: handle with TIM periph?
	// TODO

	// GATE OUTS
	mdrivlib::PinF<ControlPins::clock_out, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Inverted> clock_out;
	//TODO: PWM OUT
	mdrivlib::PinF<ControlPins::haptic_out, mdrivlib::PinMode::Output, mdrivlib::PinPolarity::Normal> haptic_out;

	// Analog inputs (ignoring MUX for now)
	static constexpr size_t NumAdcPins = ADCs::AdcPins.size();
	std::array<uint16_t, NumAdcPins> pot_vals{};
	mdrivlib::AdcDmaPeriph<ADCs::PotAdcConf> pot_adc{pot_vals, ADCs::AdcPins};

	std::array<InterpParamVariable<float>, PanelDef::NumPot> knobs;
	static constexpr uint32_t AdcReadFrequency = 580; //571
	bool _new_adc_data_ready = false;

	// MIDI
	MidiHost &usb_midi_host;
	LockFreeFifoSpsc<MidiMessage, 256> usb_midi_rx_buf;
	LockFreeFifoSpsc<MidiMessage, 256> uart_midi_rx_buf;

	EdgeStateDetector usb_midi_connected_raw;
	bool usb_midi_connected = false;

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	LedStates *cur_leds;
	bool _buffer_full = false;
	bool _first_param = true;

	uint32_t sample_rate = 48000;

	unsigned num_pot_updates = 0;
};

} // namespace MetaModule
