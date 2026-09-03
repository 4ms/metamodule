#include "patch_play/patch_player.hh"
#include "util/countzip.hh"

namespace MetaModule
{

void PatchPlayer::clear_cache() {
	for (auto i = 0u; i < dup_module_index.size(); i++) // NOLINT
		dup_module_index[i] = 0;
	// gcc 12.3 complains of writing past end of array
	// when using range-based for loop
	// for (auto &d : dup_module_index)
	// 	d = 0;

	for (auto &out_conn : out_conns)
		out_conn.clear();

	for (auto &in_conn : in_conns)
		in_conn.clear();

	panel_in_vals = {};

	for (auto &knob_set : knob_maps)
		for (auto &mappings : knob_set)
			mappings.clear();

	for (auto &conn : midi_cc_knob_maps)
		conn.clear();
	for (auto &conn : midi_note_knob_maps)
		conn.clear();
	for (auto &conn : midi_note_pitch_conns)
		conn.clear();
	for (auto &conn : midi_note_gate_conns)
		conn.clear();
	for (auto &conn : midi_note_vel_conns)
		conn.clear();
	for (auto &conn : midi_note_aft_conns)
		conn.clear();
	for (auto &ret : midi_note_retrig)
		ret.conns.clear();
	for (auto &conn : midi_cc_conns)
		conn.clear();
	for (auto &conn : midi_gate_conns)
		conn.clear();
	for (auto &mp : midi_pulses)
		mp.conns.clear();
	for (auto &mp : midi_divclk_pulses)
		mp.conns.clear();

	midi_poly_pitch_conns.clear();
	midi_poly_gate_conns.clear();
	midi_poly_vel_conns.clear();
	midi_poly_aft_conns.clear();
	midi_poly_retrig.conns.clear();

	refresh_conn_flags();
}

void PatchPlayer::refresh_conn_flags() {
	// Convert an in_conns[]/out_conns[] index to its jack_senses bit position.
	// Bits 24 is unused in jack_senses, so it's a safe bit to set if an invalid panel idx is given
	auto in_sense_bit = [](unsigned panel_in_idx) {
		return main_jacksense_input_bit(panel_in_idx)
			.value_or(AudioExpander::jacksense_input_bit(panel_in_idx).value_or(24));
	};
	auto out_sense_bit = [](unsigned panel_out_idx) {
		return main_jacksense_output_bit(panel_out_idx)
			.value_or(AudioExpander::jacksense_output_bit(panel_out_idx).value_or(24));
	};

	uint32_t in_mask = 0;
	for (auto i = 0u; i < in_conns.size(); i++) {
		if (!in_conns[i].empty())
			in_mask |= (1u << in_sense_bit(i));
	}

	uint32_t out_mask = 0;
	for (auto i = 0u; i < out_conns.size(); i++) {
		if (!out_conns[i].empty())
			out_mask |= (1u << out_sense_bit(i));

		// Direct panel-in to panel-out passthroughs read panel_in_vals via
		// out_conns and int_cables without an in_conns entry
		for (auto const &pj : out_conns[i]) {
			if (pj.module_id == 0 && pj.jack_id < NumInJacks)
				in_mask |= (1u << in_sense_bit(pj.jack_id));
		}
	}
	for (auto const &cable : pd.int_cables) {
		if (cable.out.module_id == 0 && cable.out.jack_id < NumInJacks)
			in_mask |= (1u << in_sense_bit(cable.out.jack_id));
	}

	used_input_jacks_ = in_mask;
	used_output_jacks_ = out_mask;

	has_knob_maps_ = std::ranges::any_of(knob_maps, [](auto const &param_set) {
		return std::ranges::any_of(param_set, [](auto const &maps) { return !maps.empty(); });
	});

	auto any_conns = [](auto const &pulses) {
		return std::ranges::any_of(pulses, [](auto const &mp) { return !mp.conns.empty(); });
	};
	has_midi_pulse_conns = any_conns(midi_pulses) || any_conns(midi_divclk_pulses) || any_conns(midi_note_retrig) ||
						   !midi_poly_retrig.conns.empty();
}

// Returns the index in int_cables[] for a cable that has the given Jack as an input
// Return -1 if does not exist
int PatchPlayer::find_int_cable_input_jack(Jack in) {
	for (auto [net_i, cable] : enumerate(pd.int_cables)) {
		for (auto &input_jack : cable.ins) {
			if (in == input_jack)
				return net_i;
		}
	}
	return -1;
}

bool PatchPlayer::has_other_mapped_in(Jack j) {
	int found = 0;
	for (auto const &cable : pd.mapped_ins) {
		for (auto const &in : cable.ins) {
			if (in == j) {
				if (++found == 2)
					return true;
			}
		}
	}
	return false;
};

// Map all the panel jack connections into in_conns[] and out_conns[]
// which are indexed by panel_jack_id.
// This speeds up propagating I/O from user to virtual modules
void PatchPlayer::calc_panel_jack_connections() {
	uint16_t next_midi_hub_slot = MidiHubOffset;

	for (auto const &cable : pd.mapped_ins) {
		uint16_t panel_jack_id = cable.panel_jack_id;

		for (auto const &input_jack : cable.ins) {
			auto jack_id = input_jack.jack_id;
			auto module_id = input_jack.module_id;

			if (module_id < 0 || jack_id < 0)
				break;

			if (input_jack.module_id == 0) {
				// mapped_ins->Hub passthrough:
				// MIDI or Panel In (panel_jack_id) -> Panel Out (input_jack.jack_id)
				if (Midi::is_midi_poly_cable(panel_jack_id) || Midi::is_midi_panel_id(panel_jack_id)) {
					// MIDI->Hub passthrough: allocate a unique slot in panel_in_vals
					// The slot index is stored in midi_*_conns[]
					if (next_midi_hub_slot >= PanelInValsSize) {
						pr_err("Too many MIDI-to-Hub connections\n");
						break;
					}
					auto midi_hub_jack = Jack{.module_id = 0, .jack_id = next_midi_hub_slot++};
					update_or_add_input_panel_conn(panel_jack_id, midi_hub_jack);
					pr_trace(" to jack: m=%d, p=%d (passthrough jack)\n", module_id, midi_hub_jack.jack_id);

					// Hub passthrough jack->Panel Out jack:
					out_conns[input_jack.jack_id].push_back({midi_hub_jack, {}});
					pr_trace("Connect MIDI %d to panel out %d via hub\n", panel_jack_id, input_jack.jack_id);
				} else {
					out_conns[input_jack.jack_id].push_back(PolyJack{{0, panel_jack_id}, {}});
					pr_trace("Connect panel in %d to panel out %d\n", panel_jack_id, input_jack.jack_id);
				}

			} else if (find_int_cable_input_jack(input_jack) >= 0 || has_other_mapped_in(input_jack)) {
				// The module input jack also has an internal cable or multiple panel input mappings.
				// In order to sum inputs, we map the panel/MIDI input to the Hub input (passthrough),
				// and then add a second internal cable from Hub output to the
				// original module input jack. Then the summing happens automatically via cable_cache.

				pr_trace("Panel in %d summed to m=%d j=%d\n", panel_jack_id, module_id, jack_id);

				if (Midi::is_midi_poly_cable(panel_jack_id) || Midi::is_midi_panel_id(panel_jack_id)) {
					// MIDI summed with internal cable: allocate a hub slot for the MIDI value
					if (next_midi_hub_slot >= PanelInValsSize) {
						pr_err("Too many MIDI-to-Hub connections\n");
						break;
					}
					auto midi_hub_jack = Jack{.module_id = 0, .jack_id = next_midi_hub_slot++};
					update_or_add_input_panel_conn(panel_jack_id, midi_hub_jack);
					pr_trace(" to hub passthrough slot %d\n", midi_hub_jack.jack_id);

					pd.add_internal_cable(input_jack, midi_hub_jack);
				} else {

					// Connect panel input to hub input:
					update_or_add_input_panel_conn(panel_jack_id, Jack{.module_id = 0, .jack_id = panel_jack_id});
					pr_trace(" to hub passthrough slot %d\n", panel_jack_id);

					// Add cable from hub output to the original panel-mapped jack
					pd.add_internal_cable(input_jack, {.module_id = 0, .jack_id = panel_jack_id});
				}

			} else {
				// Simple connection with no summing — route Panel In directly to module input
				update_or_add_input_panel_conn(panel_jack_id, input_jack);
				pr_trace(" to jack: m=%d, in=%d\n", module_id, jack_id);
			}
		}
	}

	for (auto const &cable : pd.mapped_outs) {
		auto panel_jack_id = cable.panel_jack_id;
		if (panel_jack_id >= out_conns.size())
			break;

		PolyJack poly_jack{cable.out};
		if (cable.out.module_id < num_modules)
			poly_jack.buf = plugin_module_get_poly_output_buffer(modules[cable.out.module_id], cable.out.jack_id);

		out_conns[panel_jack_id].push_back(poly_jack);
		pr_trace(
			"Connect module %d out jack %d to panel out %d\n", cable.out.module_id, cable.out.jack_id, panel_jack_id);
	}

	refresh_conn_flags();
}

void PatchPlayer::update_or_add_input_panel_conn(uint32_t panel_jack_id, Jack input_jack) {
	pr_trace("update_or_add_input_panel_conn: %x\n", panel_jack_id);
	const auto chan = Midi::midi_channel(panel_jack_id);

	const auto polybuf = (input_jack.module_id < num_modules) ?
							 plugin_module_get_poly_input_buffer(modules[input_jack.module_id], input_jack.jack_id) :
							 CoreProcessor::PolyPortBuffer{};

	// The 1-4 and 5-8 poly cables share the same connection vectors; poly_base selects
	// which group of MIDI poly channels (0-3 vs 4-7) the cable carries.
	constexpr uint8_t Base5_8 = Midi::MidiPolyCableChanBase;

	if (Midi::midi_note_pitch_poly(panel_jack_id)) {
		update_or_add_poly(midi_poly_pitch_conns, input_jack, chan, polybuf);
		pr_trace("MIDI note poly ch:%u", chan);

	} else if (Midi::midi_note_pitch_poly5_8(panel_jack_id)) {
		update_or_add_poly(midi_poly_pitch_conns, input_jack, chan, polybuf, Base5_8);
		pr_trace("MIDI note poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_gate_poly(panel_jack_id)) {
		update_or_add_poly(midi_poly_gate_conns, input_jack, chan, polybuf);
		pr_trace("MIDI gate poly ch:%u", chan);

	} else if (Midi::midi_note_gate_poly5_8(panel_jack_id)) {
		update_or_add_poly(midi_poly_gate_conns, input_jack, chan, polybuf, Base5_8);
		pr_trace("MIDI gate poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_vel_poly(panel_jack_id)) {
		update_or_add_poly(midi_poly_vel_conns, input_jack, chan, polybuf);
		pr_trace("MIDI vel poly ch:%u", chan);

	} else if (Midi::midi_note_vel_poly5_8(panel_jack_id)) {
		update_or_add_poly(midi_poly_vel_conns, input_jack, chan, polybuf, Base5_8);
		pr_trace("MIDI vel poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_aft_poly(panel_jack_id)) {
		update_or_add_poly(midi_poly_aft_conns, input_jack, chan, polybuf);
		pr_trace("MIDI aft poly ch:%u", chan);

	} else if (Midi::midi_note_aft_poly5_8(panel_jack_id)) {
		update_or_add_poly(midi_poly_aft_conns, input_jack, chan, polybuf, Base5_8);
		pr_trace("MIDI aft poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_retrig_poly(panel_jack_id)) {
		update_or_add_poly(midi_poly_retrig.conns, input_jack, chan, polybuf);
		pr_trace("MIDI retrig poly ch:%u", chan);

	} else if (Midi::midi_note_retrig_poly5_8(panel_jack_id)) {
		update_or_add_poly(midi_poly_retrig.conns, input_jack, chan, polybuf, Base5_8);
		pr_trace("MIDI retrig poly 5-8 ch:%u", chan);

	} else if (auto num = Midi::midi_note_pitch(panel_jack_id); num.has_value()) {
		update_or_add(midi_note_pitch_conns[num.value()], input_jack, chan);
		pr_trace("MIDI note (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_gate(panel_jack_id); num.has_value()) {
		update_or_add(midi_note_gate_conns[num.value()], input_jack, chan);
		pr_trace("MIDI gate (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_vel(panel_jack_id); num.has_value()) {
		update_or_add(midi_note_vel_conns[num.value()], input_jack, chan);
		pr_trace("MIDI vel (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_aft(panel_jack_id); num.has_value()) {
		update_or_add(midi_note_aft_conns[num.value()], input_jack, chan);
		pr_trace("MIDI aftertouch (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_retrig(panel_jack_id); num.has_value()) {
		update_or_add(midi_note_retrig[num.value()].conns, input_jack, chan);
		pr_trace("MIDI retrig (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_gate(panel_jack_id); num.has_value()) {
		update_or_add(midi_gate_conns[num.value()], input_jack, chan);
		pr_trace("MIDI note %d gate ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_cc(panel_jack_id); num.has_value()) {
		update_or_add(midi_cc_conns[num.value()], input_jack, chan);
		pr_trace("MIDI CC/PW %d ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_clk(panel_jack_id); num.has_value()) {
		update_or_add(midi_pulses[TimingEvents::Clock].conns, input_jack);
		pr_trace("MIDI Clk");

	} else if (auto num = Midi::midi_divclk(panel_jack_id); num.has_value()) {
		uint8_t div_event = *num == 0  ? Midi::DivClock1 :
							*num == 1  ? Midi::DivClock2 :
							*num == 2  ? Midi::DivClock3 :
							*num == 5  ? Midi::DivClock6 :
							*num == 11 ? Midi::DivClock12 :
							*num == 23 ? Midi::DivClock24 :
							*num == 47 ? Midi::DivClock48 :
							*num == 95 ? Midi::DivClock96 :
										 0xFF;
		if (div_event == 0xFF) {
			pr_err("Error: Unknown MIDI clock division: %d. Using /24\n", *num);
			div_event = Midi::DivClock24;
		}
		update_or_add(midi_divclk_pulses[div_event].conns, input_jack);
		pr_trace("MIDI Div %d Clk", num.value() + 1);

	} else if (auto num = Midi::midi_transport(panel_jack_id); num.has_value()) {
		update_or_add(midi_pulses[num.value() + TimingEvents::Start].conns, input_jack);
		pr_trace("MIDI %s", num.value() == 0 ? "Start" : num.value() == 1 ? "Stop" : "Cont");

	} else if (panel_jack_id >= 0 && panel_jack_id < in_conns.size()) {
		update_or_add(in_conns[panel_jack_id], input_jack);
		pr_trace("Map %d", panel_jack_id);

	} else
		pr_err("Bad panel jack mapping: panel_jack_id=%d", panel_jack_id);
}

void PatchPlayer::update_or_add(std::vector<Jack> &v, const Jack &d) {
	if (auto found = std::ranges::find(v, d); found == v.end())
		v.push_back(d);
}

void PatchPlayer::update_or_add(std::vector<MappedKnob> &v, const MappedKnob &d) {
	for (auto &el : v) {
		if (el.maps_to_same_as(d)) {
			el = d;
			return;
		}
	}
	v.push_back(d);
}

template<typename T>
void PatchPlayer::update_or_add(std::vector<T> &v, const Jack &d, uint32_t midi_chan)
	requires std::derived_from<T, JackMidi>
{
	for (auto &el : v) {
		if (el.module_id == d.module_id && el.jack_id == d.jack_id) {
			el.midi_chan = midi_chan;
			return;
		}
	}
	T entry{};
	static_cast<Jack &>(entry) = d;
	entry.midi_chan = midi_chan;
	v.push_back(entry);
}

void PatchPlayer::update_or_add_poly(std::vector<PolyJackMidi> &v,
									 const Jack &d,
									 uint32_t midi_chan,
									 CoreProcessor::PolyPortBuffer buf,
									 uint8_t poly_base) {
	for (auto &el : v) {
		if (el.module_id == d.module_id && el.jack_id == d.jack_id) {
			el.midi_chan = midi_chan;
			el.buf = buf;
			el.poly_base = poly_base;
			return;
		}
	}
	PolyJackMidi entry{};
	static_cast<Jack &>(entry) = d;
	entry.midi_chan = midi_chan;
	entry.buf = buf;
	entry.poly_base = poly_base;
	v.push_back(entry);
}

// Cache a panel knob mapping into knob_conns[]
void PatchPlayer::cache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
	if (knob_set >= knob_maps.size())
		return;

	if (k.is_panel_knob() || k.is_button()) {
		// Update existing, if present
		for (auto &el : knob_maps[knob_set][k.panel_knob_id]) {
			if (el.map.maps_to_same_as(k)) {
				el.map = k;
				return;
			}
		}
		// Create new entry:
		CatchupParam f{};
		f.mode = catchup_manager.get_default_mode();
		knob_maps[knob_set][k.panel_knob_id].push_back({k, f});
		refresh_conn_flags();
	} else
		pr_err("Cannot map panel knob id %u\n", k.panel_knob_id);
}

//Remove a mapping
void PatchPlayer::uncache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
	if (knob_set >= knob_maps.size())
		return;
	if (k.panel_knob_id >= knob_maps[knob_set].size())
		return;
	std::erase_if(knob_maps[knob_set][k.panel_knob_id], [&k](auto m) { return (k.maps_to_same_as(m.map)); });
	refresh_conn_flags();
}

void PatchPlayer::cache_midi_mapping(const MappedKnob &k) {
	if (k.is_midi_cc()) {
		pr_trace("Midi Map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
		update_or_add(midi_cc_knob_maps[k.cc_num()], k);

	} else if (k.is_midi_notegate()) {
		pr_trace("Midi Map: Note %d to m:%d p:%d\n", k.notegate_num(), k.module_id, k.param_id);
		update_or_add(midi_note_knob_maps[k.notegate_num()], k);

	} else {
		pr_warn("Bad Midi Map: panel_knob_id:%d to m:%d p:%d\n", k.panel_knob_id, k.module_id, k.param_id);
	}
}

void PatchPlayer::uncache_midi_mapping(const MappedKnob &k) {
	if (k.is_midi_cc()) {
		pr_trace("Midi un-map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
		std::erase_if(midi_cc_knob_maps[k.cc_num()], [&k](auto m) { return (k.maps_to_same_as(m)); });

	} else if (k.is_midi_notegate()) {
		pr_trace("Midi un-map: Note %d to m:%d p:%d\n", k.notegate_num(), k.module_id, k.param_id);
		std::erase_if(midi_note_knob_maps[k.notegate_num()], [&k](auto m) { return (k.maps_to_same_as(m)); });

	} else {
		pr_warn("Cannot unmap MIDI: raw panel_knob_id:%d to m:%d p:%d\n", k.panel_knob_id, k.module_id, k.param_id);
	}
}

} // namespace MetaModule
