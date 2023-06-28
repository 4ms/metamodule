#pragma once
#include "CoreModules/elements/elements.hh"
#include <string>

namespace MetaModule
{

template<typename PanelDef>
std::string get_panel_name(BaseElement &, uint16_t) {
	return "";
}

template<typename PanelDef>
std::string get_panel_name(Knob &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_param_name(panel_id);
	return name;
}

template<typename PanelDef>
std::string get_panel_name(JackInput &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_injack_name(panel_id);
	return name;
}

template<typename PanelDef>
std::string get_panel_name(JackOutput &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_outjack_name(panel_id);
	return name;
}

} // namespace MetaModule
