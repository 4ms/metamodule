#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "conf/panel_conf.hh"
#include "core_a7/smp_api.hh"
#include "drivers/smp.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_play/multicore_play.hh"
#include "pr_dbg.hh"
#include "util/countzip.hh"
#include "util/math.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <vector>

namespace MetaModule
{

class PatchPlayer {

	enum {
		NumInConns = PanelDef::NumUserFacingInJacks,
		NumOutConns = PanelDef::NumUserFacingOutJacks,
	};
	static constexpr size_t MidiPolyphony = 4;

public:
	//TODO: why not use a vector here?
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// out_conns[]: Out1-Out8
	Jack out_conns[NumOutConns] __attribute__((aligned(4))) = {{0, 0}};

	// in_conns[]: In1-In6, GateIn1, GateIn2
	std::array<std::vector<Jack>, NumInConns> in_conns;

	std::array<std::vector<Jack>, MidiPolyphony> midi_note_pitch_conns;
	std::array<std::vector<Jack>, MidiPolyphony> midi_note_gate_conns;
	std::array<std::vector<Jack>, MidiPolyphony> midi_note_vel_conns;
	std::array<std::vector<Jack>, 128> midi_gate_conns;

	// knob_conns[]: ABCDEFuvwxyz, MidiMonoNoteParam, MidiMonoGateParam
	static constexpr size_t NumParams = PanelDef::NumKnobs; // + PanelDef::NumMidiParams;
	using KnobSet = std::array<std::vector<MappedKnob>, NumParams>;

	std::array<KnobSet, MaxKnobSets> knob_conns;

	std::atomic<bool> is_loaded = false;

	MulticorePlayer smp;

private:
	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

	PatchData pd;
	unsigned active_knob_set = 0;
	static inline ModuleTypeSlug no_patch_loaded{"(Not Loaded)"};

public:
	PatchPlayer() {
		clear_cache();
	}

	void copy_patch_data(const PatchData &patchdata) {
		if (is_loaded)
			unload_patch();

		//Copy so that the currently playing PatchData is immune to edits of the saved version
		pd = patchdata;
	}

	// Loads the given patch as the active patch, and caches some pre-calculated values
	bool load_patch(const PatchData &patchdata) {

		if (patchdata.patch_name.length() == 0 || patchdata.module_slugs.size() == 0)
			return false;

		copy_patch_data(patchdata);

		// Tell the other core about the patch
		smp.load_patch(pd.module_slugs.size());

		// First module is the hub, ignore it.
		modules[0] = ModuleFactory::create(PanelDef::typeID);

		for (size_t i = 1; i < pd.module_slugs.size(); i++) {
			modules[i] = ModuleFactory::create(pd.module_slugs[i]);

			if (modules[i] == nullptr) {
				pr_err("Module %s not found\n", pd.module_slugs[i].data());
				is_loaded = false;
				return false;
			}
			pr_trace("Loaded module[%zu]: %s\n", i, pd.module_slugs[i].data());

			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
			modules[i]->set_samplerate(48000.f); //Fixed SR for now
		}

		mark_patched_jacks();
		calc_panel_jack_connections();

		for (auto [knob_set_idx, knob_set] : enumerate(pd.knob_sets)) {
			for (auto const &k : knob_set.set) {
				cache_knob_mapping(knob_set_idx, k);
			}
		}

		// Set static (non-mapped) knobs
		for (auto &k : pd.static_knobs)
			modules[k.module_id]->set_param(k.param_id, k.value);

		for (auto const &ms : pd.module_states) {
			if (ms.module_id >= modules.size())
				continue;

			modules[ms.module_id]->initialize_state(ms.data_json);
		}

		calc_multiple_module_indicies();

		set_active_knob_set(0);

		is_loaded = true;
		return true;
	}

	// Runs the patch
	void update_patch() {
		if (pd.module_slugs.size() == 2)
			modules[1]->update();
		else {
			smp.split();
			for (size_t module_i = 1; module_i < pd.module_slugs.size(); module_i += smp.ModuleStride) {
				modules[module_i]->update();
			}
			smp.join();
		}

		for (auto &cable : pd.int_cables) {
			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);
			for (auto &input_jack : cable.ins) {
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}
	}

