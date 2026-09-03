#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/hub/audio_expander_defs.hh"
#include "CoreModules/moduleFactory.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/patch_conf.hh"
#include "null_module.hh"
#include "params/catchup_manager.hh"
#include "params/catchup_param.hh"
#include "params/midi_params.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_play/balance_modules.hh"
#include "patch_play/cable_cache.hh"
#include "patch_play/live_load.hh"
#include "patch_play/midi_connections.hh"
#include "patch_play/multicore_play.hh"
#include "patch_play/param_watch.hh"
#include "patch_play/patch_player_query_patch.hh"
#include "patch_play/plugin_module.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>

#include "debug.hh"

namespace MetaModule
{

// PatchPlayer owns the running patch: the module instances, the internal cable cache,
// and the lookup tables that route panel jacks, knobs and MIDI to module ports.
//
// This header holds the data members and every function that runs in the audio
// context (which must stay inline). The non-audio duties are implemented in:
//   patch_player_load.cc     - loading/unloading a patch, module creation
//   patch_player_balance.cc  - splitting modules between cores
//   patch_player_modules.cc  - adding/removing/replacing modules in a loaded patch
//   patch_player_mappings.cc - patch mods: knob maps, MIDI maps, cables, jack mappings
//   patch_player_cache.cc    - building the panel/MIDI connection tables
//   patch_player_catchup.cc  - knob catchup modes
//   midi_connections.hh/.cc  - the MIDI routing tables
class PatchPlayer {
public:
	// TODO: modules should be a FixedVector, and then num_modules is replaced by modules.size()
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;
	CableCache<MulticorePlayer::NumCores> cables;

	unsigned num_modules = 0;
	std::atomic<bool> is_loaded = false;

	LiveLoadMeter live_load;

	PatchQuery patch_query{modules, pd};

private:
	// Out1-Out8 + Ext Out1-8
	static constexpr auto NumOutJacks = PanelDef::NumUserFacingOutJacks + AudioExpander::NumOutJacks;
	static constexpr auto NumInJacks = PanelDef::NumUserFacingInJacks + AudioExpander::NumInJacks;

	struct PolyJack : Jack {
		CoreProcessor::PolyPortBuffer buf{};
	};
	std::array<std::vector<PolyJack>, NumOutJacks> out_conns;

	// in_conns[]: In1-In6, GateIn1, GateIn2, ExpIn7-12
	std::array<std::vector<Jack>, NumInJacks> in_conns;

	// Cached panel input values, used by get_panel_output for MIDI/Hub-to-Hub summing.
	// Indices [0, NumInJacks) store panel input values.
	// Indices [MidiHubOffset, PanelInValsSize) store MIDI-to-Hub passthrough values,
	// allocated via next_midi_hub_slot counter during calc_panel_jack_connections.
	static constexpr auto MidiHubOffset = NumInJacks;
	static constexpr auto MaxMidiHubSlots = 64;
	static constexpr auto PanelInValsSize = MidiHubOffset + MaxMidiHubSlots;
	std::array<float, PanelInValsSize> panel_in_vals{};

	std::array<bool, NumOutJacks> out_patched{};
	std::array<bool, NumInJacks> in_patched{};

	// MIDI -> module jack/param routing tables
	MidiConnections midi;

	ParamWatcher param_watcher;

	std::array<ParamSet, MaxKnobSets> knob_maps;
	CatchupManager catchup_manager;

	MulticorePlayer smp;
	using CoreBalancer = Balancer<MulticorePlayer::NumCores, MAX_MODULES_IN_PATCH>;
	CoreBalancer core_balancer;

	// For live_load measurements:
	mdrivlib::CycleCounter update_patch_time;
	mdrivlib::CycleCounter section_time;

	// Cached facts about what the patch uses, so the audio stream can skip
	// iterating jacks or knobs
	uint32_t used_input_jacks_ = 0;
	uint32_t used_output_jacks_ = 0;
	bool has_knob_maps_ = false;
	bool has_midi_pulse_conns = false;

	float samplerate = 48000.f;

	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	std::array<uint8_t, MAX_MODULES_IN_PATCH> dup_module_index{};

	PatchData pd;
	unsigned active_knob_set = 0;
	static inline ModuleTypeSlug no_patch_loaded{"(Not Loaded)"};

	static inline Jack disconnected_jack = {0xFFFF, 0xFFFF};

public:
	PatchPlayer();
	~PatchPlayer();

