#pragma once
#include "patch/panels/panel_pro_defs.hh"

using PanelDef = ProPanelDef;

namespace MetaModule
{

// The panel input jack (0 = In1) that each codec input channel reads.
// p1: codec input channels 1 and 2 read In2 and In1, and channels 3..6 read In3..In6 (verified on p1)
inline constexpr std::array<uint32_t, PanelDef::NumAudioIn> audio_in_order{1, 0, 2, 3, 4, 5};

constexpr bool codec_outs_match_panel_order = false;

constexpr unsigned panel_out_of_codec_chan(unsigned codec_chan) {
	return PanelDef::NumAudioOut - 1 - codec_chan;
}

} // namespace MetaModule
