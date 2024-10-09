#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "conf/panel_conf.hh"
#include "core_a7/smp_api.hh"
#include "drivers/smp.hh"
#include "null_module.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_play/multicore_play.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include "util/countzip.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <vector>

#include "debug.hh"

namespace MetaModule
{

class PatchPlayer {
public:
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;
	std::atomic<bool> is_loaded = false;

private:
	// Out1-Out8 + Ext Out1-8
	static constexpr auto NumOutJacks = PanelDef::NumUserFacingOutJacks * 2;
	static constexpr auto NumInJacks = PanelDef::NumUserFacingInJacks * 2;

	std::array<Jack, NumOutJacks> out_conns __attribute__((aligned(4))) = {{{0, 0}}};

	// in_conns[]: In1-In6, GateIn1, GateIn2
	std::array<std::vector<Jack>, NumInJacks> in_conns;

	unsigned num_modules = 0;

	// MIDI
	bool midi_connected = false;
	std::array<std::vector<Jack>, MaxMidiPolyphony> midi_note_pitch_conns;
	std::array<std::vector<Jack>, MaxMidiPolyphony> midi_note_gate_conns;
	std::array<std::vector<Jack>, MaxMidiPolyphony> midi_note_vel_conns;
	std::array<std::vector<Jack>, MaxMidiPolyphony> midi_note_aft_conns;
	std::array<std::vector<Jack>, NumMidiCCsPW> midi_cc_conns;
	std::array<std::vector<Jack>, NumMidiNotes> midi_gate_conns;
	std::array<std::vector<MappedKnob>, NumMidiCCs> midi_knob_conns;

	struct MidiPulse {
		OneShot pulse{};
		std::vector<Jack> conns;
	};
	std::array<MidiPulse, 5> midi_pulses;
	std::array<MidiPulse, MaxMidiPolyphony> midi_note_retrig;

	uint32_t midi_divclk_ctr = 0;
	uint32_t midi_divclk_div_amt = 0;

	// knob_conns[]: ABCDEFuvwxyz
	using KnobSet = std::array<std::vector<MappedKnob>, PanelDef::NumKnobs>;
	std::array<KnobSet, MaxKnobSets> knob_conns;

	std::array<bool, NumOutJacks> out_patched{};
	std::array<bool, NumInJacks> in_patched{};

	MulticorePlayer smp;

	float samplerate = 48000.f;

private:
	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	std::array<uint8_t, MAX_MODULES_IN_PATCH> dup_module_index{};

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
	Result load_patch(const PatchData &patchdata) {

		if (patchdata.patch_name.length() == 0)
			return {false, "Cannot load: patch does not have a name"};

		if (patchdata.module_slugs.size() == 0)
			return {false, "Cannot load: patch does not have any modules"};

		copy_patch_data(patchdata);

		num_modules = pd.module_slugs.size();

		if (num_modules > MAX_MODULES_IN_PATCH) {
			return {false, "Too many modules in the patch! Max is 32"};
		}

		// Tell the other core about the patch
		smp.load_patch(num_modules);

		// First module is the hub
		modules[0] = ModuleFactory::create(PanelDef::typeID);

		unsigned num_not_found = 0;
		std::string not_found;
		for (size_t i = 1; i < num_modules; i++) {
			modules[i] = ModuleFactory::create(pd.module_slugs[i]);

			if (modules[i] == nullptr) {
				pr_err("Module %s not found\n", pd.module_slugs[i].data());
				modules[i] = std::make_unique<NullModule>();
				num_not_found++;
				if (num_not_found == 1)
					not_found = std::string_view{pd.module_slugs[i]};
			} else {
				pr_trace("Loaded module[%zu]: %s\n", i, pd.module_slugs[i].data());

				modules[i]->mark_all_inputs_unpatched();
				modules[i]->mark_all_outputs_unpatched();
				modules[i]->set_samplerate(samplerate);
			}
		}

		mark_patched_jacks();
		calc_panel_jack_connections();

		for (auto [knob_set_idx, knob_set] : enumerate(pd.knob_sets)) {
			for (auto const &k : knob_set.set) {
				cache_knob_mapping(knob_set_idx, k);
			}
		}

		pd.update_midi_poly_num();

		for (auto const &mm : pd.midi_maps.set) {
			cache_midi_mapping(mm);
		}

		// Load module states
		for (auto const &ms : pd.module_states) {
			if (ms.module_id >= num_modules)
				continue;

			modules[ms.module_id]->load_state(ms.state_data);
		}

		// Set static (non-mapped) knobs
		for (auto const &k : pd.static_knobs)
			modules[k.module_id]->set_param(k.param_id, k.value);

		calc_multiple_module_indicies();

		set_active_knob_set(0);

		// Test-run the modules once
		for (size_t i = 1; i < num_modules; i++) {
			modules[i]->update();
		}

		is_loaded = true;
		if (num_not_found == 1)
			return {true, std::string{"Module "} + not_found + std::string{" not known, ignoring."}};
		else if (num_not_found > 1)
			return {true,
					std::string{"Module "} + not_found + std::string{" and "} + std::to_string(num_not_found - 1) +
						std::string{" others not known, ignoring."}};

		else
			return {true};
	}