	ParamWatcher &watched_params() {
		return param_watcher;
	}

	//
	// Loading/unloading a patch (patch_player_load.cc)
	//

	void copy_patch_data(const PatchData &patchdata);
	Result load_patch(const PatchData &patchdata);
	void unload_patch();
	void set_samplerate(float hz);
	void calc_multiple_module_indicies();
	enum class CreateResult { Ok, NotFound, OutOfMemory, Crashed };
	static std::unique_ptr<CoreProcessor> try_create_module(std::string_view combined_slug,
															CreateResult *result = nullptr);

	//
	// Load balancing (patch_player_balance.cc)
	//

	enum class Balance { UseStored, Recalculate };
	void rebalance_modules(Balance mode = Balance::UseStored);

	std::vector<uint16_t> const &get_module_cores() const {
		return pd.module_cores;
	}

	std::vector<uint32_t> const &get_module_loads() const {
		return pd.module_loads;
	}

	struct BalanceCandidates {
		std::vector<std::vector<uint16_t>> cores;
		std::vector<uint32_t> loads_ppm;
	};
	BalanceCandidates make_balance_candidates(unsigned num_seeds);
	void set_load_balance(std::vector<uint16_t> const &module_cores, std::vector<uint32_t> const &module_loads);

	//
	// Adding/removing modules in a loaded patch (patch_player_modules.cc)
	//

	CreateResult add_module(BrandModuleSlug slug);
	bool add_module_at_idx(BrandModuleSlug slug, unsigned module_idx, CreateResult *result = nullptr);
	void remove_module(uint16_t module_idx);

	// replace a module without changing any mappings or cables
	void substitute_module(unsigned module_idx, BrandModuleSlug new_slug);

	// replace a module, discarding all its mappings and cables
	void replace_module(uint16_t module_idx, BrandModuleSlug new_slug);

	void reset_module(uint16_t module_id, std::string_view data = "");
	void set_module_bypass(uint16_t module_id, bool bypassed);

	//
	// Patch Mods (patch_player_mappings.cc)
	//

	void apply_static_param(const StaticParam &sparam);
	void add_mapped_knob(uint32_t knobset_id, const MappedKnob &map);
	void edit_mapped_knob(uint32_t knobset_id, const MappedKnob &map);
	void remove_mapped_knob(uint32_t knobset_id, const MappedKnob &map);
	void add_midi_mapped_knob(const MappedKnob &map);
	void add_internal_cable(Jack in, Jack out);
	void add_injack_mapping(uint16_t panel_jack_id, Jack jack);
	void add_outjack_mapping(uint16_t panel_jack_id, Jack jack);
	void disconnect_injack(Jack jack);
	void remove_injack_mappings(Jack jack);
	void disconnect_outjack(Jack jack);
	void remove_outjack_mappings(Jack jack);
	unsigned num_poly_cable_channels(Jack out, Jack in);

	// poly_num is the user setting: 0 = Auto (compute from cables), 1-8 = hard-set
	void set_midi_poly_num(uint16_t poly_num);

	//
	// Knob catchup (patch_player_catchup.cc)
	//

	// Set mode for all maps
	void set_catchup_mode(CatchupParam::Mode mode, bool allow_jump_outofrange);

	// Set mode for one mapping only
	void set_catchup_mode(int knob_set_idx, unsigned module_id, unsigned param_id, CatchupParam::Mode mode);

	// Set mode for one module/param, in any knobset
	void set_catchup_mode(unsigned module_id, unsigned param_id, CatchupParam::Mode mode);

	bool is_param_tracking(unsigned module_id, unsigned param_id);

	std::optional<unsigned> panel_knob_catchup_inaccessible();

	//
	// Connection cache (patch_player_cache.cc)
	//

	void calc_panel_jack_connections();
	void update_or_add_input_panel_conn(uint32_t panel_jack_id, Jack input_jack);

	//
	// Audio context: running the patch
	//

