#include "patch_play/patch_player.hh"

namespace MetaModule
{

//
// Params
//

void PatchPlayer::apply_static_param(const StaticParam &sparam) {
	if (sparam.module_id < num_modules && modules[sparam.module_id])
		modules[sparam.module_id]->set_param(sparam.param_id, sparam.value);
	//Also set it in the patch?
}

void PatchPlayer::add_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
	if (pd.add_update_mapped_knob(knobset_id, map)) {
		cache_knob_mapping(knobset_id, map);
	}
}

void PatchPlayer::edit_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
	if (knobset_id != PatchData::MIDIKnobSet && knobset_id >= knob_maps.size())
		return;

	if (knobset_id == PatchData::MIDIKnobSet) {
		if (!map.is_midi_cc() && !map.is_midi_notegate())
			return;

		if (auto *found = midi.find_knob_map(map)) {
			found->min = map.min;
			found->max = map.max;
			found->curve_type = map.curve_type;
			found->midi_chan = map.midi_chan;
			found->midi_port_mask = map.midi_port_mask;
			if (map.panel_knob_id < PanelDef::NumKnobs)
				catchup_manager.recalc_panel_param(modules, knob_maps[active_knob_set], map.panel_knob_id);
		}

		param_watcher.update_watched_param(map);

	} else {
		auto &knobconn = knob_maps[knobset_id][map.panel_knob_id];
		auto found = std::ranges::find_if(
			knobconn, [&map](auto m) { return map.param_id == m.map.param_id && map.module_id == m.map.module_id; });
		if (found != knobconn.end()) {
			found->map.min = map.min;
			found->map.max = map.max;
			found->map.curve_type = map.curve_type;
			if (map.panel_knob_id < PanelDef::NumKnobs)
				catchup_manager.recalc_panel_param(modules, knob_maps[active_knob_set], map.panel_knob_id);
		}
	}
}

void PatchPlayer::remove_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
	if (pd.remove_mapping(knobset_id, map)) {
		if (knobset_id == PatchData::MIDIKnobSet) {
			midi.uncache_knob_map(map);
			param_watcher.stop_watching_param(map);
			refresh_conn_flags();
		} else {
			uncache_knob_mapping(knobset_id, map);
		}
	}
}

void PatchPlayer::add_midi_mapped_knob(const MappedKnob &map) {
	if (pd.add_update_midi_map(map)) {
		midi.cache_knob_map(map, param_num_positions(map));
		param_watcher.start_watching_param(map);
		refresh_conn_flags();
	}
}

//
// Internal Cables
//

void PatchPlayer::add_internal_cable(Jack in, Jack out) {
	pd.add_internal_cable(in, out);
	cables.build(pd.int_cables, core_balancer.cores.parts, modules);
	modules[out.module_id]->mark_output_patched(out.jack_id);
	modules[in.module_id]->mark_input_patched(in.jack_id);
	refresh_conn_flags();
}

// Removes one input from an internal cable. The cable's other inputs, and any panel
// mappings on either jack, stay connected
void PatchPlayer::remove_internal_cable(Jack out, Jack in) {
	auto cable = pd.find_internal_cable_with_outjack(out);
	if (!cable || std::ranges::find(cable->ins, in) == cable->ins.end())
		return;

	bool const removing_last_input = cable->ins.size() == 1;

	pd.remove_internal_cable(out, in);

	// A panel/MIDI mapping that was summed with this cable is now alone
	route_lone_mapping_directly(in);

	if (!input_jack_has_module_cable(in) && !input_jack_held_by_panel(in))
		safe_unpatch_input(in);

	if (removing_last_input && !output_jack_held_by_panel(out))
		safe_unpatch_output(out);

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	refresh_conn_flags();
}

//
// Panel Jack/MIDI mappings: adding
//

void PatchPlayer::add_injack_mapping(uint32_t panel_jack_id, Jack jack) {
	pd.add_mapped_injack(panel_jack_id, jack);

	update_or_add_input_panel_conn(panel_jack_id, jack);

	if (Midi::is_midi_poly_cable(panel_jack_id))
		midi.set_poly_channel_count(pd.midi_poly_num);

	bool panel_patched = false;
	if (panel_jack_id < in_conns.size()) {
		panel_patched = in_patched[panel_jack_id];

		// TODO:
	} else if (panel_jack_id > LastPossibleKnob) {
		panel_patched = midi.connected;
	}

	if (panel_patched && jack.module_id < num_modules)
		modules[jack.module_id]->mark_input_patched(jack.jack_id);

	refresh_conn_flags();
}

void PatchPlayer::add_outjack_mapping(uint16_t panel_jack_id, Jack jack) {
	pd.add_mapped_outjack(panel_jack_id, jack);

	PolyJack poly_jack{jack};
	poly_jack.buf = plugin_module_get_poly_output_buffer(modules[jack.module_id], jack.jack_id);
	if (panel_jack_id < out_conns.size()) {
		out_conns[panel_jack_id].push_back(poly_jack);

		if (out_patched[panel_jack_id] && jack.module_id < num_modules)
			modules[jack.module_id]->mark_output_patched(jack.jack_id);
	}

	refresh_conn_flags();
}