	// Runs the patch
	void update_patch() {
		if (num_modules <= 1)
			return;
		else if (num_modules == 2)
			modules[1]->update();
		else {
			smp.update_modules();
			// Debug::Pin2::high();
			for (size_t module_i = 1; module_i < num_modules; module_i += smp.ModuleStride) {
				modules[module_i]->update();
			}
			// Debug::Pin2::low();
			smp.join();
		}

		for (auto &cable : pd.int_cables) {
			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);
			for (auto &input_jack : cable.ins) {
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}

		update_midi_pulses();
	}

	void update_patch_singlecore() {
		Debug::Pin2::high();
		for (size_t module_i = 1; module_i < num_modules; module_i++) {
			modules[module_i]->update();
		}
		Debug::Pin2::low();

		for (auto &cable : pd.int_cables) {
			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);
			for (auto &input_jack : cable.ins) {
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}

		update_midi_pulses();
	}

	void update_lights() {
		smp.read_patch_state();
		smp.join();
	}

	std::vector<ModuleInitState> get_module_states() {
		std::vector<ModuleInitState> states;
		states.reserve(num_modules);

		for (auto [i, module] : enumerate(modules)) {
			if (i >= num_modules)
				break;
			if (!module)
				continue;
			if (auto state_data = module->save_state(); state_data.size() > 0)
				states.push_back({(uint32_t)i, state_data});
		}

		return states;
	}

	void unload_patch() {
		smp.join();
		is_loaded = false;
		for (size_t i = 0; i < num_modules; i++) {
			modules[i].reset(nullptr);
		}
		pd.int_cables.clear();
		pd.mapped_ins.clear();
		pd.knob_sets.clear();
		pd.mapped_outs.clear();
		pd.static_knobs.clear();
		pd.module_slugs.clear();
		pd.midi_maps.set.clear();
		pd.midi_maps.name = "";

		num_modules = 0;

		clear_cache();
	}

	// K-rate setters/getters:

	void set_panel_param(unsigned param_id, float val) {
		if (param_id < PanelDef::NumKnobs) {
			for (auto const &k : knob_conns[active_knob_set][param_id]) {
				modules[k.module_id]->set_param(k.param_id, k.get_mapped_val(val));
			}
		}
	}

	void set_panel_button(unsigned button_id, bool val) {
		// TODO: button_id is 0-31
	}

	void set_panel_input(unsigned jack_id, float val) {
		set_all_connected_jacks(in_conns[jack_id], val);
	}

	void set_midi_note_pitch(unsigned midi_poly_note, float val) {
		set_all_connected_jacks(midi_note_pitch_conns[midi_poly_note], val);
	}

	void set_midi_note_gate(unsigned midi_poly_note, float val) {
		set_all_connected_jacks(midi_note_gate_conns[midi_poly_note], val);
	}

	void set_midi_note_velocity(unsigned midi_poly_note, float val) {
		set_all_connected_jacks(midi_note_vel_conns[midi_poly_note], val);
	}

	void set_midi_note_aftertouch(unsigned midi_poly_note, float val) {
		set_all_connected_jacks(midi_note_aft_conns[midi_poly_note], val);
	}

	void set_midi_note_retrig(unsigned midi_poly_note, float val) {
		set_all_connected_jacks(midi_note_retrig[midi_poly_note].conns, val);
		midi_note_retrig[midi_poly_note].pulse.start(0.01);
	}

