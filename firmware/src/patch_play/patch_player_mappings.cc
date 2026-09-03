#include "patch_play/patch_player.hh"

namespace MetaModule
{

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

		auto *knobconn = map.is_midi_cc()		? &midi_cc_knob_maps[map.cc_num()] :
						 map.is_midi_notegate() ? &midi_note_knob_maps[map.notegate_num()] :
												  nullptr;
		if (!knobconn)
			return;

		auto found = std::ranges::find_if(
			*knobconn, [&map](auto m) { return map.param_id == m.param_id && map.module_id == m.module_id; });

		if (found != knobconn->end()) {
			found->min = map.min;
			found->max = map.max;
			found->curve_type = map.curve_type;
			found->midi_chan = map.midi_chan;
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
			uncache_midi_mapping(map);
			param_watcher.stop_watching_param(map);
		} else {
			uncache_knob_mapping(knobset_id, map);
		}
	}
}

void PatchPlayer::add_midi_mapped_knob(const MappedKnob &map) {
	if (pd.add_update_midi_map(map)) {
		cache_midi_mapping(map);
		param_watcher.start_watching_param(map);
	}
}

void PatchPlayer::add_internal_cable(Jack in, Jack out) {
	pd.add_internal_cable(in, out);
	cables.build(pd.int_cables, core_balancer.cores.parts, modules);
	modules[out.module_id]->mark_output_patched(out.jack_id);
	modules[in.module_id]->mark_input_patched(in.jack_id);
	refresh_conn_flags();
}

void PatchPlayer::add_injack_mapping(uint16_t panel_jack_id, Jack jack) {
	pd.add_mapped_injack(panel_jack_id, jack);

	update_or_add_input_panel_conn(panel_jack_id, jack);

	if (Midi::is_midi_poly_cable(panel_jack_id))
		set_midi_poly_channel_count(pd.midi_poly_num);

	bool panel_patched = false;
	if (panel_jack_id < in_conns.size()) {
		panel_patched = in_patched[panel_jack_id];

		// TODO:
	} else if (panel_jack_id > LastPossibleKnob) {
		panel_patched = midi_connected;
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

void PatchPlayer::safe_unpatch_output(Jack jack) {
	if (jack.module_id < num_modules)
		modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
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

void PatchPlayer::safe_unpatch_input(Jack jack) {
	if (jack.module_id < num_modules)
		modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
}

void PatchPlayer::disconnect_injack(Jack jack) {
	for (auto &ins : in_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_note_pitch_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_note_gate_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_note_vel_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_note_aft_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_cc_conns)
		std::erase(ins, jack);
	for (auto &ins : midi_gate_conns)
		std::erase(ins, jack);
	for (auto &mp : midi_pulses)
		std::erase(mp.conns, jack);
	for (auto &mp : midi_divclk_pulses)
		std::erase(mp.conns, jack);
	for (auto &mp : midi_note_retrig)
		std::erase(mp.conns, jack);

	std::erase(midi_poly_pitch_conns, jack);
	std::erase(midi_poly_gate_conns, jack);
	std::erase(midi_poly_vel_conns, jack);
	std::erase(midi_poly_aft_conns, jack);
	std::erase(midi_poly_retrig.conns, jack);

	safe_unpatch_input(jack);

	// Unpatch the output if the int_cable has no more inputs -- unless that output is still
	// patched to a physical panel/hardware output
	if (auto cable = pd.find_internal_cable_with_injack(jack)) {
		if (cable->ins.size() == 1 && !output_jack_held_by_panel(cable->out)) {
			safe_unpatch_output(cable->out);
		}
	}

	pd.disconnect_injack(jack);

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	refresh_conn_flags();
}

void PatchPlayer::remove_injack_mappings(Jack jack) {
	for (auto &ins : in_conns)
		std::erase(ins, jack);

	if (pd.find_internal_cable_with_injack(jack) == nullptr) {
		// unpatch the module's jack if it has no cables connected
		safe_unpatch_input(jack);
	}

	pd.remove_injack_mappings(jack);

	refresh_conn_flags();
}

void PatchPlayer::disconnect_outjack(Jack jack) {
	for (auto &outs : out_conns) {
		std::erase(outs, jack);
	}
	safe_unpatch_output(jack);

	// Disconnect all inputs
	if (auto cable = pd.find_internal_cable_with_outjack(jack)) {
		for (auto in : cable->ins) {
			safe_unpatch_input(in);
		}
	}

	pd.disconnect_outjack(jack);

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);

	refresh_conn_flags();
}

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

// poly_num is the user setting: 0 = Auto (compute from cables), 1-8 = hard-set
void PatchPlayer::set_midi_poly_num(uint16_t poly_num) {
	pd.midi_poly_num_setting = poly_num;
	pd.update_midi_poly_num();
	set_midi_poly_channel_count(pd.midi_poly_num);
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

} // namespace MetaModule