	// Runs the patch
	void update_patch() {
		if (num_modules < 2)
			return;

		if (core_balancer.cores.parts[1].size() == 0) {
			update_patch_singlecore();
			return;
		}

		else {
			update_patch_time.start_simple_measurement();

			smp.update_modules();

			uint32_t module_ticks = 0;
			if (live_load.detailed()) {
				// Chained per-module timing: one counter read marks both the
				// end of one module and the start of the next
				section_time.start_measurement();
				for (auto module_i : core_balancer.cores.parts[0]) {
					step_module(module_i);

					section_time.start_measurement();
					auto ticks = section_time.get_last_period_raw();
					live_load.tally_module(module_i, ticks);
					module_ticks += ticks;
				}
			} else {
				section_time.start_simple_measurement();
				for (auto module_i : core_balancer.cores.parts[0]) {
					step_module(module_i);
				}
				module_ticks = section_time.stop_simple_measurement();
			}

			section_time.start_simple_measurement();
			process_outputs_samecore<0>();
			auto cable_ticks = section_time.stop_simple_measurement();

			// Synchronize cores here before they update each other's module's inputs
			section_time.start_simple_measurement();
			smp.join();
			auto sync_ticks = section_time.stop_simple_measurement();

			section_time.start_simple_measurement();
			update_midi_pulses();
			auto midi_ticks = section_time.stop_simple_measurement();

			smp.process_cables();

			section_time.start_simple_measurement();
			process_outputs_diffcore<0>();
			process_summed_inputs<0>();
			cable_ticks += section_time.stop_simple_measurement();

			section_time.start_simple_measurement();
			smp.join();
			auto sync2_ticks = section_time.stop_simple_measurement();

			live_load.tally_update_patch(update_patch_time.stop_simple_measurement(),
										 module_ticks,
										 sync_ticks,
										 cable_ticks,
										 midi_ticks,
										 sync2_ticks);
		}
	}

	void process_outputs(auto &cables) {
		for (auto const &cable : cables) {
			if (cable.out_buf.voltages) {
				auto num_poly = *cable.out_buf.channels;
				for (auto i = 0u; auto &in_buf : cable.in_bufs) {
					if (in_buf.voltages) {
						// poly->poly
						*in_buf.channels = num_poly;
						std::copy_n(cable.out_buf.voltages, num_poly, in_buf.voltages);
					} else {
						// poly->mono
						modules[cable.ins[i].module_id]->set_input(cable.ins[i].jack_id, *cable.out_buf.voltages);
					}
					i++;
				}
			} else {
				// mono->poly, mono->mono
				float val = modules[cable.out.module_id]->get_output(cable.out.jack_id);

				for (auto const &in : cable.ins) {
					modules[in.module_id]->set_input(in.jack_id, val);
				}
			}
		}
	}

	template<size_t Core>
	void process_outputs_samecore() {
		process_outputs(cables.samecore_cables[Core]);
	}

	template<size_t Core>
	void process_outputs_diffcore() {
		process_outputs(cables.diffcore_cables[Core]);
	}

	template<size_t Core>
	void process_summed_inputs() {
		for (auto const &si : cables.summed_inputs[Core]) {
			if (si.in_buf.voltages) {
				// Poly input: sum per-channel across all sources
				unsigned max_channels = 0;

				for (size_t i = 0; i < si.outs.size(); i++) {
					if (si.out_bufs[i].voltages)
						max_channels = std::max<unsigned>(max_channels, *si.out_bufs[i].channels);
				}
				max_channels = std::min<unsigned>(max_channels, CoreProcessor::MaxPolyChannels);

				// Zero the input buffer, then accumulate
				for (unsigned ch = 0; ch < max_channels; ch++)
					si.in_buf.voltages[ch] = 0.f;

				for (size_t i = 0; i < si.outs.size(); i++) {
					if (si.out_bufs[i].voltages) {
						auto n = std::min<unsigned>(*si.out_bufs[i].channels, max_channels);
						for (unsigned ch = 0; ch < n; ch++)
							si.in_buf.voltages[ch] += si.out_bufs[i].voltages[ch];
					} else {
						// Mono source: add to channel 0
						si.in_buf.voltages[0] += get_output(si.outs[i]);
					}
				}
				*si.in_buf.channels = max_channels;

			} else {
				// Mono input: sum all sources via get_output/set_input
				float sum = 0.f;
				for (auto const &out : si.outs) {
					sum += get_output(out);
				}
				modules[si.in.module_id]->set_input(si.in.jack_id, sum);
			}
		}
	}

	void step_module(unsigned module_i) {
		modules[module_i]->update();
	}

