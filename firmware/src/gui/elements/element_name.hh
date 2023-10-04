#pragma once
#include "CoreModules/elements/elements.hh"
#include <string>

namespace MetaModule
{

template<typename PanelDef>
std::string get_panel_name(const BaseElement &, uint16_t) {
	return "";
}

template<typename PanelDef>
std::string get_panel_name(const ParamElement &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_param_name(panel_id);
	return name;
}

template<typename PanelDef>
std::string get_panel_name(const JackInput &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_injack_name(panel_id);
	return name;
}

template<typename PanelDef>
std::string get_panel_name(const JackOutput &, uint16_t panel_id) {
	std::string name{8};
	name += PanelDef::get_map_outjack_name(panel_id);
	return name;
}

} // namespace MetaModule