	void unload_patch() {
		smp.join();
		is_loaded = false;
		for (size_t i = 0; i < pd.module_slugs.size(); i++) {
			modules[i].reset(nullptr);
		}
		pd.int_cables.clear();
		pd.mapped_ins.clear();
		pd.knob_sets.clear();
		pd.mapped_outs.clear();
		pd.static_knobs.clear();
		pd.module_slugs.clear();

		clear_cache();
	}

	// K-rate setters/getters:

	void set_panel_param(int param_id, float val) {
		for (auto const &k : knob_conns[active_knob_set][param_id]) {
			modules[k.module_id]->set_param(k.param_id, k.get_mapped_val(val));
		}
	}

	void set_all_jacks(std::vector<Jack> const &jacks, float val) {
		for (auto const &jack : jacks)
			modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_panel_input(int jack_id, float val) {
		set_all_jacks(in_conns[jack_id], val);
		// for (auto const &jack : in_conns[jack_id])
		// 	modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_midi_note_pitch(int midi_poly_note, float val) {
		set_all_jacks(midi_note_pitch_conns[midi_poly_note], val);
		// for (auto const &jack : midi_note_pitch_conns[midi_poly_note])
		// 	modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_midi_note_gate(int midi_poly_note, float val) {
		set_all_jacks(midi_note_gate_conns[midi_poly_note], val);
		// for (auto const &jack : midi_note_gate_conns[midi_poly_note])
		// 	modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_midi_note_velocity(int midi_poly_note, float val) {
		set_all_jacks(midi_note_vel_conns[midi_poly_note], val);
		// for (auto const &jack : midi_note_vel_conns[midi_poly_note])
		// 	modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_midi_gate(unsigned note_num, float vel) {
		if (note_num > 127)
			return;

		set_all_jacks(midi_gate_conns[note_num], vel);
	}

	float get_panel_output(int jack_id) {
		auto const &jack = out_conns[jack_id];
		if (jack.module_id > 0)
			return modules[jack.module_id]->get_output(jack.jack_id);
		else
			return 0.f;
	}

	void apply_static_param(const StaticParam &sparam) {
		modules[sparam.module_id]->set_param(sparam.param_id, sparam.value);
		//Also set it in the patch?
	}

	void add_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
		if (pd.add_update_mapped_knob(knobset_id, map)) {
			cache_knob_mapping(knobset_id, map);
		}
	}

	void set_active_knob_set(unsigned num) {
		active_knob_set = std::min(num, MaxKnobSets - 1);
	}

	// General info getters:

	const ModuleTypeSlug &get_patch_name() {
		return is_loaded ? pd.patch_name : no_patch_loaded;
	}

	unsigned get_num_modules() {
		return is_loaded ? pd.module_slugs.size() : 0;
	}

	int get_num_int_cables() {
		return is_loaded ? pd.int_cables.size() : 0;
	}

	unsigned get_num_int_cable_ins(unsigned int_cable_idx) {
		if (int_cable_idx >= pd.int_cables.size())
			return 0;
		return pd.int_cables[int_cable_idx].ins.size();
	}

	// int get_num_mapped_knobs() {
	// 	return is_loaded ? pd.mapped_knobs.size() : 0;
	// }

	const ModuleTypeSlug &get_module_name(unsigned idx) {
		return (is_loaded && idx < pd.module_slugs.size()) ? pd.module_slugs[idx] : no_patch_loaded;
	}

	StaticString<15> const &get_panel_knob_name(int param_id) {
		return pd.knob_sets[active_knob_set].set[param_id].alias_name;
	}

	InternalCable &get_int_cable(unsigned idx) {
		if (idx < pd.int_cables.size())
			return pd.int_cables[idx];
		else
			return pd.int_cables[0]; //error
	}

	// Given the user-facing output jack id (0 = Audio Out L, 1 = Audio Out R, etc)
	// Return the Jack {module_id, jack_id} that it's connected to
	// {0,0} means not connected, or index out of range
	Jack get_panel_output_connection(unsigned jack_id) {
		if (jack_id >= PanelDef::NumUserFacingOutJacks)
			return {.module_id = 0, .jack_id = 0};

		return out_conns[jack_id];
	}

