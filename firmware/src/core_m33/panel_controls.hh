#pragma once
#include "conf/control_expander_conf.hh"
#include "core_m4/midi_controls.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/rotary.hh"
#include "drivers/timekeeper.hh"
#include "midi/midi_message.hh"
#include "param_block.hh"
#include "usb/usb_connection.hh"
#include "usb/usb_midi_device.hh"
#include "util/edge_detector.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <span>

namespace MetaModule
{

// MP2's version of MP1's Controls (core_m4/controls.hh): reads the panel controls and writes them
// into the param blocks that the A35's audio stream reads (and passes on to the GUI).
// (Named PanelControls because the pro conf's pins are in namespace Controls.)
//
// So far, only the controls wired to MCU pins that MP1's GUI uses: the control encoder and its
// button (MP1's rotary), and the Back button (MP1's button 0). Not yet: the nav encoder, the gate
// ins, jack sense, and the knob encoders and buttons on the I2C expanders.
//
// As on MP1, when the A35 releases a param block's semaphore, we start filling the other block.
// MP1 runs the controls at the frame rate from an LRCLK pin interrupt; here a timer runs them at
// 48kHz. That's enough for debouncing, but per-frame data (gate ins) will need it synced to the
// audio frames.
//
// USB MIDI (MP1's Controls::parse_midi()): MP1 fills in one frame's MIDI per audio frame. Without
// frame sync, we'd fill frames the audio stream doesn't read (it reads the first block-size frames):
// a received message put there would be lost, and later read back as outgoing MIDI. So instead,
// when a block starts, we do all of its MIDI at once, for exactly the frames the audio stream uses
// (SharedIndex::audio_block_size): send the patch's outgoing USB MIDI, and put the received
// messages in, one per frame. The A35 doesn't touch the block again until the next one starts. The
// cost is up to one more block of latency than MP1.
class PanelControls {
public:
	PanelControls(DoubleBufParamBlock &param_blocks);

	void start();

	// The USB connection status, for the GUI (MP1's Controls asks UsbManager from its interrupt; here
	// the main loop passes it in)
	void set_usb_connection(UsbConnection conn) {
		usb_connection = conn;
	}

	// Routes USB MIDI between the USB device and the patch. audio_block_size is published by the A35.
	// (No USB MIDI host yet.)
	void start_midi(UsbMidiDevice &midi_device, volatile uint32_t const &audio_block_size);

private:
	void update();
	void update_metaparams();
	void update_rotary();
	void update_midi();
	void update_midi_connected();
	void process_midi_frame(Params &params);
	void route_usb_midi_rx(std::span<uint8_t> rxbuffer);

	template<size_t block_num>
	void start_param_block();

	mdrivlib::Timekeeper frame_timer;

	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, Controls::Direct::CtlEncA, Controls::Direct::CtlEncB> rotary;
	mdrivlib::DebouncedPin<Controls::Direct::CtlEncBut, mdrivlib::PinPolarity::Inverted> rotary_button;
	mdrivlib::DebouncedPin<Controls::Direct::BackBut, mdrivlib::PinPolarity::Inverted> back_button;
	bool rotary_moved_while_pressed = false;

	DoubleBufParamBlock &param_blocks;
	MetaParams *cur_metaparams;
	Params *cur_params;
	volatile bool new_block = false;
	volatile UsbConnection usb_connection = UsbConnection::None;

	UsbMidiDevice *midi_device = nullptr;
	volatile uint32_t const *audio_block_size = nullptr;
	LockFreeFifoSpsc<MidiMessage, 256> midi_usb_rx_buf; // USB interrupt -> update()
	Midi::MessageParser midi_parser;
	EdgeStateDetector midi_usb_connected_raw;
	bool midi_usb_connected = false;
};

} // namespace MetaModule
