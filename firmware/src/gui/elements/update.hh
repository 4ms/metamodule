#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "gui/elements/redraw.hh"
#include "lvgl.h"
#include "params_state.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include <optional>

namespace MetaModule
{

namespace ElementUpdate
{
inline std::optional<float> get_mapped_param_value(const ParamsState &params, unsigned mapped_panel_id) {
	if (mapped_panel_id >= params.knobs.size())
		return {};

	auto latched = params.knobs[mapped_panel_id];
	if (latched.changed)
		return latched.val;
	else
		return {};
}

inline void
update_element_value(const ParamElement &, const ParamsState &params, PatchData &patch, const GuiElement &gui_el) {
	if (!gui_el.obj || !gui_el.mapped_panel_id.has_value())
		return;

	auto val = ElementUpdate::get_mapped_param_value(params, gui_el.mapped_panel_id.value());

	if (val.has_value())
		patch.set_static_knob_value(gui_el.module_idx, gui_el.idx.param_idx, val.value());
}

inline void update_element_value(const BaseElement &, const ParamsState &, PatchData &, const GuiElement &) {
	//Catch-all
}
} // namespace ElementUpdate

struct UpdateElement {
	ParamsState &params;
	PatchData &patch;
	GuiElement &gui_el;

	bool operator()(auto &el) {
		// Update mapped knob values -> store in patch (static_knobs)
		ElementUpdate::update_element_value(el, params, patch, gui_el);

		auto val = patch.get_static_knob_value(gui_el.module_idx, gui_el.idx.param_idx);
		if (!val.has_value())
			return false;

		return ElementRedrawDetails::redraw_element(el, gui_el, val.value());
	}
};

} // namespace MetaModule
