#pragma once
#include "conf/audio_pins_conf.hh"
#include "conf/control_expander_conf.hh"
#include "conf/frame_rate_conf.hh"
#include "core_m4/midi_controls.hh"
#include "din_midi.hh"
#include "expander_controls.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin_change.hh"
#include "drivers/rotary.hh"
#include "midi/midi_message.hh"
#include "param_block.hh"
#include "usb/midi_host.hh"
#include "usb/usb_connection.hh"
#include "usb/usb_midi_device.hh"
#include "util/edge_detector.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <atomic>
#include <optional>
#include <span>

namespace MetaModule
{

// MP2's version of MP1's Controls (core_m4/controls.hh): reads the panel controls and writes them
// into the param blocks that the A35's audio stream reads (and passes on to the GUI).
// (Named PanelControls because the pro conf's pins are in namespace Controls.)
//
// Into the param blocks so far, as on MP1: the nav encoder (ENC102) and its button (MP1's rotary), the
// Back button (MP1's button 0), the gate ins, jack sense, and BUT1-8, which are MP1's first Button
// Expander. And the knob encoders ENC1..16: their clicks per block (MetaParams::encoder_clicks).
//
// The rest are read, but not passed on yet: the encoders' buttons and the other buttons on the I2C
// expanders (expander_controls.hh), and the control encoder (ENC103) and its button. For bring-up,
// print_changes() reports them on the console (and the gate ins and jack sense).
//
// The headphone amp is on only while headphones are plugged in: the frame interrupt drives
// HP_SHUTDOWN low while HP_SENSE is (debounced) high.
//
// As on MP1: when the A35 releases a param block's semaphore, we start filling the other block,
// one frame per audio frame, from an interrupt on the SAI's frame clock (LRCLK), so we fill the
// frames the audio stream reads (the first block-size frames) at the sample rate. The metaparams
// are written at a block's first frame. Each frame sends the patch's outgoing MIDI (USB or DIN5) and
// takes one received message (MP1's Controls::parse_midi()). The DIN5 jacks are MP1's MIDI Expander's
// DIN5 port (the pro has no TRS MIDI jacks).
class PanelControls {
public:
	PanelControls(DoubleBufParamBlock &param_blocks);

	void start();

	// The USB connection status, for the GUI (MP1's Controls asks UsbManager from its interrupt; here
	// the main loop passes it in)
	void set_usb_connection(UsbConnection conn) {
		usb_connection = conn;
	}

	// Routes USB MIDI between the patch and the USB MIDI host or device (whichever is connected)
	void start_midi(MidiHost &midi_host, UsbMidiDevice &midi_device);

	// Main loop
	void process();

	// Main loop: reads the jack sense expander (U1212) on I2C4, every JackSensePollMs. The caller
	// holds the shared I2C4 lock, and passes the M33's I2C4 peripheral (UsbManager's).
	// As MP1's SensePinReader: until the first good read, and while the expander isn't answering
	// (fail-safe), all jacks are reported as patched.
	void update_jack_sense(mdrivlib::I2CPeriph &i2c4);

	// Audio frames so far (the frame clock interrupts)
	uint32_t num_frames() const {
		return frame_count;
	}

private:
	void update();
	void update_metaparams();
	void update_rotary();
	void update_midi_connected();
	void update_button_expander();
	void update_encoders();
	void print_changes();
	void update_headphone_amp();
	void process_midi_frame(Params &params);
	void route_usb_midi_rx(std::span<uint8_t> rxbuffer);

	template<size_t block_num>
	void start_param_block();

	mdrivlib::PinChangeInt<FrameRatePinChangeConf> frame_task;

	// The direct encoders' B is RotaryEnc's A, and vice versa: with A first, they count backwards
	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, Controls::Direct::NavEncB, Controls::Direct::NavEncA> rotary;
	mdrivlib::DebouncedPin<Controls::Direct::NavEncBut, mdrivlib::PinPolarity::Inverted> rotary_button;
	mdrivlib::DebouncedPin<Controls::Direct::BackBut, mdrivlib::PinPolarity::Inverted> back_button;
	bool rotary_moved_while_pressed = false;

