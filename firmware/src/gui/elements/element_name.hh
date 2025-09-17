#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/element_type.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"

namespace MetaModule
{

struct FullElementName {
	std::string_view module_name;
	std::string_view element_name;
};

// Return the module name and element name, given the IDs and type (not the Element)
FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch);

// Append to string `opts` the module and jack names connected to the given GuiElement in the patch
void append_connected_jack_name(std::string &opts,
								ElementCount::Indices indices,
								uint16_t module_idx,
								PatchData const &patch);

void append_panel_name(std::string &opts, Element const &el, uint16_t panel_jack_id);

void set_param_item_name(lv_obj_t *label, MappedKnob const &map, PatchData *patch);

} // namespace MetaModule
