#pragma once
// #include "gui/elements/context.hh"
// #include "gui/elements/element_name.hh"
// #include "gui/elements/state_names.hh"
// #include "gui/pages/add_map_popup.hh"
// #include "gui/pages/manual_control_popup.hh"
// #include "gui/pages/module_view_mapping_pane_list.hh"
// #include "gui/pages/page_list.hh"
// #include "params/params_state.hh"
#include "CoreModules/elements/element_counter.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"

namespace MetaModule
{

struct MapCableUserData {
	uint16_t module_id{};
	ElementCount::Indices idx;
};

//TODO
struct ModuleViewCablePane {
	ModuleViewCablePane(PatchContext &context) {
	}
};

} // namespace MetaModule
