#pragma once
#include "CoreModules/elements/base_element.hh"
#include <string>

namespace MetaModule
{

std::string get_panel_name(const BaseElement &, uint32_t);
std::string get_panel_name(const ParamElement &, uint32_t panel_id);
std::string get_panel_name(const JackInput &, uint32_t panel_id);
std::string get_panel_name(const JackOutput &, uint32_t panel_id);
std::string get_panel_brief_name(const JackOutput &, uint16_t panel_id);
std::string get_panel_brief_name(const JackInput &, uint16_t panel_id);

} // namespace MetaModule
