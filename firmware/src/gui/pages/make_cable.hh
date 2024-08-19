#pragma once
#include "gui/pages/base.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

inline bool has_connections(PatchData const *patch, Jack jack, ElementType jack_type, bool is_mapped) {
	auto has_int_cable = [&]() {
		if (jack_type == ElementType::Output)
			return patch->find_internal_cable_with_outjack(jack);
		else
			return patch->find_internal_cable_with_injack(jack);
	};

	return (has_int_cable() || is_mapped);
}

inline bool can_finish_cable(GuiState::CableBeginning const &new_cable,
							 bool this_jack_has_connections,
							 ElementType this_jack_type) {
	auto begin_type = new_cable.type;
	auto begin_connected = new_cable.has_connections;
	auto begin_node_has_output = begin_connected || begin_type == ElementType::Output;
	auto this_node_has_output = this_jack_has_connections || this_jack_type == ElementType::Output;
	// Exactly one node can have an output
	bool can_finish_cable_ = this_node_has_output ^ begin_node_has_output;
	return can_finish_cable_;
}

inline bool can_finish_cable(GuiState::CableBeginning const &new_cable,
							 PatchData const *patch,
							 Jack jack,
							 ElementType jack_type,
							 bool is_mapped) {

	return can_finish_cable(new_cable, has_connections(patch, jack, jack_type, is_mapped), jack_type);
}

inline void make_cable(GuiState::CableBeginning &new_cable,
					   PatchData *patch,
					   PatchModQueue &patch_mod_queue,
					   NotificationQueue &notify_queue,
					   Jack this_jack,
					   ElementType this_jack_type) {

	auto begin_jack = new_cable.jack;
	auto begin_jack_type = new_cable.type;

	bool make_panel_mapping = false;

	// Handle case of starting with a PanelIn->In and finishing on an input
	if (begin_jack_type == ElementType::Input && this_jack_type == ElementType::Input) {
		AddJackMapping jackmapping{};
		if (auto panel_jack = patch->find_mapped_injack(begin_jack)) {
			jackmapping.jack = this_jack;
			jackmapping.panel_jack_id = panel_jack->panel_jack_id;
			make_panel_mapping = true;

		} else if (auto panel_jack = patch->find_mapped_injack(this_jack)) {
			jackmapping.jack = begin_jack;
			jackmapping.panel_jack_id = panel_jack->panel_jack_id;
			make_panel_mapping = true;
		}

		if (make_panel_mapping) {
			jackmapping.type = ElementType::Input;
			patch_mod_queue.put(jackmapping);
			notify_queue.put({"Added cable from panel input"});
		}
	}

	if (!make_panel_mapping) {
		AddInternalCable newcable{};
		if (begin_jack_type == ElementType::Input) {
			newcable.in = begin_jack;
			newcable.out = this_jack;
		} else {
			newcable.in = this_jack;
			newcable.out = begin_jack;
		}

		patch_mod_queue.put(newcable);
		notify_queue.put({"Added cable"});
	}
}

} // namespace MetaModule
