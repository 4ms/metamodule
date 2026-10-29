#pragma once
#include "conf/panel_conf.hh"
#include "patch/patch.hh"

namespace MetaModule
{

// A mapping to one of the panel's knobs: MP1's pots, or the pro's encoders.
// (MappedKnob::is_panel_knob() only knows MP1's 12 pots)
constexpr bool is_panel_knob(MappedKnob const &map) {
	return map.panel_knob_id < PanelDef::NumKnobs;
}

// A mapping to one of the pro's encoders. They don't catch up: they step the param from its own value.
constexpr bool is_panel_encoder(MappedKnob const &map) {
	return PanelDef::is_encoder(map.panel_knob_id);
}

} // namespace MetaModule
