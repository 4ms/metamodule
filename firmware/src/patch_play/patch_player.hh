#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/hub/audio_expander_defs.hh"
#include "CoreModules/moduleFactory.hh"
#include "conf/patch_conf.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "delay.hh"
#include "drivers/cache.hh"
#include "null_module.hh"
#include "params/catchup_manager.hh"
#include "params/catchup_param.hh"
#include "params/midi_params.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_play/balance_modules.hh"
#include "patch_play/cable_cache.hh"
#include "patch_play/multicore_play.hh"
#include "patch_play/patch_player_query_patch.hh"
#include "patch_play/plugin_module.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include "util/countzip.hh"
#include "util/oscs.hh"
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <string_view>
#include <vector>

#include "debug.hh"
#include "util/zip.hh"

namespace MetaModule
{

class PatchPlayer {
public:
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;
	CableCache<MulticorePlayer::NumCores> cables;

	unsigned num_modules = 0;
	std::atomic<bool> is_loaded = false;

	PatchQuery patch_query{modules, pd};

private:
	// Out1-Out8 + Ext Out1-8
	static constexpr auto NumOutJacks = PanelDef::NumUserFacingOutJacks + AudioExpander::NumOutJacks;
	static constexpr auto NumInJacks = PanelDef::NumUserFacingInJacks + AudioExpander::NumInJacks;

	std::array<Jack, NumOutJacks> out_conns __attribute__((aligned(4))) = {{{0, 0}}};

	// in_conns[]: In1-In6, GateIn1, GateIn2, ExpIn7-12
	std::array<std::vector<Jack>, NumInJacks> in_conns;

	// MIDI
	bool midi_connected = false;

	struct JackMidi : Jack {
		uint32_t midi_chan = 0; //0: Omni
	};
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> midi_note_pitch_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> midi_note_gate_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> midi_note_vel_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> midi_note_aft_conns;
	std::array<std::vector<JackMidi>, NumMidiCCsPW> midi_cc_conns;
	std::array<std::vector<JackMidi>, NumMidiNotes> midi_gate_conns;

	std::array<std::vector<MappedKnob>, NumMidiCCs> midi_cc_knob_maps;
	std::array<std::vector<MappedKnob>, NumMidiNotes> midi_note_knob_maps;

	struct MidiPulse {
		OneShot pulse{};
		std::vector<JackMidi> conns;
	};
	struct MidiPulseDivider {
		OneShot pulse{};
		std::vector<Jack> conns;
		uint32_t midi_divclk_ctr = 0;
	};
	std::array<MidiPulse, TimingEvents::NumTimingEvents> midi_pulses;
	std::array<MidiPulseDivider, Midi::NumDivClocks> midi_divclk_pulses;

	std::array<MidiPulse, MaxMidiPolyphony> midi_note_retrig;

	std::array<ParamSet, MaxKnobSets> knob_maps;
	CatchupManager catchup_manager;

	std::array<bool, NumOutJacks> out_patched{};
	std::array<bool, NumInJacks> in_patched{};

	MulticorePlayer smp;
	Balancer<MulticorePlayer::NumCores, MAX_MODULES_IN_PATCH> core_balancer;