//
// Panel Jack/MIDI mappings: removing
//

void PatchPlayer::safe_unpatch_input(Jack jack) {
	if (jack.module_id < num_modules)
		modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
}

void PatchPlayer::safe_unpatch_output(Jack jack) {
	if (jack.module_id < num_modules)
		modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
}

// Disconnect all mappings and cables from an input jack
void PatchPlayer::disconnect_injack(Jack jack) {
	for (auto &ins : in_conns)
		std::erase(ins, jack);
	midi.erase_jack(jack);

	safe_unpatch_input(jack);

	// Unpatch each output whose cable has no other inputs -- unless that output is still
	// patched to a physical panel/hardware output
	for (auto const &cable : pd.int_cables) {
		if (cable.ins.size() == 1 && cable.ins[0] == jack && !output_jack_held_by_panel(cable.out))
			safe_unpatch_output(cable.out);
	}

	pd.disconnect_injack(jack);

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	refresh_conn_flags();
}

// Disconnect all mappings and cables from an output jack
void PatchPlayer::disconnect_outjack(Jack jack) {
	for (auto &outs : out_conns) {
		std::erase(outs, jack);
	}
	safe_unpatch_output(jack);

	// Disconnect all inputs
	std::vector<Jack> ins;
	if (auto cable = pd.find_internal_cable_with_outjack(jack))
		ins = cable->ins;

	pd.disconnect_outjack(jack);

	for (auto in : ins) {
		// A panel/MIDI mapping that was summed with this cable is now alone
		route_lone_mapping_directly(in);

		if (!input_jack_has_module_cable(in) && !input_jack_held_by_panel(in))
			safe_unpatch_input(in);
	}

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	refresh_conn_flags();
}

// Remove all mappings to an input jack (leaving internal cables in place)
void PatchPlayer::remove_injack_mappings(Jack jack) {
	pd.remove_injack_mappings(jack);

	// Direct routes: panel or MIDI -> this jack
	for (auto &ins : in_conns)
		std::erase(ins, jack);
	midi.erase_jack(jack);

	// Summed routes: panel or MIDI -> Hub passthrough -> Hub cable -> this jack
	if (remove_hub_cable_with_injack(jack, [](Jack) { return true; }))
		cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	midi.set_poly_channel_count(pd.midi_poly_num);

	// unpatch the module's jack if it has no cables connected
	if (!input_jack_has_module_cable(jack))
		safe_unpatch_input(jack);

	refresh_conn_flags();
}

// Remove all mappings from an out jack (leaving internal cables in place)
void PatchPlayer::remove_outjack_mappings(Jack jack) {
	for (auto &outs : out_conns) {
		std::erase(outs, jack);
	}

	if (pd.find_internal_cable_with_outjack(jack) == nullptr) {
		// unpatch the module's jack if it has no cables connected
		safe_unpatch_output(jack);
	}

	pd.remove_outjack_mappings(jack);

	refresh_conn_flags();
}

// Remove one mapping to an input jack
void PatchPlayer::remove_injack_mapping(uint32_t panel_jack_id, Jack jack) {
	if (!pd.remove_mapped_injack(panel_jack_id, jack))
		return;

	bool const is_midi = Midi::is_midi_panel_id(panel_jack_id);

	// Direct route: panel or MIDI -> this jack
	if (is_midi)
		midi.erase_jack_conn(panel_jack_id, jack);
	else if (panel_jack_id < in_conns.size())
		std::erase(in_conns[panel_jack_id], jack);

	// Summed route: panel or MIDI -> Hub passthrough -> Hub cable -> this jack
	bool cables_changed = remove_hub_cable_with_injack(jack, [&](Jack hub_out) {
		return is_midi ? midi.has_jack_conn(panel_jack_id, hub_out) : hub_out.jack_id == panel_jack_id;
	});

	// If that leaves the jack with one mapping and no module cables, it's no longer summed.
	// Otherwise the remaining Hub cables still work (and are direct again after a patch reload)
	cables_changed |= route_lone_mapping_directly(jack);

	if (cables_changed)
		cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	midi.set_poly_channel_count(pd.midi_poly_num);

	if (!input_jack_has_module_cable(jack) && !input_jack_held_by_panel(jack))
		safe_unpatch_input(jack);

	refresh_conn_flags();
}

// Remove one mapping from an output jack
void PatchPlayer::remove_outjack_mapping(uint16_t panel_jack_id, Jack jack) {
	if (!pd.remove_mapped_outjack(panel_jack_id, jack))
		return;

	if (panel_jack_id < out_conns.size())
		std::erase(out_conns[panel_jack_id], jack);

	if (!pd.find_internal_cable_with_outjack(jack) && !output_jack_held_by_panel(jack))
		safe_unpatch_output(jack);

	refresh_conn_flags();
}

