#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include <cstdint>
#include <optional>
#include <vector>

namespace MetaModule
{

struct GuiElement {
	lv_obj_t *obj = nullptr;				 //gui object
	lv_obj_t *map_ring = nullptr;			 //gui map ring object
	uint16_t module_idx = 0;				 //index in patch
	uint16_t idx = 0;						 //index of cateogry in module: param_idx, light_idx, etc
	std::optional<uint16_t> mapped_panel_id; //patch mapping
};

// Element and it context in a patch, drawn on the screen
struct DrawnElement {
	GuiElement drawn;
	const Element &element;
};

// using DrawnElements = std::vector<DrawnElement>;

} // namespace MetaModule