	void set_midi_cc(unsigned ccnum, float val) {
		// Update jacks connected to this CC
		if (ccnum < midi_cc_conns.size())
			set_all_connected_jacks(midi_cc_conns[ccnum], val);

		// Update knobs connected to theis CC
		if (ccnum < midi_knob_conns.size()) {
			for (auto &mm : midi_knob_conns[ccnum]) {
				if (mm.module_id < num_modules)
					modules[mm.module_id]->set_param(mm.param_id, mm.get_mapped_val(val / 10.f));
			}
		}
	}

	void set_midi_gate(unsigned note_num, float val) {
		if (note_num < midi_gate_conns.size())
			set_all_connected_jacks(midi_gate_conns[note_num], val);
	}

	void send_midi_time_event(uint8_t event, float val) {
		if (event > TimingEvents::Cont || event == TimingEvents::DivClock)
			return;

		set_all_connected_jacks(midi_pulses[event].conns, val);
		midi_pulses[event].pulse.start(0.01);

		if (event == TimingEvents::Start) {
			midi_divclk_ctr = 0;
		}

		if (event == TimingEvents::Clock) {
			midi_divclk_ctr++;
			if (midi_divclk_ctr >= midi_divclk_div_amt) {
				set_all_connected_jacks(midi_pulses[TimingEvents::DivClock].conns, val);
				midi_divclk_ctr = 0;
				midi_pulses[TimingEvents::DivClock].pulse.start(0.01);
			}
		}
	}

private:
	void set_all_connected_jacks(std::vector<Jack> const &jacks, float val) {
		for (auto const &jack : jacks)
			modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void update_midi_pulses() {
		for (auto &mp : midi_pulses) {
			if (!mp.pulse.update())
				set_all_connected_jacks(mp.conns, 0);
		}

		for (auto &ret : midi_note_retrig) {
			if (!ret.pulse.update())
				set_all_connected_jacks(ret.conns, 0);
		}
	}

public:
	float get_panel_output(uint32_t jack_id) {
		auto const &jack = out_conns[jack_id];
		if (jack.module_id < num_modules)
			return modules[jack.module_id]->get_output(jack.jack_id);
		else
			return 0.f;
	}

	float get_module_light(uint16_t module_id, uint16_t light_id) const {
		if (is_loaded && module_id < num_modules)
			return modules[module_id]->get_led_brightness(light_id);
		else
			return 0;
	}

	unsigned get_display_text(uint16_t module_id, uint16_t light_id, std::span<char> text) const {
		if (is_loaded && module_id < num_modules)
			return modules[module_id]->get_display_text(light_id, text);
		else
			return 0;
	}

	void set_midi_poly_num(uint32_t poly_num) {
		pd.midi_poly_num = poly_num;
	}

	uint32_t get_midi_poly_num() {
		return pd.midi_poly_num;
	}

	void apply_static_param(const StaticParam &sparam) {
		if (sparam.module_id < num_modules && modules[sparam.module_id])
			modules[sparam.module_id]->set_param(sparam.param_id, sparam.value);
		//Also set it in the patch?
	}

	void add_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
		if (pd.add_update_mapped_knob(knobset_id, map)) {
			cache_knob_mapping(knobset_id, map);
		}
	}

	void edit_mapped_knob(uint32_t knobset_id, const MappedKnob &map, float cur_val) {
		if (knobset_id != PatchData::MIDIKnobSet && knobset_id >= knob_conns.size())
			return;

		auto &knobconn = knobset_id == PatchData::MIDIKnobSet ? midi_knob_conns[map.cc_num()] :
																knob_conns[knobset_id][map.panel_knob_id];

		auto found = std::find_if(knobconn.begin(), knobconn.end(), [&map](auto m) {
			return map.param_id == m.param_id && map.module_id == m.module_id;
		});

		if (found != knobconn.end()) {
			found->min = map.min;
			found->max = map.max;
			found->curve_type = map.curve_type;
			set_panel_param(map.panel_knob_id, cur_val);
		}
	}

	void remove_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
		if (pd.remove_mapping(knobset_id, map)) {
			uncache_knob_mapping(knobset_id, map);
		}
	}

