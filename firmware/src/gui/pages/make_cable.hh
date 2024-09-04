#pragma once
#include "gui/pages/base.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

inline bool has_connections(PatchData const *patch, Jack jack, ElementType jack_type) {
	if (jack_type == ElementType::Output)
		return patch->find_internal_cable_with_outjack(jack) != nullptr;
	else
		return patch->find_internal_cable_with_injack(jack) != nullptr;
}

inline bool can_finish_cable(ElementType begin_jack_type,
							 bool begin_jack_has_connections,
							 ElementType this_jack_type,
							 bool this_jack_has_connections) {

	auto begin_node_has_output = begin_jack_has_connections || begin_jack_type == ElementType::Output;
	auto this_node_has_output = this_jack_has_connections || this_jack_type == ElementType::Output;

	// XOR: Exactly one node can have an output
	bool can_finish_cable_ = this_node_has_output ^ begin_node_has_output;

	return can_finish_cable_;
}

inline bool can_finish_cable(GuiState::CableBeginning const &new_cable,
							 PatchData const *patch,
							 Jack jack,
							 ElementType jack_type,
							 bool is_mapped) {

	return can_finish_cable(
		new_cable.type, new_cable.has_connections, jack_type, is_mapped || has_connections(patch, jack, jack_type));
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
	// In this case we create a new Panel mapping
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
			if (this_jack_type == ElementType::Output) {
				newcable.in = begin_jack;
				newcable.out = this_jack;
			} else {
				//both are inputss
				newcable.in = this_jack;
				if (auto cable = patch->find_internal_cable_with_injack(begin_jack)) {
					newcable.out = cable->out;
				} else if (auto cable = patch->find_internal_cable_with_injack(this_jack)) {
					newcable.out = cable->out;
				} else {
					notify_queue.put({"Error: cannot connect two inputs", Notification::Priority::Error});
				}
			}
		} else {
			newcable.in = this_jack;
			newcable.out = begin_jack;
		}

		patch_mod_queue.put(newcable);
		notify_queue.put({"Added cable"});
	}
}

inline void abort_cable(GuiState &gui_state, NotificationQueue &notify_queue) {
	if (gui_state.new_cable) {
		gui_state.new_cable = std::nullopt;
		notify_queue.put(Notification{"Cancelled making a cable", Notification::Priority::Info, 1000});
	}
}

} // namespace MetaModule
