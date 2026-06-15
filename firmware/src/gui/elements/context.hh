#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include <cstdint>
#include <optional>

typedef struct _lv_obj_t lv_obj_t;

namespace MetaModule
{

struct GuiElement {
	lv_obj_t *obj = nullptr;				 //gui object
	lv_obj_t *map_ring = nullptr;			 //gui map ring object
	uint16_t module_idx = 0;				 //index of module in patch
	ElementCount::Counts count{};			 //Number elements of each category in module
	ElementCount::Indices idx;				 //index within cateogry in module: param_idx, injack_idx, etc
	std::optional<uint16_t> mapped_panel_id; //patch mapping
	std::optional<uint16_t> midi_mapped_id;	 //midi map panel_id
};

// Element and its context in a patch, drawn on the screen
struct DrawnElement {
	GuiElement gui_element;
	const Element &element;
};

} // namespace MetaModule