	void add_midi_mapped_knob(const MappedKnob &map) {
		if (pd.add_update_midi_map(map)) {
			cache_midi_mapping(map);
		}
	}

	void set_active_knob_set(unsigned num) {
		active_knob_set = std::min(num, MaxKnobSets - 1);
	}

	void add_internal_cable(Jack in, Jack out) {
		pd.add_internal_cable(in, out);
		modules[out.module_id]->mark_output_patched(out.jack_id);
		modules[in.module_id]->mark_input_patched(in.jack_id);
	}

	void add_injack_mapping(uint16_t panel_jack_id, Jack jack) {
		pd.add_mapped_injack(panel_jack_id, jack);

		update_or_add_input_panel_conn(panel_jack_id, jack);

		bool panel_patched = false;
		if (panel_jack_id < in_conns.size()) {
			panel_patched = in_patched[panel_jack_id];

			// TODO:
		} else if (panel_jack_id > LastPossibleKnob) {
			panel_patched = midi_connected;
		}

		if (panel_patched && jack.module_id < num_modules)
			modules[jack.module_id]->mark_input_patched(jack.jack_id);
	}

	void add_outjack_mapping(uint16_t panel_jack_id, Jack jack) {
		pd.add_mapped_outjack(panel_jack_id, jack);

		if (panel_jack_id < out_conns.size()) {
			out_conns[panel_jack_id] = jack;

			if (out_patched[panel_jack_id] && jack.module_id < num_modules)
				modules[jack.module_id]->mark_output_patched(jack.jack_id);
		}
	}

	void safe_unpatch_output(Jack jack) {
		if (jack.module_id < num_modules)
			modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
	}

	void safe_unpatch_input(Jack jack) {
		if (jack.module_id < num_modules)
			modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
	}

	void disconnect_injack(Jack jack) {
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
		for (auto &mp : midi_note_retrig)
			std::erase(mp.conns, jack);

		safe_unpatch_input(jack);

		// Unpatch the output if the int_cable has no more inputs
		if (auto cable = pd.find_internal_cable_with_injack(jack)) {
			if (cable->ins.size() == 1) {
				safe_unpatch_output(cable->out);
			}
		}

		pd.disconnect_injack(jack);
	}

	void disconnect_outjack(Jack jack) {
		for (auto &out : out_conns) {
			if (out == jack) {
				out = disconnected_jack;
			}
		}
		safe_unpatch_output(jack);

		// Disconnect all inputs
		if (auto cable = pd.find_internal_cable_with_outjack(jack)) {
			for (auto in : cable->ins) {
				safe_unpatch_input(in);
			}
		}

		pd.disconnect_outjack(jack);
	}

	void reset_module(uint16_t module_id) {
		if (module_id < num_modules)
			modules[module_id]->load_state("");
	}

	void add_module(BrandModuleSlug slug) {
		auto module_idx = num_modules;
		pd.module_slugs.push_back(slug);
		calc_multiple_module_indicies();

		modules[module_idx] = ModuleFactory::create(slug);
		if (modules[module_idx] == nullptr) {
			pr_err("Module %s not found\n", slug.c_str());
			return;
		}
		pr_trace("Loaded module[%zu]: %s\n", module_idx, slug.c_str());

		modules[module_idx]->mark_all_inputs_unpatched();
		modules[module_idx]->mark_all_outputs_unpatched();
		modules[module_idx]->set_samplerate(samplerate);

		reset_module(module_idx);

		smp.load_patch(num_modules);
	}