// Removes `jack` from each Hub cable that sums a panel/MIDI input into it,
// if the Hub passthrough jack driving the cable passes the filter.
// A Hub passthrough left with no cable inputs is disconnected from its panel/MIDI input.
// Returns true if any cable changed: the caller must rebuild the cable cache.
bool PatchPlayer::remove_hub_cable_with_injack(Jack jack, auto &&hub_out_filter) {
	bool changed = false;

	for (auto &cable : pd.int_cables) {
		if (cable.out.module_id != 0 || std::ranges::find(cable.ins, jack) == cable.ins.end())
			continue;
		if (!hub_out_filter(cable.out))
			continue;

		std::erase(cable.ins, jack);
		changed = true;

		if (cable.ins.empty()) {
			// Panel passthroughs use the panel jack id as the Hub jack id, MIDI ones use a slot above that
			if (cable.out.jack_id < in_conns.size())
				std::erase(in_conns[cable.out.jack_id], cable.out);
			else
				midi.erase_jack(cable.out);
		}
	}

	if (changed)
		std::erase_if(pd.int_cables, [](auto const &cable) { return cable.ins.empty(); });

	return changed;
}

// Hub cables are only used to sum panel/MIDI mappings with other signals. So when we
// remove other connections, if only a lone hub cable remains, we have to convert it
// back to a normal mapping like calc_panel_jack_connections() would.
// Returns true if any cable changed: the caller must rebuild the cable cache.
bool PatchPlayer::route_lone_mapping_directly(Jack jack) {
	if (jack.module_id == 0 || input_jack_has_module_cable(jack))
		return false;

	MappedInputJack const *lone_map = nullptr;
	for (auto const &map : pd.mapped_ins) {
		if (std::ranges::find(map.ins, jack) != map.ins.end()) {
			if (lone_map)
				return false; // still summing two or more mappings
			lone_map = &map;
		}
	}
	if (!lone_map)
		return false;

	if (!remove_hub_cable_with_injack(jack, [](Jack) { return true; }))
		return false; // already direct

	update_or_add_input_panel_conn(lone_map->panel_jack_id, jack);

	if (Midi::is_midi_poly_cable(lone_map->panel_jack_id))
		midi.set_poly_channel_count(pd.midi_poly_num);

	return true;
}

//
// Helpers
//

void PatchPlayer::update_input_patched_state(Jack jack) {
	if (jack.module_id == 0 || jack.module_id >= num_modules)
		return;

	if (input_jack_has_module_cable(jack) || input_jack_held_by_panel(jack))
		modules[jack.module_id]->mark_input_patched(jack.jack_id);
	else
		modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
}

// Returns the number of poly channels flowing from out jack to in jack,
// or 0 if the connection is mono (or unknowable, e.g. no patch loaded)
unsigned PatchPlayer::num_poly_cable_channels(Jack out, Jack in) {
	if (!is_loaded || out.module_id >= num_modules || in.module_id >= num_modules)
		return 0;

	auto out_buf = plugin_module_get_poly_output_buffer(modules[out.module_id], out.jack_id);
	if (!out_buf.channels || *out_buf.channels <= 1)
		return 0;

	auto in_buf = plugin_module_get_poly_input_buffer(modules[in.module_id], in.jack_id);
	if (!in_buf.channels || *in_buf.channels <= 1)
		return 0;

	return std::min(*out_buf.channels, *in_buf.channels);
}

// True if the jack is mapped to a panel input with a physical cable plugged in, or to MIDI while MIDI is connected
bool PatchPlayer::input_jack_held_by_panel(Jack jack) const {
	for (auto const &map : pd.mapped_ins) {
		if (std::ranges::find(map.ins, jack) == map.ins.end())
			continue;

		if (Midi::is_midi_panel_id(map.panel_jack_id)) {
			if (midi.connected)
				return true;
		} else if (map.panel_jack_id < in_patched.size() && in_patched[map.panel_jack_id])
			return true;
	}
	return false;
}

// True if the jack is driven by another module's output.
// (Ignores the Hub cables that calc_panel_jack_connections() adds to sum panel inputs)
bool PatchPlayer::input_jack_has_module_cable(Jack jack) const {
	return std::ranges::any_of(pd.int_cables, [jack](auto const &cable) {
		return cable.out.module_id != 0 && std::ranges::find(cable.ins, jack) != cable.ins.end();
	});
}

bool PatchPlayer::output_jack_held_by_panel(Jack jack) const {
	for (auto i = 0u; i < out_conns.size(); i++) {
		if (!out_patched[i])
			continue;
		for (auto const &pj : out_conns[i])
			if (pj.module_id == jack.module_id && pj.jack_id == jack.jack_id)
				return true;
	}
	return false;
}

// poly_num is the user setting: 0 = Auto (compute from cables), 1-8 = hard-set
void PatchPlayer::set_midi_poly_num(uint16_t poly_num) {
	pd.midi_poly_num_setting = poly_num;
	pd.update_midi_poly_num();
	midi.set_poly_channel_count(pd.midi_poly_num);
}

} // namespace MetaModule
