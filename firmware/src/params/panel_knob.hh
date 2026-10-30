#pragma once
#include "conf/panel_conf.hh"
#include "patch/patch.hh"

namespace MetaModule
{

// A mapping to one of the panel's knobs: MP1's pots, or the pro's encoders
constexpr bool is_panel_knob(MappedKnob const &map) {
	return map.panel_knob_id < PanelDef::NumKnobs;
}

// A mapping to one of the pro's encoders. They don't catch up: they step the param from its own value.
constexpr bool is_panel_encoder(MappedKnob const &map) {
	return PanelDef::is_encoder(map.panel_knob_id);
}

constexpr bool is_button(MappedKnob const &map) {
	return map.panel_knob_id >= FirstButton && map.panel_knob_id <= LastButton;
}

constexpr std::optional<uint32_t> ext_button(MappedKnob const &map) {
	using namespace MetaModule;
	return MathTools::between<uint32_t>(map.panel_knob_id, FirstButton, LastButton);
}

} // namespace MetaModule