	void update_patch_singlecore() {
		update_patch_time.start_simple_measurement();

		uint32_t module_ticks = 0;
		if (live_load.detailed()) {
			// Chained per-module timing: one counter read marks both the end of
			// one module and the start of the next
			section_time.start_measurement();
			for (size_t module_i = 1; module_i < num_modules; module_i++) {
				step_module(module_i);

				section_time.start_measurement();
				auto ticks = section_time.get_last_period_raw();
				live_load.tally_module(module_i, ticks);
				module_ticks += ticks;
			}
		} else {
			section_time.start_simple_measurement();
			for (size_t module_i = 1; module_i < num_modules; module_i++) {
				step_module(module_i);
			}
			module_ticks = section_time.stop_simple_measurement();
		}

		section_time.start_simple_measurement();
		process_outputs_samecore<0>();
		process_outputs_diffcore<0>();
		process_summed_inputs<0>();
		auto cable_ticks = section_time.stop_simple_measurement();

		section_time.start_simple_measurement();
		update_midi_pulses();
		auto midi_ticks = section_time.stop_simple_measurement();

		live_load.tally_update_patch(
			update_patch_time.stop_simple_measurement(), module_ticks, 0, cable_ticks, midi_ticks, 0);
	}

	void trigger_reading_gui_elements() {
		smp.read_patch_gui_elements();
	}

	void sync() {
		smp.join();
	}

	void notify_audio_resumed() {
		smp.refresh_patch_gui_elements();
	}

	//
	// Audio context: interface with audio stream
	//

	void set_panel_param(unsigned panel_knob_id, float val) {
		catchup_manager.set_panel_param(modules, knob_maps[active_knob_set], panel_knob_id, val);
	}

	void set_panel_param_no_play(unsigned panel_knob_id, float val) {
		catchup_manager.set_panel_param_no_play(panel_knob_id, val);
	}

	void set_panel_input(unsigned jack_id, float val) {
		// cache signal for Panel Ins
		if (jack_id < NumInJacks)
			panel_in_vals[jack_id] = val;
		set_all_connected_jacks(in_conns[jack_id], val);
	}

	// Bitmask of panel input jacks that are mapped
	// Bit positions match ParamsState::jack_senses
	uint32_t used_input_jacks() const {
		return used_input_jacks_;
	}

	// Bitmask of panel output jacks that are mapped (jack_senses bit positions)
	uint32_t used_output_jacks() const {
		return used_output_jacks_;
	}

	// True if any knobset maps a panel knob
	bool has_knob_maps() const {
		return has_knob_maps_;
	}

	void set_active_knob_set(unsigned num) {
		auto new_active_knob_set = std::min(num, MaxKnobSets - 1);

		if (active_knob_set != new_active_knob_set) {
			active_knob_set = new_active_knob_set;

			catchup_manager.reset(modules, knob_maps[active_knob_set]);
		}
	}

	void set_midi_note_pitch(unsigned poly_chan, float val, uint16_t midi_chan) {
		set_all_connected_jacks(midi.note_pitch_conns[poly_chan], val, midi_chan);
		set_all_connected_poly_jacks(midi.poly_pitch_conns, poly_chan, val, midi_chan);
	}

	void set_midi_note_gate(unsigned poly_chan, float val, uint16_t midi_chan) {
		set_all_connected_jacks(midi.note_gate_conns[poly_chan], val, midi_chan);
		set_all_connected_poly_jacks(midi.poly_gate_conns, poly_chan, val, midi_chan);
	}

	void set_midi_note_velocity(unsigned poly_chan, int16_t val, uint16_t midi_chan) {
		float volts = float(val) / 12.7f;

		set_all_connected_jacks(midi.note_vel_conns[poly_chan], volts, midi_chan);
		set_all_connected_poly_jacks(midi.poly_vel_conns, poly_chan, volts, midi_chan);
	}

	void set_midi_note_aftertouch(unsigned poly_chan, int16_t val, uint16_t midi_chan) {
		float volts = float(val) / 12.7f;

		// Mono cables:
		set_all_connected_jacks(midi.note_aft_conns[poly_chan], volts, midi_chan);
		set_all_connected_poly_jacks(midi.poly_aft_conns, poly_chan, volts, midi_chan);
	}

	void set_midi_note_retrig(unsigned poly_chan, float val, uint16_t midi_chan) {
		// Mono cables:
		set_all_connected_jacks(midi.note_retrig[poly_chan].conns, val, midi_chan);
		midi.note_retrig[poly_chan].pulse.start(0.01);

		set_all_connected_poly_jacks(midi.poly_retrig.conns, poly_chan, val, midi_chan);
		if (poly_chan < MaxMidiPolyphony)
			midi.poly_retrig.pulses[poly_chan].start(0.01);
	}

