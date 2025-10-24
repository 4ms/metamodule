#pragma once
#include "conf/control_conf.hh"
#include "conf/pin_conf.hh"
#include "drivers/lis2hh12_accel.hh"
#include "drivers/uart.hh"
#include "params/metaparams.hh"
#include "params/params.hh"

//
#include "drivers/debounced_switch.hh"
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

using mdrivlib::DebouncedButton;
using mdrivlib::DebouncedPin;
using mdrivlib::PinPolarity;
using mdrivlib::RotaryEnc;

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

	RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[0].A, ControlPins::encoders[0].B> encoder1;
	RotaryEnc<mdrivlib::RotaryFullStep, ControlPins::encoders[1].A, ControlPins::encoders[1].B> encoder2;

	DebouncedButton<ControlPins::encoder_but_1, PinPolarity::Inverted> encoder1_but;
	DebouncedButton<ControlPins::encoder_but_2, PinPolarity::Inverted> encoder2_but;
	DebouncedButton<ControlPins::button_1, PinPolarity::Inverted> button_1;
	DebouncedButton<ControlPins::button_2, PinPolarity::Inverted> button_2;
	DebouncedButton<ControlPins::button_3, PinPolarity::Inverted> button_3;
	DebouncedButton<ControlPins::button_4, PinPolarity::Inverted> button_4;

	DebouncedPin<ControlPins::sense_injack, PinPolarity::Inverted> sense_in_jack;
	DebouncedPin<ControlPins::sense_outjack, PinPolarity::Inverted> sense_out_jack;

	mdrivlib::LIS2HH12accelerometer accel{ControlPins::sensor_i2c_conf};

	// MIDI
	MidiHost &usb_midi_host;
	LockFreeFifoSpsc<MidiMessage, 256> usb_midi_rx_buf;
	EdgeStateDetector usb_midi_connected_raw;
	bool usb_midi_connected = false;

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;

	mdrivlib::PinChangeInt<FrameRatePinChangeConf> read_controls_task;
	bool _buffer_full = false;
	bool _first_param = true;

	uint32_t sample_rate = 48000;

	unsigned num_pot_updates = 0;
};

} // namespace MetaModule
