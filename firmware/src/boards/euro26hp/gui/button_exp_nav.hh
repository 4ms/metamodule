#pragma once
#include "params/metaparams.hh"

namespace MetaModule
{

inline void button_expander_nav(MetaParams &metaparams) {
	// Button 5: back
	if (metaparams.ext_buttons_high_events & (1 << 4))
		metaparams.meta_buttons[0].register_rising_edge();
	if (metaparams.ext_buttons_low_events & (1 << 4))
		metaparams.meta_buttons[0].register_falling_edge();

	// Buttons 7,8: Rotary turn
	if (metaparams.ext_buttons_high_events & (1 << 7))
		metaparams.rotary.motion--;
	if (metaparams.ext_buttons_high_events & (1 << 6))
		metaparams.rotary.motion++;

	// Button 6: Rotary press
	if (metaparams.ext_buttons_high_events & (1 << 5))
		metaparams.rotary_button.register_rising_edge();
	if (metaparams.ext_buttons_low_events & (1 << 5))
		metaparams.rotary_button.register_falling_edge();

	// Buttons 3,4: Back+Rotary
	if (metaparams.ext_buttons_high_events & (1 << 3))
		metaparams.rotary_with_metabutton.motion--;
	if (metaparams.ext_buttons_high_events & (1 << 2))
		metaparams.rotary_with_metabutton.motion++;

	//0?
	//1?

	// Clear expander 1's events:
	metaparams.ext_buttons_high_events &= 0xFFFFFF00;
	metaparams.ext_buttons_low_events &= 0xFFFFFF00;
}

} // namespace MetaModule
