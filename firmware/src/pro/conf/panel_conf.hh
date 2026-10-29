#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"

namespace MetaModule
{

// The pro panel: MP1's jacks, and 16 encoders (ENC1..16) in place of MP1's 12 pots.
// ENC1..12 have MP1's knob IDs (A-F, u-z), so MP1 patches play with their knobs on ENC1..12.
// ENC13..16 have the next four IDs (the first of the expander knob IDs, which nothing uses).
//
// This shadows MP1's ::PanelDef (panel_medium_defs.hh) in namespace MetaModule, which is where the
// firmware uses it. CoreModules' hub headers still see ::PanelDef, but only for the jack counts,
// which are the same. (So headers that use the knob members must include conf/panel_conf.hh.)
struct PanelDef : ::PanelDef {
	static constexpr uint32_t NumPot = 0;
	static constexpr uint32_t NumEncoders = 16;
	static constexpr uint32_t NumKnobs = NumEncoders;

	static constexpr std::array<std::string_view, NumKnobs> KnobNames{
		"A", "B", "C", "D", "E", "F", "G", "H", "s", "t", "u", "v", "w", "x", "y", "z"};

	static constexpr bool is_encoder(uint32_t panel_knob_id) {
		return panel_knob_id < NumEncoders;
	}

	static constexpr std::string_view get_map_param_name(uint32_t id) {
		if (id < KnobNames.size())
			return KnobNames[id];
		return "?";
	}
};

inline constexpr unsigned NumPanelEncoders = PanelDef::NumEncoders;

// The panel input jack (0 = In1) that each codec input channel reads.
// p1: codec input channels 1 and 2 read In2 and In1, and channels 3..6 read In3..In6 (verified on p1)
inline constexpr std::array<uint32_t, PanelDef::NumAudioIn> audio_in_order{1, 0, 2, 3, 4, 5};

constexpr bool codec_outs_match_panel_order = false;

constexpr unsigned panel_out_of_codec_chan(unsigned codec_chan) {
	return PanelDef::NumAudioOut - 1 - codec_chan;
}

} // namespace MetaModule