	void set_midi_cc(unsigned ccnum, int16_t val, uint16_t midi_chan) {
		// CC values arrive as 14-bit from the M4 core (see Midi::u14cc_to_volts). Pitch
		// bend is a separate signed 14-bit value handled directly.
		using namespace Midi;
		float volts = (ccnum == PitchBendCC) ? s14_to_semitones<2>(val) : u14cc_to_volts<10>(val);

		volts = std::clamp(volts, 0.f, 10.f);

		// Update jacks connected to this CC
		if (ccnum < midi.cc_conns.size()) {
			set_all_connected_jacks(midi.cc_conns[ccnum], volts, midi_chan);
		}

		// Update knobs connected to this CC
		if (ccnum < midi.cc_knob_maps.size()) {
			for (auto &mm : midi.cc_knob_maps[ccnum]) {
				if (mm.module_id < num_modules) {
					if (mm.midi_chan == 0 || mm.midi_chan == (midi_chan + 1)) {
						modules[mm.module_id]->set_param(mm.param_id, mm.get_mapped_val(volts / 10.f));
					}
				}
			}
		}
	}

	void set_midi_gate(unsigned note_num, float volts, uint16_t midi_chan) {
		if (note_num < midi.gate_conns.size())
			set_all_connected_jacks(midi.gate_conns[note_num], volts, midi_chan);

		if (note_num >= midi.note_knob_maps.size())
			return;

		for (auto &mm : midi.note_knob_maps[note_num]) {
			if (mm.module_id >= num_modules)
				continue;

			if (mm.midi_chan > 0 && mm.midi_chan != (midi_chan + 1))
				continue;

			auto normal_val = volts / 10.f;
			if (is_toggle(mm)) {
				toggle_button(modules[mm.module_id], mm, normal_val);

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

			set_all_connected_jacks(midi.pulses[event].conns, val);
			midi.pulses[event].pulse.start(0.01);
		}

		if (event == TimingEvents::Start) {
			midi.reset_divclocks();
		}

		// Handle DivClocks
		if (event == TimingEvents::Clock) {
			unsigned idx = 0;
			for (auto &divclk_pulse : midi.divclk_pulses) {
				divclk_pulse.divclk_ctr++;
				if (divclk_pulse.divclk_ctr >= Midi::DivClockAmt[idx]) {
					divclk_pulse.divclk_ctr = 0;
					divclk_pulse.pulse.start(0.01);
					set_all_connected_jacks(divclk_pulse.conns, val);
				}
				idx++;
			}
		}
	}

private:
	// Returns module output, or the cached midi/hub passthrough value
	float get_output(Jack out) {
		if (out.module_id == 0) {
			// Hub module: read from cached panel input values
			if (out.jack_id < panel_in_vals.size())
				return panel_in_vals[out.jack_id];
			else
				return 0;
		} else {
			return modules[out.module_id]->get_output(out.jack_id);
		}
	}

	// Sets a module input, or a midi/hub passthrough value
	void set_input(Jack in, float val) {
		if (in.module_id == 0) {
			if (in.jack_id < panel_in_vals.size())
				panel_in_vals[in.jack_id] = val;
		} else {
			modules[in.module_id]->set_input(in.jack_id, val);
		}
	}

	template<typename JackT>
	void set_all_connected_jacks(std::vector<JackT> const &jacks, float val) {
		for (auto const &jack : jacks)
			set_input(jack, val);
	}

	template<typename JackMidiT>
	void set_all_connected_jacks(std::vector<JackMidiT> const &jacks, float val, uint32_t midi_chan) {
		for (auto const &jack : jacks) {
			if (jack.midi_chan == 0 || jack.midi_chan == (midi_chan + 1)) {
				set_input(jack, val);
			}
		}
	}

	template<typename JackMidiT>
	void set_all_connected_poly_jacks(std::vector<JackMidiT> const &jacks,
									  unsigned poly_chan,
									  float val,
									  uint32_t midi_chan) {
		for (auto const &jack : jacks) {
			if (jack.midi_chan != 0 && jack.midi_chan != uint32_t(midi_chan + 1))
				continue;

			// Route to the cable that carries this poly channel (1-4 cable: base 0, 5-8 cable: base 4)
			if (poly_chan < jack.poly_base)
				continue;

			auto idx = poly_chan - jack.poly_base;

			if (idx >= CoreProcessor::MaxPolyChannels)
				continue;

			if (jack.buf.voltages)
				jack.buf.voltages[idx] = val;

			else if (idx == 0)
				set_input(jack, val);
		}
	}

	void update_midi_pulses() {
		if (!has_midi_pulse_conns)
			return;

		midi.update_pulses([this](Jack jack, float val) { set_input(jack, val); });
	}

public:
	float get_panel_output(uint32_t jack_id) {
		float sum = 0.f;
		for (auto const &jack : out_conns[jack_id]) {
			if (jack.buf.voltages) {
				auto num_chan = std::min<unsigned>(CoreProcessor::MaxPolyChannels, *jack.buf.channels);
				for (unsigned i = 0; i < num_chan; i++)
					sum += jack.buf.voltages[i];
			} else {
				sum += get_output(jack);
			}
		}
		return sum;
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

	uint32_t get_midi_poly_num() {
		return pd.midi_poly_num;
	}

	//
	// Audio context: jack sense and MIDI connect/disconnect events
	//

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

		for (auto const &jack : out_conns[panel_out_jack_id]) {
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
	}

	// Follow every internal cable and tell the modules that their jacks are patched
	// Optionally filter by module id
	void mark_patched_jacks(std::optional<uint16_t> module_id = std::nullopt) {
		for (auto const &cable : pd.int_cables) {
			if (!module_id.has_value() || cable.out.module_id == module_id.value())
				modules[cable.out.module_id]->mark_output_patched(cable.out.jack_id);

			for (auto const &input_jack : cable.ins) {
				if (input_jack.module_id < num_modules)
					if (!module_id.has_value() || input_jack.module_id == module_id.value())
						modules[input_jack.module_id]->mark_input_patched(input_jack.jack_id);
			}
		}
	}

	void mark_patched_panel_jacks(std::optional<uint16_t> module_idx = std::nullopt) {
		for (auto i = 0u; auto const &panel_out : out_conns) {
			if (out_patched[i]) {
				for (auto const &c : panel_out) {
					if (!module_idx.has_value() || c.module_id == module_idx)
						modules[c.module_id]->mark_output_patched(c.jack_id);
				}
			}
			i++;
		}
		for (auto i = 0u; auto const &panel_in : in_conns) {
			if (in_patched[i]) {
				for (auto const &c : panel_in) {
					if (!module_idx.has_value() || c.module_id == module_idx)
						modules[c.module_id]->mark_input_patched(c.jack_id);
				}
			}
			i++;
		}
	}

	void set_midi_connected() {
		midi.for_each_jack([this](Jack const &jack) {
			if (jack.module_id > 0 && jack.module_id < num_modules)
				modules[jack.module_id]->mark_input_patched(jack.jack_id);
		});

		midi.set_poly_channel_count(pd.midi_poly_num);

		midi.reset_divclocks();

		midi.connected = true;
	}

	void set_midi_disconnected() {
		midi.for_each_jack([this](Jack const &jack) {
			if (jack.module_id > 0 && jack.module_id < num_modules)
				modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
		});

		midi.zero_poly_buffers();

		midi.connected = false;
	}

private:
	//
	// Non-audio private helpers
	//

	// patch_player_balance.cc
	// Records the load balance in the patch data, so it can be saved to the patch file
	// and re-used the next time the patch is loaded.
	void store_load_balance(CoreBalancer::Arrangement const &arrangement, std::span<const unsigned> cpu_times);

	// patch_player_mappings.cc
	void safe_unpatch_output(Jack jack);
	void safe_unpatch_input(Jack jack);
	bool output_jack_held_by_panel(Jack jack) const;

	// patch_player_cache.cc
	void clear_cache();
	void refresh_conn_flags();

	// Returns the index in int_cables[] for a cable that has the given Jack as an input
	// Return -1 if does not exist
	int find_int_cable_input_jack(Jack in);
	bool has_other_mapped_in(Jack j);

	static void update_or_add(std::vector<Jack> &v, const Jack &d);

	// Cache a panel knob mapping into knob_conns[]
	void cache_knob_mapping(unsigned knob_set, const MappedKnob &k);
	//Remove a mapping
	void uncache_knob_mapping(unsigned knob_set, const MappedKnob &k);

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
	Jack get_panel_output_connection(unsigned jack_id, unsigned multiple_connection_id = 0) {
		if ((jack_id >= out_conns.size()) || (multiple_connection_id >= out_conns[jack_id].size()))
			return {.module_id = 0, .jack_id = 0};

		return out_conns[jack_id][multiple_connection_id];
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