	float samplerate = 48000.f;

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

public:
	// Loads the given patch as the active patch, and caches some pre-calculated values
	Result load_patch(const PatchData &patchdata) {

		// load_patch must only be called from the GUI context -- which ASyncThreads will interrupt
		// Otherwise, if load_patch is interrupting an AsyncThread, then the AsyncThread
		// will crash since its module * is no longer valid
		pause_module_threads();

		if (patchdata.patch_name.length() == 0)
			return {false, "Cannot load: patch does not have a name"};

		if (patchdata.module_slugs.size() == 0)
			return {false, "Cannot load: patch does not have any modules"};

		copy_patch_data(patchdata);

		num_modules = pd.module_slugs.size();

		if (num_modules > MAX_MODULES_IN_PATCH) {
			return {false, "Too many modules in the patch! Max is 64"};
		}

		// First module is the hub
		modules[0] = ModuleFactory::create(PanelDef::typeID);
		if (modules[0] != nullptr)
			modules[0]->id = 0;

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

				modules[i]->id = i;
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

		active_knob_set = 0;
		catchup_manager.reset(modules, knob_maps[active_knob_set]);

		rebalance_modules();

		cables.build(pd.int_cables, core_balancer.cores.parts);

		resume_module_threads();
		delay_ms(2); // Allow threads to start

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

	void rebalance_modules() {
		auto cpu_times = core_balancer.measure_modules(
			modules, num_modules, [this](unsigned module_i) { step_module(module_i, 1); });

		core_balancer.balance_loads(cpu_times);

		core_balancer.print_times(cpu_times, pd.module_slugs);

		// Tell other SMP core which modules it's been assigned
		smp.assign_modules(core_balancer.cores.parts[MulticorePlayer::NumCores - 1]);

		for (auto core_id = 0u; core_id < core_balancer.cores.parts.size(); core_id++) {
			for (auto id : core_balancer.cores.parts[core_id]) {
				peg_task_to_core(id, core_id);
			}
		}
	}

	// Runs the patch
	void update_patch() {
		if (num_modules == 2)
			modules[1]->update();

		else if (num_modules > 2) {
			smp.update_modules();
			for (auto module_i : core_balancer.cores.parts[0]) {
				Debug::Pin0::high();
				process_module_outputs(module_i, 0);
				Debug::Pin0::low();
			}
			for (auto module_i : core_balancer.cores.parts[0]) {
				step_module(module_i, 0);
			}
			smp.join();
		} else
			return;

		update_midi_pulses();
	}

	// Inval each out.val, no DMB: 72-73% [sounds good]
	// Inval each out.val, DMB after: 72-73% [sounds good]
	// Inval each out.val: 73-74% [sounds good]
	// Inval before, clean after: 73-75 [sounds good]

	// Inval range and single DMB before only: 70% [sounds good]  <<<<<<<<<

	// Clean after only: 64-67% [sounds bad]
	// Neither: 59-61% [sounds bad]
	void process_module_outputs(unsigned module_i, unsigned core) {
		auto *startaddr = cables.outvals[core].data();
		mdrivlib::SystemCache::invalidate_dcache_by_addr_fast(startaddr);

		for (auto [val, jack] : zip(cables.outvals[core], cables.outjacks[core])) {
			val = modules[jack.module_id_only()]->get_output(jack.jack_id);
			// if (jack.is_tagged())
			// 	mdrivlib::SystemCache::invalidate_dcache_by_addr_fast(&val);
		}

		// mdrivlib::SystemCache::invalidate_dcache_by_range(cables.outs[module_i].data(), cables.outs[module_i].size());

		// for (auto &out : cables.outs[module_i]) {
		// 	// mdrivlib::SystemCache::invalidate_dcache_by_addr_fast(&out.val);
		// 	out.val = modules[module_i]->get_output(out.jack_id);
		// 	mdrivlib::SystemCache::clean_dcache_by_addr_fast(&out.val);
		// }

		// mdrivlib::SystemCache::mem_barrier();
	}

	// None above and
	// Clean before: 63-65% sounds bad
	// Inval before: 69% sounds bad
	void step_module(unsigned module_i, unsigned core) {
		// if (core == 0)
		// 	Debug::Pin1::high();
		for (auto const &in : cables.ins[module_i]) {
			modules[module_i]->set_input(in.jack_id, *in.outval);
		}
		// if (core == 0)
		// 	Debug::Pin1::low();

		modules[module_i]->update();
	}

	void update_patch_singlecore() {
		for (size_t module_i = 1; module_i < num_modules; module_i++) {
			step_module(module_i, 0);
		}
		update_midi_pulses();
	}

	void trigger_reading_gui_elements() {
		smp.read_patch_gui_elements();
		smp.join();
	}

	void unload_patch() {
		smp.join();
		is_loaded = false;
		for (size_t i = 0; i < num_modules; i++) {
			plugin_module_deinit(modules[i]);
			modules[i].reset(nullptr);
		}
		cables.clear();
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

	// Interface with audio stream:

	void set_panel_param(unsigned panel_knob_id, float val) {
		catchup_manager.set_panel_param(modules, knob_maps[active_knob_set], panel_knob_id, val);
	}

	void set_panel_param_no_play(unsigned panel_knob_id, float val) {
		catchup_manager.set_panel_param_no_play(panel_knob_id, val);
	}

	void set_panel_input(unsigned jack_id, float val) {
		set_all_connected_jacks(in_conns[jack_id], val);
	}

	void set_active_knob_set(unsigned num) {
		auto new_active_knob_set = std::min(num, MaxKnobSets - 1);

		if (active_knob_set != new_active_knob_set) {
			active_knob_set = new_active_knob_set;

			catchup_manager.reset(modules, knob_maps[active_knob_set]);
		}
	}

	void set_midi_note_pitch(unsigned midi_poly_note, float val, uint16_t midi_chan) {
		set_all_connected_jacks(midi_note_pitch_conns[midi_poly_note], val, midi_chan);
	}

	void set_midi_note_gate(unsigned midi_poly_note, float val, uint16_t midi_chan) {
		set_all_connected_jacks(midi_note_gate_conns[midi_poly_note], val, midi_chan);
	}

	void set_midi_note_velocity(unsigned midi_poly_note, int16_t val, uint16_t midi_chan) {
		set_all_connected_jacks(midi_note_vel_conns[midi_poly_note], float(val) / 12.7f, midi_chan);
	}

	void set_midi_note_aftertouch(unsigned midi_poly_note, int16_t val, uint16_t midi_chan) {
		set_all_connected_jacks(midi_note_aft_conns[midi_poly_note], float(val) / 12.7f, midi_chan);
	}

	void set_midi_note_retrig(unsigned midi_poly_note, float val, uint16_t midi_chan) {
		set_all_connected_jacks(midi_note_retrig[midi_poly_note].conns, val, midi_chan);
		midi_note_retrig[midi_poly_note].pulse.start(0.01);
	}

	void set_midi_cc(unsigned ccnum, int16_t val, uint16_t midi_chan) {
		float volts = ccnum == Midi::PitchBendCC ? Midi::s14_to_semitones<2>(val) : val / 12.7f; //0-127 => 0-10

		// Update jacks connected to this CC
		if (ccnum < midi_cc_conns.size()) {
			set_all_connected_jacks(midi_cc_conns[ccnum], volts, midi_chan);
		}

		// Update knobs connected to this CC
		if (ccnum < midi_cc_knob_maps.size()) {
			for (auto &mm : midi_cc_knob_maps[ccnum]) {
				if (mm.module_id < num_modules) {
					if (mm.midi_chan == 0 || mm.midi_chan == (midi_chan + 1)) {
						modules[mm.module_id]->set_param(mm.param_id, mm.get_mapped_val(volts / 10.f)); //0V-10V => 0-1
					}
				}
			}
		}
	}

	void set_midi_gate(unsigned note_num, float volts, uint16_t midi_chan) {
		if (note_num < midi_gate_conns.size())
			set_all_connected_jacks(midi_gate_conns[note_num], volts, midi_chan);

		if (note_num >= midi_note_knob_maps.size())
			return;

		for (auto &mm : midi_note_knob_maps[note_num]) {
			if (mm.module_id >= num_modules)
				continue;

			if (mm.midi_chan > 0 && mm.midi_chan != (midi_chan + 1))
				continue;

			auto normal_val = volts / 10.f;
			if (mm.curve_type == MappedKnob::CurveType::Toggle) {
				// Latching: toggle
				if (normal_val > 0.5f) { //rising edge
					auto cur_val = modules[mm.module_id]->get_param(mm.param_id);

					// if param is currently closer to min, then set it to max (and vice-versa)
					if (std::abs(cur_val - mm.min) < std::abs(cur_val - mm.max)) {
						modules[mm.module_id]->set_param(mm.param_id, mm.max);
					} else {
						modules[mm.module_id]->set_param(mm.param_id, mm.min);
					}
				}

			} else {
				// Momentary (follow)
				modules[mm.module_id]->set_param(mm.param_id, mm.get_mapped_val(normal_val));
			}
		}
	}

	// Event must be either Clock, or Start, Stop, or Cont.
	// Div clocks are calculated here on each Clock event
	void send_midi_time_event(uint8_t event, float val) {
		if (event == TimingEvents::Cont || event == TimingEvents::Stop || event == TimingEvents::Start ||
			event == TimingEvents::Clock)
		{

			set_all_connected_jacks(midi_pulses[event].conns, val);
			midi_pulses[event].pulse.start(0.01);
		}

		if (event == TimingEvents::Start) {
			midi_divclocks_reset();
		}

		// Handle DivClocks
		if (event == TimingEvents::Clock) {
			unsigned idx = 0;
			for (auto &midi_divclk_pulse : midi_divclk_pulses) {
				midi_divclk_pulse.midi_divclk_ctr++;
				if (midi_divclk_pulse.midi_divclk_ctr >= Midi::DivClockAmt[idx]) {
					midi_divclk_pulse.midi_divclk_ctr = 0;
					midi_divclk_pulse.pulse.start(0.01);
					set_all_connected_jacks(midi_divclk_pulse.conns, val);
				}
				idx++;
			}
		}
	}

	void midi_divclocks_reset() {
		// Reset all clock counters on Start event
		for (auto &midi_divclk_pulse : midi_divclk_pulses) {
			midi_divclk_pulse.midi_divclk_ctr = 0;
		}
	}

	void set_samplerate(float hz) {
		samplerate = hz;

		for (auto &mp : midi_pulses)
			mp.pulse.set_update_rate_hz(samplerate);

		for (auto &mp : midi_divclk_pulses)
			mp.pulse.set_update_rate_hz(samplerate);

		for (size_t i = 1; i < num_modules; i++) {
			modules[i]->set_samplerate(samplerate);
		}
	}

private:
	template<typename JackT>
	void set_all_connected_jacks(std::vector<JackT> const &jacks, float val) {
		for (auto const &jack : jacks)
			modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	void set_all_connected_jacks(std::vector<JackMidi> const &jacks, float val, uint32_t midi_chan) {
		for (auto const &jack : jacks) {
			if (jack.midi_chan == 0 || jack.midi_chan == (midi_chan + 1))
				modules[jack.module_id]->set_input(jack.jack_id, val);
		}
	}

	void update_midi_pulses() {
		for (auto &mp : midi_pulses) {
			if (!mp.pulse.update()) {
				set_all_connected_jacks(mp.conns, 0);
			}
		}

		for (auto &mp : midi_divclk_pulses) {
			if (!mp.pulse.update()) {
				set_all_connected_jacks(mp.conns, 0);
			}
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

	float get_param(uint16_t module_id, uint16_t param_id) const {
		if (is_loaded && module_id < num_modules)
			return modules[module_id]->get_param(param_id);
		else
			return 0;
	}

	void set_midi_poly_num(uint32_t poly_num) {
		pd.midi_poly_num = poly_num;
	}

	uint32_t get_midi_poly_num() {
		return pd.midi_poly_num;
	}

	// Patch Mods:

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

	void edit_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
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

		} else {
			auto &knobconn = knob_maps[knobset_id][map.panel_knob_id];
			auto found = std::ranges::find_if(knobconn, [&map](auto m) {
				return map.param_id == m.map.param_id && map.module_id == m.map.module_id;
			});
			if (found != knobconn.end()) {
				found->map.min = map.min;
				found->map.max = map.max;
				found->map.curve_type = map.curve_type;
				if (map.panel_knob_id < PanelDef::NumKnobs)
					catchup_manager.recalc_panel_param(modules, knob_maps[active_knob_set], map.panel_knob_id);
			}
		}
	}

	void remove_mapped_knob(uint32_t knobset_id, const MappedKnob &map) {
		if (pd.remove_mapping(knobset_id, map)) {
			if (knobset_id == PatchData::MIDIKnobSet)
				uncache_midi_mapping(map);
			else
				uncache_knob_mapping(knobset_id, map);
		}
	}

	void add_midi_mapped_knob(const MappedKnob &map) {
		if (pd.add_update_midi_map(map)) {
			cache_midi_mapping(map);
		}
	}

	void add_internal_cable(Jack in, Jack out) {
		pd.add_internal_cable(in, out);
		cables.add(in, out, core_balancer.cores.parts);
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
		for (auto &mp : midi_divclk_pulses)
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

		cables.build(pd.int_cables, core_balancer.cores.parts);
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

		cables.build(pd.int_cables, core_balancer.cores.parts);
	}

	void reset_module(uint16_t module_id, std::string_view data = "") {
		if (module_id < num_modules)
			modules[module_id]->load_state(data);
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

		modules[module_idx]->id = module_idx;
		modules[module_idx]->mark_all_inputs_unpatched();
		modules[module_idx]->mark_all_outputs_unpatched();
		modules[module_idx]->set_samplerate(samplerate);

		reset_module(module_idx);

		rebalance_modules();
	}

	void remove_module(uint16_t module_idx) {
		// For all cache structures, if (module_id > deleted_module_idx) module_id -= 1;

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
		for (auto &param_set : knob_maps) {
			// erase_and_squash(knob_set);
			for (auto &set : param_set) {
				std::erase_if(set, [=](auto &map) { return (map.map.module_id == module_idx); });
				for (auto &map : set) {
					squash_module_id(map.map.module_id);
				}
			}
		}

		erase_and_squash(midi_cc_knob_maps);
		erase_and_squash(midi_note_knob_maps);
		erase_and_squash(midi_note_pitch_conns);
		erase_and_squash(midi_note_gate_conns);
		erase_and_squash(midi_note_vel_conns);
		erase_and_squash(midi_note_aft_conns);
		erase_and_squash(midi_cc_conns);
		erase_and_squash(midi_gate_conns);
		erase_and_squash_inner(midi_note_retrig);
		erase_and_squash_inner(midi_pulses);
		erase_and_squash_inner(midi_divclk_pulses);

		pd.remove_module(module_idx);

		plugin_module_deinit(modules[module_idx]);
		modules[module_idx].reset();

		// Move [i+1...end) to i
		std::move(std::next(modules.begin(), module_idx + 1), modules.end(), std::next(modules.begin(), module_idx));

		calc_multiple_module_indicies();

		for (auto i = 0u; i < num_modules; i++) {
			if (modules[i])
				modules[i]->id = i;
		}

		rebalance_modules();
	}

	// General info getters:

	// Jack patched/unpatched status

	// Follow every internal cable and tell the modules that their jacks are patched
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
			// Don't mark the virtual module jack unpatched/patched
			// if there is an existing internal cable
			if (!pd.find_internal_cable_with_outjack(jack)) {
				if (is_patched)
					modules[jack.module_id]->mark_output_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
			}
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

		for (auto const &conn : midi_pulses) {
			for (auto const &jack : conn.conns) {
				if (jack.module_id < num_modules) {
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
				}
			}
		}
		for (auto const &conn : midi_divclk_pulses) {
			for (auto const &jack : conn.conns) {
				if (jack.module_id < num_modules) {
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
				}
			}
		}

		midi_divclocks_reset();

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

		for (auto const &conn : midi_pulses) {
			for (auto const &jack : conn.conns) {
				if (jack.module_id < num_modules) {
					modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
				}
			}
		}
		for (auto const &conn : midi_divclk_pulses) {
			for (auto const &jack : conn.conns) {
				if (jack.module_id < num_modules) {
					modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
				}
			}
		}

		midi_connected = false;
	}

	// Set mode for all maps
	void set_catchup_mode(CatchupParam::Mode mode, bool allow_jump_outofrange);

	// Set mode for one mapping only
	void set_catchup_mode(int knob_set_idx, unsigned module_id, unsigned param_id, CatchupParam::Mode mode);

	// Set mode for one module/param, in any knobset
	void set_catchup_mode(unsigned module_id, unsigned param_id, CatchupParam::Mode mode);

	bool is_param_tracking(unsigned module_id, unsigned param_id);

	std::optional<unsigned> panel_knob_catchup_inaccessible();

private:
	static inline Jack disconnected_jack = {0xFFFF, 0xFFFF};

	// Cache functions:
	void clear_cache() {
		for (auto i = 0u; i < dup_module_index.size(); i++) // NOLINT
			dup_module_index[i] = 0;
		// gcc 12.3 complains of writing past end of array
		// when using range-based for loop
		// for (auto &d : dup_module_index)
		// 	d = 0;

		for (auto &out_conn : out_conns)
			out_conn = disconnected_jack;

		for (auto &in_conn : in_conns)
			in_conn.clear();

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
		pr_dbg("update_or_add_input_panel_conn: %x\n", panel_jack_id);
		auto chan = Midi::midi_channel(panel_jack_id);

		if (auto num = Midi::midi_note_pitch(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_pitch_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI note (poly %d) ch: %u", num.value(), chan);

		} else if (auto num = Midi::midi_note_gate(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_gate_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI gate (poly %d) ch:% ch:%uu", num.value(), chan);

		} else if (auto num = Midi::midi_note_vel(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_vel_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI vel (poly %d) ch:%u", num.value(), chan);

		} else if (auto num = Midi::midi_note_aft(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_aft_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI aftertouch (poly %d) ch:%u", num.value(), chan);

		} else if (auto num = Midi::midi_note_retrig(panel_jack_id); num.has_value()) {
			update_or_add(midi_note_retrig[num.value()].conns, input_jack, chan);
			pr_dbg("MIDI retrig (poly %d) ch:%u", num.value(), chan);

		} else if (auto num = Midi::midi_gate(panel_jack_id); num.has_value()) {
			update_or_add(midi_gate_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI note %d gate ch:%u", num.value(), chan);

		} else if (auto num = Midi::midi_cc(panel_jack_id); num.has_value()) {
			update_or_add(midi_cc_conns[num.value()], input_jack, chan);
			pr_dbg("MIDI CC/PW %d ch:%u", num.value(), chan);

		} else if (auto num = Midi::midi_clk(panel_jack_id); num.has_value()) {
			update_or_add(midi_pulses[TimingEvents::Clock].conns, input_jack);
			pr_dbg("MIDI Clk");

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
	void update_or_add(std::vector<Jack> &v, const Jack &d) {
		if (auto found = std::ranges::find(v, d); found == v.end())
			v.push_back(d);
	}

	void update_or_add(std::vector<MappedKnob> &v, const MappedKnob &d) {
		for (auto &el : v) {
			if (el.maps_to_same_as(d)) {
				el = d;
				return;
			}
		}
		v.push_back(d);
	}

	void update_or_add(std::vector<JackMidi> &v, const Jack &d, uint32_t midi_chan = 0) {
		for (auto &el : v) {
			if (el.module_id == d.module_id && el.jack_id == d.jack_id) {
				el.midi_chan = midi_chan;
				return;
			}
		}
		v.push_back({d, midi_chan});
	}

	// Cache a panel knob mapping into knob_conns[]
	void cache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
		if (knob_set >= knob_maps.size())
			return;
		if (k.panel_knob_id < PanelDef::NumKnobs) {
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
		}
	}

	//Remove a mapping
	void uncache_knob_mapping(unsigned knob_set, const MappedKnob &k) {
		if (knob_set >= knob_maps.size())
			return;
		if (k.panel_knob_id >= knob_maps[knob_set].size())
			return;
		std::erase_if(knob_maps[knob_set][k.panel_knob_id], [&k](auto m) { return (k.maps_to_same_as(m.map)); });
	}

	void cache_midi_mapping(const MappedKnob &k) {
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

	void uncache_midi_mapping(const MappedKnob &k) {
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
		return knob_maps;
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
