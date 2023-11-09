#pragma once
#include "audio.hh"

namespace MetaModule
{

void AudioStream::handle_button_events(uint32_t event_bitmask, float param_val) {
	unsigned i = 0;
	while (event_bitmask) {
		if (event_bitmask & 0b1)
			player.set_panel_param(i + FirstExtButton, param_val);
		event_bitmask >>= 1;
		i++;
	}
}

} // namespace MetaModule