	// Given the user-facing panel input jack id (0 = Audio In L, 1 = Audio In R, etc)
	// return the Jack {module_id, jack_id} that it's connected to.
	// The optional multiple_connection_id is used if multiple jacks are connected to the panel jack (defaults to 0).
	// {0,0} means not connected, or index out of range
	Jack get_panel_input_connection(unsigned jack_id, unsigned multiple_connection_id = 0) {
		// Todo: support multiple jacks connected to one net
		if ((jack_id >= PanelDef::NumUserFacingInJacks) || (multiple_connection_id >= in_conns[jack_id].size()))
			return {.module_id = 0, .jack_id = 0};

		return in_conns[jack_id][multiple_connection_id];
	}

	static constexpr unsigned get_num_panel_knobs() {
		return PanelDef::NumKnobs;
	}
	static constexpr unsigned get_num_panel_inputs() {
		return PanelDef::NumUserFacingOutJacks;
	}
	static constexpr unsigned get_num_panel_outputs() {
		return PanelDef::NumUserFacingInJacks;
	}

	// Jack patched/unpatched status

	void mark_patched_jacks() {
		for (auto const &cable : pd.int_cables) {
			modules[cable.out.module_id]->mark_output_patched(cable.out.jack_id);
			for (auto const &input_jack : cable.ins) {
				if (input_jack.module_id > 0)
					modules[input_jack.module_id]->mark_input_patched(input_jack.jack_id);
			}
		}

		for (auto const &cable : pd.mapped_ins) {
			for (auto const &input_jack : cable.ins) {
				if (input_jack.module_id > 0)
					modules[input_jack.module_id]->mark_input_patched(input_jack.jack_id);
			}
		}
	}

	void set_input_jack_patched_status(int panel_in_jack_id, bool is_patched) {
		if (panel_in_jack_id >= NumInConns)
			return;
		for (auto const &jack : in_conns[panel_in_jack_id]) {
			if (jack.module_id > 0) {
				if (is_patched)
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
			}
		}
	}

	void set_output_jack_patched_status(int panel_out_jack_id, bool is_patched) {
		if (panel_out_jack_id >= NumOutConns)
			return;
		auto const &jack = out_conns[panel_out_jack_id];
		if (jack.module_id > 0) {
			if (is_patched)
				modules[jack.module_id]->mark_output_patched(jack.jack_id);
			else
				modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
		}
	}

	// Cache functions:
	void clear_cache() {
		for (auto &d : dup_module_index)
			d = 0;

		for (auto &out_conn : out_conns)
			out_conn = {0, 0};

		for (auto &in_conn : in_conns)
			in_conn.clear();

		for (auto &knob_set : knob_conns)
			for (auto &mappings : knob_set)
				mappings.clear();
	}

	// Returns the index in int_cables[] for a cable that has the given Jack as an input
	// Return -1 if does not exist
	int find_int_cable_input_jack(Jack in) {
		for (auto [net_i, cable] : enumerate(pd.int_cables)) {
			for (auto &input_jack : cable.ins) {
				if (in == input_jack)
					return net_i;
			}
		}
		return -1;
	}