	void remove_module(uint16_t module_idx) {
		// TODO: for all cache structures, if (module_id > deleted_module_idx) module_id -= 1;
		// For testing, we just replace module with a blank and don't touch any indices

		auto squash_module_id = [gap = module_idx](auto &module_id) {
			if (module_id > gap && module_id != disconnected_jack.module_id)
				module_id--;
		};

		auto erase_and_squash = [=](auto &container) {
			for (auto &item : container) {
				std::erase_if(item, [=](auto &map) { return (map.module_id == module_idx); });
				for (auto &map : item) {
					squash_module_id(map.module_id);
				}
			}
		};

		auto erase_and_squash_inner = [=](auto &container) {
			for (auto &item : container) {
				std::erase_if(item.conns, [=](auto &map) { return (map.module_id == module_idx); });
				for (auto &map : item.conns) {
					squash_module_id(map.module_id);
				}
			}
		};

		// Panel Input connections
		erase_and_squash(in_conns);

		// Panel Output connections
		for (auto &out : out_conns) {
			if (out.module_id == module_idx) {
				out = disconnected_jack;
			}
			squash_module_id(out.module_id);
		}

		// Internal cables
		// Inform other modules connected to this one
		// that their jacks are to be disconnected
		for (auto &cable : pd.int_cables) {

			unsigned ins_to_disconnect = 0;
			for (auto in : cable.ins) {

				if (cable.out.module_id == module_idx) {
					modules[in.module_id]->mark_input_unpatched(in.jack_id);
				}

				if (in.module_id == module_idx) {
					ins_to_disconnect++;
				}
			}

			if (ins_to_disconnect == cable.ins.size()) {
				modules[cable.out.module_id]->mark_output_unpatched(cable.out.jack_id);
			}
		}

		// Knob and MIDI connections
		for (auto &knob_set : knob_conns) {
			erase_and_squash(knob_set);
		}

		erase_and_squash(midi_knob_conns);
		erase_and_squash(midi_note_pitch_conns);
		erase_and_squash(midi_note_gate_conns);
		erase_and_squash(midi_note_vel_conns);
		erase_and_squash(midi_note_aft_conns);
		erase_and_squash(midi_cc_conns);
		erase_and_squash(midi_gate_conns);
		erase_and_squash_inner(midi_note_retrig);
		erase_and_squash_inner(midi_pulses);

		pd.remove_module(module_idx);

		std::move(std::next(modules.begin(), module_idx + 1), modules.end(), std::next(modules.begin(), module_idx));

		calc_multiple_module_indicies();

		smp.load_patch(num_modules);
	}

	void set_samplerate(float hz) {
		samplerate = hz;

		for (auto &mp : midi_pulses)
			mp.pulse.set_update_rate_hz(samplerate);

		for (size_t i = 1; i < num_modules; i++) {
			modules[i]->set_samplerate(samplerate);
		}
	}

	// General info getters:

	// Jack patched/unpatched status

	void mark_patched_jacks() {
		for (auto const &cable : pd.int_cables) {
			modules[cable.out.module_id]->mark_output_patched(cable.out.jack_id);
			for (auto const &input_jack : cable.ins) {
				if (input_jack.module_id < num_modules)
					modules[input_jack.module_id]->mark_input_patched(input_jack.jack_id);
			}
		}
	}

	void set_input_jack_patched_status(uint32_t panel_in_jack_id, bool is_patched) {
		if (panel_in_jack_id >= in_conns.size())
			return;

		in_patched[panel_in_jack_id] = is_patched;

		for (auto const &jack : in_conns[panel_in_jack_id]) {
			if (jack.module_id < num_modules) {
				if (is_patched)
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
			}
		}
	}

	void set_output_jack_patched_status(uint32_t panel_out_jack_id, bool is_patched) {
		if (panel_out_jack_id >= out_conns.size())
			return;

		out_patched[panel_out_jack_id] = is_patched;

		auto const &jack = out_conns[panel_out_jack_id];
		if (jack.module_id < num_modules) {
			if (is_patched)
				modules[jack.module_id]->mark_output_patched(jack.jack_id);
			else
				modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
		}
	}

	void set_midi_connected() {
		auto mark_patched = [&](auto const &midi_conns) {
			for (auto const &conn : midi_conns) {
				for (auto const &jack : conn) {
					if (jack.module_id < num_modules)
						modules[jack.module_id]->mark_input_patched(jack.jack_id);
				}
			}
		};
		mark_patched(midi_note_pitch_conns);
		mark_patched(midi_note_gate_conns);
		mark_patched(midi_note_vel_conns);
		mark_patched(midi_note_aft_conns);
		mark_patched(midi_cc_conns);
		mark_patched(midi_gate_conns);

		midi_connected = true;
	}

