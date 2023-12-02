#pragma once
#include "gui/elements/context.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

struct FullElementName {
	std::string_view module_name;
	std::string_view element_name;
};

enum class ElementType { Param, Input, Output, Light };

// Return the module name and element name, given the IDs and type (not the Element)
FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch);

// Append to string `opts` the module and jack names connected to the given GuiElement in the patch
void append_connected_jack_name(std::string &opts, GuiElement const &drawn, PatchData const &patch);

} // namespace MetaModule
