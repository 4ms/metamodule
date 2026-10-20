#pragma once
#include "conf/control_expander_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/rotary.hh"
#include "drivers/timekeeper.hh"
#include "param_block.hh"

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
class PanelControls {
public:
	PanelControls(DoubleBufParamBlock &param_blocks);

	void start();

private:
	void update();
	void update_metaparams();
	void update_rotary();

	template<size_t block_num>
	void start_param_block();

	mdrivlib::Timekeeper frame_timer;

	mdrivlib::RotaryEnc<mdrivlib::RotaryFullStep, Controls::Direct::CtlEncA, Controls::Direct::CtlEncB> rotary;
	mdrivlib::DebouncedPin<Controls::Direct::CtlEncBut, mdrivlib::PinPolarity::Inverted> rotary_button;
	mdrivlib::DebouncedPin<Controls::Direct::BackBut, mdrivlib::PinPolarity::Inverted> back_button;
	bool rotary_moved_while_pressed = false;

	DoubleBufParamBlock &param_blocks;
	MetaParams *cur_metaparams;
	volatile bool new_block = false;
};

} // namespace MetaModule
