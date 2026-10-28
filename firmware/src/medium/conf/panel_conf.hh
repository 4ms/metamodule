#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"

namespace MetaModule
{

// The panel input jack (0 = In1) that each codec input channel reads
inline constexpr auto &audio_in_order = PanelDef::audioin_order;

constexpr bool codec_outs_match_panel_order = true;

} // namespace MetaModule