	void set_midi_disconnected() {
		auto mark_unpatched = [&](auto const &midi_conns) {
			for (auto const &conn : midi_conns) {
				for (auto const &jack : conn) {
					if (jack.module_id < num_modules)
						modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
				}
			}
		};
		mark_unpatched(midi_note_pitch_conns);
		mark_unpatched(midi_note_gate_conns);
		mark_unpatched(midi_note_vel_conns);
		mark_unpatched(midi_note_aft_conns);
		mark_unpatched(midi_cc_conns);
		mark_unpatched(midi_gate_conns);

		midi_connected = false;
	}

private:
	static inline Jack disconnected_jack = {0xFFFF, 0xFFFF};

	// Cache functions:
	void clear_cache() {
		for (auto &d : dup_module_index)
			d = 0;

		for (auto &out_conn : out_conns)
			out_conn = disconnected_jack;

		for (auto &in_conn : in_conns)
			in_conn.clear();

		for (auto &knob_set : knob_conns)
			for (auto &mappings : knob_set)
				mappings.clear();

		for (auto &conn : midi_knob_conns)
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

public:
	// Map all the panel jack connections into in_conns[] and out_conns[]
	// which are indexed by panel_jack_id.
	// This speeds up propagating I/O from user to virtual modules
	void calc_panel_jack_connections() {
		for (auto const &cable : pd.mapped_ins) {
			auto panel_jack_id = cable.panel_jack_id;

			for (auto const &input_jack : cable.ins) {
				auto jack_id = input_jack.jack_id;
				auto module_id = input_jack.module_id;

				if (module_id < 0 || jack_id < 0)
					break;

				int dup_int_cable = find_int_cable_input_jack(input_jack);
				if (dup_int_cable >= 0) {
					pr_warn("Warning: Outputs are connected: panel_jack_id=%d and int_cable=%d\n",
							panel_jack_id,
							dup_int_cable);
					// TODO: When panel input jack is mapped to a jack containing a cable (to an output)
					// ->>> Create a normalized mapping: Use the int_cable when panel jack is unpatched
					continue;
				}

				update_or_add_input_panel_conn(panel_jack_id, input_jack);
				pr_dbg(" to jack: m=%d, p=%d\n", module_id, jack_id);

				// Handle MIDI->Hub and Hub->Hub cables by connecting Hub input to output
				if (input_jack.module_id == 0) {
					out_conns[input_jack.jack_id] = input_jack;
					pr_dbg("Connect hub module out jack %d to panel out %d\n", input_jack.jack_id, input_jack.jack_id);
				}
			}
		}

		for (auto const &cable : pd.mapped_outs) {
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id >= out_conns.size())
				break;
			out_conns[panel_jack_id] = cable.out;
			pr_dbg("Connect module %d out jack %d to panel out %d\n",
				   cable.out.module_id,
				   cable.out.jack_id,
				   panel_jack_id);
		}
	}

	void update_or_add_input_panel_conn(uint32_t panel_jack_id, Jack input_jack) {
		if (auto num = Midi::midi_note_pitch(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_pitch_conns[num.value()], input_jack);
			pr_dbg("MIDI note (poly %d)", num.value());

		} else if (auto num = Midi::midi_note_gate(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_gate_conns[num.value()], input_jack);
			pr_dbg("MIDI gate (poly %d)", num.value());

		} else if (auto num = Midi::midi_note_vel(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_vel_conns[num.value()], input_jack);
			pr_dbg("MIDI vel (poly %d)", num.value());

		} else if (auto num = Midi::midi_note_aft(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_aft_conns[num.value()], input_jack);
			pr_dbg("MIDI aftertouch (poly %d)", num.value());

		} else if (auto num = Midi::midi_note_retrig(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_retrig[num.value()].conns, input_jack);
			pr_dbg("MIDI retrig (poly %d)", num.value());

		} else if (auto num = Midi::midi_gate(panel_jack_id); num.has_value()) {
			update_or_add(midi_gate_conns[num.value()], input_jack);
			pr_dbg("MIDI note %d gate", num.value());

		} else if (auto num = Midi::midi_cc(panel_jack_id); num.has_value()) {
			update_or_add(midi_cc_conns[num.value()], input_jack);
			pr_dbg("MIDI CC/PW %d", num.value());

		} else if (auto num = Midi::midi_clk(panel_jack_id); num.has_value()) {
			update_or_add(midi_pulses[TimingEvents::Clock].conns, input_jack);
			pr_dbg("MIDI Clk");

		} else if (auto num = Midi::midi_divclk(panel_jack_id); num.has_value()) {
			update_or_add(midi_pulses[TimingEvents::DivClock].conns, input_jack);
			midi_divclk_div_amt = num.value() + 1;
			pr_dbg("MIDI Div %d Clk", num.value() + 1);

		} else if (auto num = Midi::midi_transport(panel_jack_id); num.has_value()) {
			update_or_add(midi_pulses[num.value() + TimingEvents::Start].conns, input_jack);
			pr_dbg("MIDI %s", num.value() == 0 ? "Start" : num.value() == 1 ? "Stop" : "Cont");

		} else if (panel_jack_id >= 0 && panel_jack_id < in_conns.size()) {
			update_or_add(in_conns[panel_jack_id], input_jack);
			pr_dbg("Map %d", panel_jack_id);

		} else
			pr_err("Bad panel jack mapping: panel_jack_id=%d", panel_jack_id);
	}

