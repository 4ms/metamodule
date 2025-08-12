#include "gui/pages/module_view/module_view.hh"

namespace MetaModule
{

void ModuleViewPage::handle_quick_assign() {
	const DrawnElement *current_element = get_highlighted_element();

	if (!current_element) {
		return;
	}

	bool is_param = std::visit(overloaded{
								   [](BaseElement const &el) { return false; },
								   [](ParamElement const &el) { return true; },
								   [](AltParamElement const &el) { return false; },
							   },
							   current_element->element);

	bool is_input_jack = std::holds_alternative<JackInput>(current_element->element);
	bool is_output_jack = std::holds_alternative<JackOutput>(current_element->element);

	bool is_jack = is_input_jack || is_output_jack;

	if (!is_param && !is_jack) {
		return;
	}

	quickmap_rotary_button.register_state(metaparams.rotary_button.is_pressed());

	if (quickmap_rotary_button.is_pressed()) {
		// Parameter quick assign: hold encoder + wiggle knob
		if (is_param) {
			for (unsigned i = 0; auto &knob : params.knobs) {
				if (knob.did_change()) {
					perform_knob_assign(i, current_element);
					roller_hover.force_redraw();
					return;
				}
				i++;
			}

			if (midi_mapping_mode) {

				// Clear all MIDI events when the button is first pressed
				if (quickmap_rotary_button.is_just_pressed()) {
					if (midi_mapping_mode) {
						for (auto &cc : params.midi_ccs)
							cc.changed = false;
						params.last_midi_note.changed = false;
					}
				}

				// MIDI CC quick assign: hold encoder + send MIDI CC
				for (unsigned ccnum = 0; auto &cc : params.midi_ccs) {
					if (cc.changed) {
						cc.changed = 0; // Clear the flag
						perform_midi_assign(MidiCC0 + ccnum, current_element);
						roller_hover.force_redraw();
						return;
					}
					ccnum++;
				}

				// MIDI Note quick assign: hold encoder + send MIDI note
				auto &note = params.last_midi_note;
				if (note.changed) {
					note.changed = 0; // Clear the flag
					perform_midi_assign(MidiGateNote0 + note.val, current_element);
					roller_hover.force_redraw();
					return;
				}

				if (auto motion = metaparams.rotary_pushed.use_motion(); motion != 0) {
					mapping_pane.show_control_popup(group, ui_ElementRollerPanel, *current_element);
					auto newval = lv_arc_get_value(ui_ControlArc) + motion;
					lv_arc_set_value(ui_ControlArc, newval);
					lv_event_send(ui_ControlArc, LV_EVENT_VALUE_CHANGED, nullptr);
				}
			}
		}

		// Jack quick assign: hold encoder + turn encoder
		if (is_jack) {
			if (auto motion = metaparams.rotary_pushed.use_motion(); motion != 0) {
				ElementType jack_type = is_input_jack ? ElementType::Input : ElementType::Output;
				if (cycle_port_selection(motion, jack_type))
					perform_jack_assign(current_element, jack_type);
				roller_hover.force_redraw();
				return;
			}
		}

	} else {
		if (mapping_pane.control_popup_visible()) {
			mapping_pane.hide_control_popup();
		}
	}
}

void ModuleViewPage::handle_encoder_back_removal() {
	const DrawnElement *current_element = get_highlighted_element();

	if (!current_element) {
		return;
	}

	bool is_param = std::visit(overloaded{
								   [](BaseElement const &el) { return false; },
								   [](ParamElement const &el) { return true; },
								   [](AltParamElement const &el) { return false; },
							   },
							   current_element->element);

	bool is_input_jack = std::holds_alternative<JackInput>(current_element->element);
	bool is_output_jack = std::holds_alternative<JackOutput>(current_element->element);
	bool is_jack = is_input_jack || is_output_jack;

	if (is_param) {
		// Remove parameter mappings
		uint16_t module_id = (uint16_t)current_element->gui_element.module_idx;
		uint16_t param_id = (uint16_t)current_element->gui_element.idx.param_idx;
		remove_existing_mappings_for_param(module_id, param_id);

	} else if (is_jack) {
		// Remove jack mappings
		ElementType jack_type = is_input_jack ? ElementType::Input : ElementType::Output;

		Jack module_jack;
		if (jack_type == ElementType::Input) {
			module_jack = {.module_id = (uint16_t)current_element->gui_element.module_idx,
						   .jack_id = (uint16_t)current_element->gui_element.idx.input_idx};
		} else {
			module_jack = {.module_id = (uint16_t)current_element->gui_element.module_idx,
						   .jack_id = (uint16_t)current_element->gui_element.idx.output_idx};
		}

		module_mods.put(RemoveJackMappings{.jack = module_jack, .type = jack_type});
	} else
		return;

	suppress_next_click = true;
	roller_hover.force_redraw();
}

const DrawnElement *ModuleViewPage::get_highlighted_element() {
	if (auto drawn_idx = get_drawn_idx(cur_selected)) {
		return &drawn_elements[*drawn_idx];
	}
	return nullptr;
}

void ModuleViewPage::remove_existing_mappings_for_param(uint16_t module_id, uint16_t param_id) {
	uint32_t target_knobset = page_list.get_active_knobset();

	// Remove ALL existing knob mappings for this parameter in this knobset (non-MIDI)
	if (target_knobset != PatchData::MIDIKnobSet && target_knobset < patch->knob_sets.size()) {
		auto &knobset = patch->knob_sets[target_knobset];

		for (const auto &mapping : knobset.set) {
			if (mapping.module_id == module_id && mapping.param_id == param_id) {
				module_mods.put(RemoveMapping{.map = mapping, .set_id = target_knobset});
			}
		}
	}

	// Remove ALL existing MIDI mappings for this parameter
	auto &midi_knobset = patch->midi_maps.set;
	for (auto &mapping : midi_knobset) {
		if (mapping.module_id == module_id && mapping.param_id == param_id) {
			module_mods.put(RemoveMapping{.map = mapping, .set_id = PatchData::MIDIKnobSet});
		}
	}
}

void ModuleViewPage::perform_knob_assign(uint16_t knob_id, const DrawnElement *element) {
	if (!element) {
		return;
	}

	uint16_t module_id = (uint16_t)element->gui_element.module_idx;
	uint16_t param_id = (uint16_t)element->gui_element.idx.param_idx;

	// Check to see if the knob is already mapped to this parameter
	// Ignore it if so
	for (auto &mapping : patch->knob_sets[page_list.get_active_knobset()].set) {
		if (mapping.panel_knob_id == knob_id && mapping.module_id == module_id && mapping.param_id == param_id) {
			return;
		}
	}

	remove_existing_mappings_for_param(module_id, param_id);

	auto map = MappedKnob{
		.panel_knob_id = knob_id,
		.module_id = module_id,
		.param_id = param_id,
		.min = 0.f,
		.max = 1.f,
	};

	// Queue the modification - this will be processed by handle_patch_mods() which will
	// update the patch data and call refresh() automatically
	uint32_t target_knobset = page_list.get_active_knobset();
	module_mods.put(AddMapping{.map = map, .set_id = target_knobset});

	// Suppress the next click to prevent unwanted mapping pane opening
	suppress_next_click = true;
}

void ModuleViewPage::perform_midi_assign(uint16_t midi_id, const DrawnElement *element) {
	if (!element) {
		return;
	}

	uint16_t module_id = (uint16_t)element->gui_element.module_idx;
	uint16_t param_id = (uint16_t)element->gui_element.idx.param_idx;

	remove_existing_mappings_for_param(module_id, param_id);

	auto map = MappedKnob{
		.panel_knob_id = midi_id,
		.module_id = module_id,
		.param_id = param_id,
		.curve_type = MappedKnob::Normal,
		.midi_chan = 0, // 0 = all channels
		.min = 0.f,
		.max = 1.f,
	};

	module_mods.put(AddMidiMap{.map = map});

	// Suppress the next click to prevent unwanted mapping pane opening
	suppress_next_click = true;
}

bool ModuleViewPage::cycle_port_selection(int motion, ElementType jack_type) {
	if (motion != 1 && motion != -1)
		return false;

	if (jack_type == ElementType::Input) {
		unsigned total_ports = PanelDef::NumUserFacingInJacks;
		if (Expanders::get_connected().ext_audio_connected) {
			total_ports += AudioExpander::NumInJacks;
		}

		selected_input_port = ((int)selected_input_port + motion) % total_ports;

	} else if (jack_type == ElementType::Output) {
		unsigned total_ports = PanelDef::NumUserFacingOutJacks;
		if (Expanders::get_connected().ext_audio_connected) {
			total_ports += AudioExpander::NumOutJacks;
		}

		uint16_t start_port = selected_output_port;

		do {
			selected_output_port = ((int)selected_output_port + motion) % total_ports;

			// Check if this port is available (not already mapped)
			if (!patch->find_mapped_outjack(selected_output_port)) {
				return true;
			}

			// If we've cycled through all options and returned to start, break to avoid infinite loop
			if (selected_output_port == start_port) {
				return false;
			}

		} while (true);
	}
	return true;
}

void ModuleViewPage::perform_jack_assign(const DrawnElement *element, ElementType jack_type) {
	if (!element) {
		return;
	}

	Jack module_jack;
	uint16_t selected_port;

	if (jack_type == ElementType::Input) {
		module_jack = {.module_id = (uint16_t)element->gui_element.module_idx,
					   .jack_id = (uint16_t)element->gui_element.idx.input_idx};
		selected_port = selected_input_port;
	} else {
		module_jack = {.module_id = (uint16_t)element->gui_element.module_idx,
					   .jack_id = (uint16_t)element->gui_element.idx.output_idx};
		selected_port = selected_output_port;
	}

	// Always disconnect existing connection first
	module_mods.put(RemoveJackMappings{.jack = module_jack, .type = jack_type});

	// Create new mapping to the selected port
	AddJackMapping mapping{.panel_jack_id = selected_port, .jack = module_jack, .type = jack_type};

	module_mods.put(mapping);

	// Suppress the next click to prevent unwanted mapping pane opening
	suppress_next_click = true;
}

} // namespace MetaModule
