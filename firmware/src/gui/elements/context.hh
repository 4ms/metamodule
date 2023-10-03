#pragma once
#include "CoreModules/elements/element_counter.hh"
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
	uint16_t module_idx = 0;				 //index of module in patch
	ElementCount::Counts count{};			 //Number elements of each category in module
	ElementCount::Indices idx;				 //index within cateogry in module: param_idx, injack_idx, etc
	std::optional<uint16_t> mapped_panel_id; //patch mapping
};

// Element and its context in a patch, drawn on the screen
struct DrawnElement {
	GuiElement gui_element;
	const Element &element;
};

} // namespace MetaModule
