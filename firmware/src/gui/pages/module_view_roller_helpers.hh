#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "gui/elements/context.hh"
#include "gui/elements/element_type.hh"
#include "gui/pages/base.hh"
#include "gui/pages/make_cable.hh"
#include "gui/styles.hh"
#include "patch/patch_data.hh"
#include "util/overloaded.hh"
#include <optional>

namespace MetaModule::ModView
{

inline bool is_light_only(GuiElement const &gui_el) {
	return (gui_el.count.num_lights > 0) && (gui_el.count.num_params == 0) && (gui_el.count.num_outputs == 0) &&
		   (gui_el.count.num_inputs == 0);
}

inline bool should_skip_for_cable_mode(std::optional<GuiState::CableBeginning> const &new_cable,
									   GuiElement const &gui_el,
									   GuiState &gui_state,
									   PatchData *patch,
									   uint16_t this_module_id) {
	if (gui_state.new_cable.has_value()) {
		uint16_t this_jack_id{};
		if (gui_el.count.num_inputs > 0)
			this_jack_id = gui_el.idx.input_idx;
		else if (gui_el.count.num_outputs > 0)
			this_jack_id = gui_el.idx.output_idx;
		else
			return true;
		auto this_jack_type = (gui_el.count.num_inputs > 0) ? ElementType::Input : ElementType::Output;
		if (!can_finish_cable(gui_state.new_cable.value(),
							  patch,
							  Jack{.module_id = this_module_id, .jack_id = this_jack_id},
							  this_jack_type,
							  gui_el.mapped_panel_id.has_value()))
			return true;
	}
	return false;
}

inline bool append_header(std::string &opts, ElementCount::Counts last_type, ElementCount::Counts this_type) {
	if (last_type.num_params == 0 && this_type.num_params > 0) {
		opts += Gui::orange_text("Params:") + "\n";
		return true;

	} else if ((last_type.num_inputs == 0 && last_type.num_outputs == 0) &&
			   (this_type.num_inputs > 0 || this_type.num_outputs > 0))
	{
		opts += Gui::orange_text("Jacks:") + "\n";
		return true;

	} else if (last_type.num_lights == 0 && this_type.num_lights > 0 && this_type.num_params == 0) {
		opts += Gui::orange_text("Lights:") + "\n";
		return true;
	} else {
		return false;
	}
}

} // namespace MetaModule::ModView