	ExpanderControls expanders;

	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, Controls::Direct::CtlEncB, Controls::Direct::CtlEncA> ctl_encoder;
	mdrivlib::DebouncedPin<Controls::Direct::CtlEncBut, mdrivlib::PinPolarity::Inverted> ctl_encoder_button;
	volatile int32_t ctl_encoder_pos = 0;
	mdrivlib::DebouncedPin<Controls::Direct::GateIn1, mdrivlib::PinPolarity::Normal> gate_in_1;
	mdrivlib::DebouncedPin<Controls::Direct::GateIn2, mdrivlib::PinPolarity::Normal> gate_in_2;

	// HP_SENSE is high when headphones are plugged in. It needs the internal pull-up.
	using HpSensePin = mdrivlib::FPin<Headphone::SensePin.gpio, Headphone::SensePin.pin, mdrivlib::PinMode::Input>;
	using HpShutdownPin =
		mdrivlib::FPin<Headphone::ShutdownPin.gpio, Headphone::ShutdownPin.pin, mdrivlib::PinMode::Output>;
	HpSensePin hp_sense_pin{mdrivlib::PinPull::Up};
	HpShutdownPin hp_shutdown_pin{mdrivlib::PinPull::None, mdrivlib::PinSpeed::Low, mdrivlib::PinOType::PushPull};
	// Sampled every HpSenseFrames frames (1ms at 48kHz), so the debouncer needs ~12ms of no bouncing
	static constexpr uint32_t HpSenseFrames = 48;
	uint32_t hp_sense_ctr = 0;
	Debouncer<> hp_sense;
	volatile bool headphones_plugged = false;

	static constexpr uint32_t JackSensePollMs = 50;
	uint32_t last_jack_sense_tm = 0;
	std::optional<uint16_t> jack_sense_reading; // bit set = pin high
	bool jack_sense_failed = false;
	// Fail-safe, same as MP1's SensePinReader: this many errors, and this long without a good read
	static constexpr uint32_t JackSenseFailSafeErrors = 8;
	static constexpr uint32_t JackSenseFailSafeMs = 5000;
	// Good reads in a row needed to leave the fail-safe state
	static constexpr uint32_t JackSenseRecoverReads = 2;
	uint32_t jack_sense_errors = 0;
	uint32_t jack_sense_last_ok_tm = 0;
	uint32_t jack_sense_good_reads = 0;
	bool jack_sense_failsafe = false;
	void publish_jack_sense();
	// Main loop -> update_metaparams(). As MetaParams::jack_senses: 1 = patched. The upper 16 bits
	// are MP1's Audio Expander, which the pro doesn't have: reported as patched, as MP1 does.
	std::atomic<uint32_t> jack_senses{0xFFFF'FFFF};
	std::atomic<uint8_t> jack_sense_faults{0};

	// update_encoders(): the encoder positions sent so far
	std::array<int32_t, ExpanderControls::NumEncoders> sent_enc_positions{};

	// print_changes(): what it last reported
	int32_t printed_ctl_encoder_pos = 0;
	bool printed_gate_in_1 = false;
	bool printed_gate_in_2 = false;
	bool printed_headphones_plugged = false;

	DoubleBufParamBlock &param_blocks;
	MetaParams *cur_metaparams;
	Params *cur_params;
	Params *cur_params_end;
	bool first_frame = true;
	bool block_full = false;
	volatile uint32_t frame_count = 0;
	// Set by the HSEM interrupt, and taken by update(), which owns the pointers above
	std::atomic<int> next_block = -1;
	volatile UsbConnection usb_connection = UsbConnection::None;

	DinMidi din_midi;

	MidiHost *midi_host = nullptr;
	UsbMidiDevice *midi_device = nullptr;
	// USB interrupt (device) or main loop (host: only one is connected at a time) -> update()
	LockFreeFifoSpsc<MidiMessage, 256> midi_usb_rx_buf;
	Midi::MessageParser midi_parser;
	EdgeStateDetector midi_usb_connected_raw;
	bool midi_usb_connected = false;
};

} // namespace MetaModule
