#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"

namespace MetaModule
{

// The panel input jack (0 = In1) that each codec input channel reads
inline constexpr auto &audio_in_order = PanelDef::audioin_order;

// The panel's knobs are pots, not encoders
inline constexpr unsigned NumPanelEncoders = 0;

constexpr bool codec_outs_match_panel_order = true;

// Not called (codec_outs_match_panel_order), but audio.cc's other branch needs it declared
constexpr unsigned panel_out_of_codec_chan(unsigned codec_chan) {
	return codec_chan;
}

} // namespace MetaModule