	// Map all the panel jack connections into in_conns[] and out_conns[]
	// which are indexed by panel_jack_id.
	// This speeds up propagating I/O from user to virtual modules
	void calc_panel_jack_connections() {
		for (auto const &cable : pd.mapped_ins) {
			auto panel_jack_id = cable.panel_jack_id;

			for (auto const &input_jack : cable.ins) {
				if (input_jack.module_id < 0 || input_jack.jack_id < 0)
					break;

				int dup_int_cable = find_int_cable_input_jack(input_jack);
				if (dup_int_cable == -1) {

					if (auto num = cable.midi_note_pitch(); num.has_value()) {
						update_or_add(midi_note_pitch_conns[num.value()], input_jack);
						pr_dbg("MIDI note pitch to jack: m=%d, p=%d\n", input_jack.module_id, input_jack.jack_id);
						continue;
					}

					if (auto num = cable.midi_note_gate(); num.has_value()) {
						update_or_add(midi_note_gate_conns[num.value()], input_jack);
						pr_trace("MIDI gate to jack: m=%d, p=%d\n", input_jack.module_id, input_jack.jack_id);
						continue;
					}

					if (auto num = cable.midi_note_vel(); num.has_value()) {
						update_or_add(midi_note_vel_conns[num.value()], input_jack);
						pr_trace("MIDI vel to jack: m=%d, p=%d\n", input_jack.module_id, input_jack.jack_id);
						continue;
					}

					if (auto num = cable.midi_gate(); num.has_value()) {
						update_or_add(midi_gate_conns[num.value()], input_jack);
						pr_trace("MIDI note %d on/off to gate to jack:  m=%d, p=%d\n",
								 num.value(),
								 input_jack.module_id,
								 input_jack.jack_id);
						continue;
					}

					if (panel_jack_id >= 0 && panel_jack_id < PanelDef::NumUserFacingInJacks) {
						update_or_add(in_conns[panel_jack_id], input_jack);
						continue;
					}

					pr_err("Bad panel jack mapping: panel_jack_id=%d\n", panel_jack_id);
				} else {
					pr_warn("Warning: Outputs are connected: panel_jack_id=%d and int_cable=%d\n",
							panel_jack_id,
							dup_int_cable);
					// TODO: When panel input jack is mapped to a jack containing a cable (to an output)
					// ->>> Create a normalized mapping: Use the int_cable when panel jack is unpatched
				}
			}
		}

		for (auto const &cable : pd.mapped_outs) {
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id < 0 || panel_jack_id >= PanelDef::NumUserFacingOutJacks)
				break;
			out_conns[panel_jack_id] = cable.out;
		}
	}

	template<typename T>
	void update_or_add(std::vector<T> &v, const T &d) {
		for (auto &el : v) {
			if (el == d) { //if (T::operator==(el, d)) {
				el = d;
				return;
			}
		}
		v.push_back(d);
	}

	// Cache a panel knob mapping into knob_conns[]
	void cache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
		if (knob_set >= knob_conns.size())
			return;

		// if (k.is_monophonic_note()) {
		// 	update_or_add(knob_conns[knob_set][MidiMonoNoteParam], k);
		// 	pr_dbg("Mapping midi monophonic note to knob: m=%d, p=%d\n", k.module_id, k.param_id);

		// } else if (k.is_monophonic_gate()) {
		// 	update_or_add(knob_conns[knob_set][MidiMonoGateParam], k);
		// 	pr_dbg("Mapping midi monophonic gate to knob: m=%d, p=%d\n", k.module_id, k.param_id);
		// } else
		if (k.panel_knob_id < PanelDef::NumKnobs) {
			update_or_add(knob_conns[knob_set][k.panel_knob_id], k);
		}
	}

	// Check for multiple instances of same module type, and cache the results
	// This is used to create unique names for modules (e.g. LFO#1, LFO#2,...)
	void calc_multiple_module_indicies() {
		// Todo: this is a naive implementation, perhaps can be made more efficient
		for (size_t i = 0; i < pd.module_slugs.size(); i++) {
			auto &this_slug = pd.module_slugs[i];

			unsigned found = 1;
			unsigned this_index = 0;
			for (size_t j = 0; j < pd.module_slugs.size(); j++) {
				if (i == j) {
					this_index = found;
					continue;
				}
				auto &that_slug = pd.module_slugs[j];
				if (that_slug == this_slug) {
					found++;
				}
			}
			if (found == 1)
				this_index = 0;
			dup_module_index[i] = this_index;
		}
	}

public:
	// Return the mulitple-module-same-type index of the given module index
	// 0 ==> this is the only module of its type
	// >0 ==> a number to append to the module name, e.g. 1 ==> LFO#1, 2 ==> LFO#2, etc
	uint8_t get_multiple_module_index(uint8_t idx) {
		return dup_module_index[idx];
	}
};
} // namespace MetaModule