	// Check for multiple instances of same module type, and cache the results
	// This is used to create unique names for modules (e.g. LFO#1, LFO#2,...)
	void calc_multiple_module_indicies() {

		num_modules = pd.module_slugs.size(); //refresh this anytime we are refreshing dup_module_index

		// Todo: this is a naive implementation, perhaps can be made more efficient
		for (size_t i = 0; i < num_modules; i++) {

			unsigned found = 1;
			unsigned this_index = 0;
			for (size_t j = 0; j < num_modules; j++) {
				if (i == j) {
					this_index = found;
					continue;
				}

				auto &this_slug = pd.module_slugs[i];
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

private:
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
		if (k.panel_knob_id < PanelDef::NumKnobs) {
			update_or_add(knob_conns[knob_set][k.panel_knob_id], k);
		}
	}

	//Remove a mapping
	void uncache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
		if (knob_set >= knob_conns.size())
			return;
		if (k.panel_knob_id >= knob_conns[knob_set].size())
			return;
		std::erase_if(knob_conns[knob_set][k.panel_knob_id],
					  [&k](auto m) { return (k.module_id == m.module_id && k.param_id == m.param_id); });
	}

	void cache_midi_mapping(const MappedKnob &k) {
		if (k.is_midi_cc()) {
			pr_dbg("Midi Map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
			update_or_add(midi_knob_conns[k.cc_num()], k);
		} else {
			pr_warn("Bad Midi Map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
		}
	}

	///////////////////////////////////////
#if defined(TESTPROJECT)
public:
	//Used in unit tests
	unsigned get_num_int_cable_ins(unsigned int_cable_idx) {
		if (int_cable_idx >= pd.int_cables.size())
			return 0;
		return pd.int_cables[int_cable_idx].ins.size();
	}

	//Used in unit tests
	InternalCable &get_int_cable(unsigned idx) {
		if (idx < pd.int_cables.size())
			return pd.int_cables[idx];
		else
			return pd.int_cables[0]; //error
	}

	//Used in unit tests
	Jack get_panel_output_connection(unsigned jack_id) {
		if (jack_id >= out_conns.size())
			return {.module_id = 0, .jack_id = 0};

		return out_conns[jack_id];
	}

	//Used in unit tests
	Jack get_panel_input_connection(unsigned jack_id, unsigned multiple_connection_id = 0) {
		if ((jack_id >= in_conns.size()) || (multiple_connection_id >= in_conns[jack_id].size()))
			return {.module_id = 0, .jack_id = 0};

		return in_conns[jack_id][multiple_connection_id];
	}

	// Unit tests:
	// Return the mulitple-module-same-type index of the given module index
	// 0 ==> this is the only module of its type
	// >0 ==> a number to append to the module name, e.g. 1 ==> LFO#1, 2 ==> LFO#2, etc
	uint8_t get_multiple_module_index(uint8_t idx) {
		return dup_module_index[idx];
	}

	auto const &get_inconns() {
		return in_conns;
	}

	auto const &get_outconns() {
		return out_conns;
	}

	auto const &get_knobconns() {
		return knob_conns;
	}

	auto const &get_int_cables() {
		return pd.int_cables;
	}

	auto const &get_modules() {
		return modules;
	}

	auto const &get_module_slugs() {
		return pd.module_slugs;
	}

#endif
};
} // namespace MetaModule
