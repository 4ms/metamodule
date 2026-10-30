#pragma once
#include "patch/panels/panel_medium_defs.hh"

using PanelDef = MediumPanelDef;

namespace MetaModule
{

// The panel input jack (0 = In1) that each codec input channel reads
inline constexpr std::array<uint32_t, PanelDef::NumAudioIn> audio_in_order{3, 2, 1, 0, 5, 4};

constexpr bool codec_outs_match_panel_order = true;

// Not called (codec_outs_match_panel_order), but audio.cc's other branch needs it declared
constexpr unsigned panel_out_of_codec_chan(unsigned codec_chan) {
	return codec_chan;
}

} // namespace MetaModule
