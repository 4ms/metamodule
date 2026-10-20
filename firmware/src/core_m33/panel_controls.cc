#include "panel_controls.hh"
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{

using namespace mdrivlib;

namespace
{
// Lower priority than the HSEM interrupt (0: see HWSemaphoreGlobalBase::enable_all_handlers()), so
// a new block can start during update(), but update() never interrupts start_param_block()
const TimekeeperConfig FrameTimerConf{
	.TIMx = TIM6,
	.period_ns = TimekeeperConfig::Hz(48000),
	.priority1 = 1,
	.priority2 = 0,
};
} // namespace

PanelControls::PanelControls(DoubleBufParamBlock &param_blocks)
	: param_blocks{param_blocks}
	, cur_metaparams{&param_blocks[0].metaparams} {
}

void PanelControls::start() {
	// Same as MP1's Controls::start()
	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreGlobalBase::register_channel_ISR<ParamsBuf1Lock>([this] { start_param_block<0>(); });

	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreGlobalBase::register_channel_ISR<ParamsBuf2Lock>([this] { start_param_block<1>(); });

	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();
	HWSemaphoreGlobalBase::enable_all_handlers();

	frame_timer.init(FrameTimerConf, [this] { update(); });
	frame_timer.start();
}

// The A35 just released the other block's semaphore: it's done with that block
template<size_t block_num>
void PanelControls::start_param_block() {
	cur_metaparams = &param_blocks[block_num].metaparams;
	new_block = true;
}

void PanelControls::update() {
	rotary.update();
	rotary_button.update();
	back_button.update();

	// Like MP1, the metaparams are written once per block, at its first frame
	if (new_block) {
		new_block = false;
		update_metaparams();
	}
}

void PanelControls::update_metaparams() {
	update_rotary();

	cur_metaparams->meta_buttons[0].transfer_events(back_button);
}

// Same as MP1's Controls::update_rotary()
void PanelControls::update_rotary() {
	if (rotary_button.is_just_pressed()) {
		rotary_moved_while_pressed = false;
		cur_metaparams->rotary_button.register_rising_edge();
	}

	if (rotary_button.is_just_released()) {
		if (rotary_moved_while_pressed) {
			cur_metaparams->rotary_button.reset();
		} else {
			cur_metaparams->rotary_button.register_falling_edge();
		}
	}
	cur_metaparams->rotary_button.set_state_no_events(rotary_button.is_pressed());

	int new_rotary_motion = rotary.read();
	bool pressed = rotary_button.is_pressed();
	cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
	cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
	// If the rotary was turned at any point since the button was pressed
	rotary_moved_while_pressed |= pressed && (new_rotary_motion != 0);
}

} // namespace MetaModule
