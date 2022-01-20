#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#if !defined(TESTPROJECT) && !defined(SIMULATOR)
#include "debug.hh"
#else
#include "../stubs/debug.hh"
#endif
#include "conf/hsem_conf.hh"
#include "conf/panel_conf.hh"
#include "drivers/smp.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "smp_api.hh"
#include "sys/alloc_buffer.hh"
#include "util/countzip.hh"
#include "util/math.hh"
#include <array>
#include <cstdint>
#include <vector>

namespace MetaModule
{

class PatchPlayer {
	enum {
		NumInConns = PanelDef::NumOutJacks,
		NumOutConns = PanelDef::NumInJacks,
	};

public:
	//TODO: why not use a vector here?
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// out_conns[]: OutL OutR CVOut1 CVOut2 ClockOut, each element is a Jack
	Jack out_conns[NumOutConns] __attribute__((aligned(4))) = {{0, 0}};

	// in_conns[]: InL InR CVA CVB CVC CVD GateIn1 GateIn2 ClockIn, each element is a vector of Jacks it's connected to
	std::array<std::vector<Jack>, NumInConns> in_conns;

	// knob_conns[]: A B C D a b c d, each element is a vector of knobs it's mapped to
	std::array<std::vector<MappedKnob>, PanelDef::NumKnobs> knob_conns;

	std::vector<int> num_int_cable_ins;

	bool is_loaded = false;

private:
	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

	PatchData *pd;
	static const inline ModuleTypeSlug no_patch_loaded = "(Not Loaded)";

public:
	PatchPlayer() {
		clear_cache();
	}

	void load_patch_header_data(PatchData *patchdata) {
		if (is_loaded)
			unload_patch();

		pd = patchdata;

		num_int_cable_ins.reserve(pd->int_cables.size());
		calc_int_cable_connections();
	}

	// Loads the given patch as the active patch, and caches some pre-calculated values
	bool load_patch(PatchData *patchdata) {
		mdrivlib::SMPThread::init();

		if (patchdata == nullptr)
			return false;

		load_patch_header_data(patchdata);

		for (int i = 0; i < pd->module_slugs.size(); i++) {
			//FIXME: Do we ever do anything with modules[0] ? Perhaps just UI displaying names, which we can get from a defs file
			if (i == 0)
				modules[i] = ModuleFactory::create(PanelDef::typeID);
			else
				modules[i] = ModuleFactory::create(pd->module_slugs[i]);

			if (modules[i] == nullptr) {
				is_loaded = false;
				return false;
			}

			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
		}

		// Todo: if we need to improve patch loading time by a small amount,
		// it's a little faster to combine these functions so we only do one loop over nets/jacks
		// ...but it's harder to unit test.
		mark_patched_jacks();
		calc_panel_jack_connections();
		calc_panel_knob_connections();

		// Set all initial knob values:
		for (auto &k : pd->static_knobs) {
			modules[k.module_id]->set_param(k.param_id, k.value);
		}

		is_loaded = true;

		calc_multiple_module_indicies();
		return true;
	}

	// Runs the patch
	void update_patch() {
		if (pd->module_slugs.size() < 2)
			return;

		if (pd->module_slugs.size() == 2)
			modules[1]->update();
		else {
			mdrivlib::SMPControl::write<SMPRegister::ModuleID>(2);
			mdrivlib::SMPControl::write<SMPRegister::NumModules>(pd->module_slugs.size());
			mdrivlib::SMPControl::write<SMPRegister::IndexIncrement>(2);
			mdrivlib::SMPControl::notify<SMPCommand::UpdateListOfModules>();
			for (int module_i = 1; module_i < pd->module_slugs.size(); module_i += 2) {
				// Debug::Pin2::high();
				modules[module_i]->update();
				// Debug::Pin2::low();
			}

			// LEave this here until we are sure it's working OK on Mini
			// for (int module_i = 1; module_i < header->num_modules; module_i++) {
			// 	if (!mdrivlib::SMPThread::is_running()) {
			// 		mdrivlib::SMPThread::launch_command<SMPCommand::UpdateModule, SMPRegister::ModuleID>(module_i);
			// 	} else {
			// 		Debug::Pin2::high();
			// 		modules[module_i]->update();
			// 		Debug::Pin2::low();
			// 	}
			// }
			mdrivlib::SMPThread::join();
		}

		for (auto &cable : pd->int_cables) {
			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);
			for (auto &input_jack : cable.ins) {
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}
	}

	void unload_patch() {
		mdrivlib::SMPThread::join();
		is_loaded = false;
		for (int i = 0; i < pd->module_slugs.size(); i++) {
			modules[i].reset(nullptr);
		}

		num_int_cable_ins.clear();

		clear_cache();
		BigAllocControl::reset();
	}

	// K-rate setters/getters:

	void set_panel_param(int param_id, float val) {
		if (!is_loaded)
			return;
		auto &knob_conn = knob_conns[param_id];
		for (auto const &k : knob_conn) {
			modules[k.module_id]->set_param(k.param_id, k.get_mapped_val(val));
		}
	}

	void set_panel_input(int jack_id, float val) {
		if (!is_loaded)
			return;
		// if (jack_id >= NumInConns)
		// 	return;
		auto &jacks = in_conns[jack_id];
		for (auto const &jack : jacks)
			modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	float get_panel_output(int jack_id) {
		if (!is_loaded)
			return 0.f;
		auto const &jack = out_conns[jack_id];
		if (jack.module_id > 0)
			return modules[jack.module_id]->get_output(jack.jack_id);
		else
			return 0.f;
	}

	// General info getters:

	const ModuleTypeSlug &get_patch_name() {
		return is_loaded ? pd->patch_name : no_patch_loaded;
	}

	int get_num_modules() {
		return is_loaded ? pd->module_slugs.size() : 0;
	}

	int get_num_int_cables() {
		return is_loaded ? pd->int_cables.size() : 0;
	}

	int get_num_mapped_knobs() {
		return is_loaded ? pd->mapped_knobs.size() : 0;
	}

	const ModuleTypeSlug &get_module_name(int idx) {
		return (is_loaded && idx < pd->module_slugs.size()) ? pd->module_slugs[idx] : no_patch_loaded;
	}

	InternalCable &get_int_cable(int idx) {
		if (idx < pd->int_cables.size())
			return pd->int_cables[idx];
		else
			return pd->int_cables[0]; //error
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
		return PanelDef::NumInJacks;
	}
	static constexpr unsigned get_num_panel_outputs() {
		return PanelDef::NumOutJacks;
	}

	// Jack patched/unpatched status

	void mark_patched_jacks() {
		for (auto const &cable : pd->int_cables) {
			modules[cable.out.module_id]->mark_output_patched(cable.out.jack_id);
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

		for (auto &knob_conn : knob_conns)
			knob_conn.clear();
	}

	// Returns the index in int_cables[] for a cable that has the given Jack as an input
	// Return -1 if does not exist
	int find_int_cable_input_jack(Jack in) {
		// for (int net_i = 0; net_i < ph->num_int_cables; net_i++) {
		// 	auto &cable = pd->int_cables[net_i];
		for (auto [net_i, cable] : enumerate(pd->int_cables)) {
			for (int jack_i = 0; jack_i < num_int_cable_ins[net_i]; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				if (in == input_jack)
					return net_i;
			}
		}
		return -1;
	}

	void calc_int_cable_connections() {
		for (int net_i = 0; net_i < pd->int_cables.size(); net_i++) {
			num_int_cable_ins[net_i] = MAX_CONNECTIONS_PER_NODE - 1;
			auto &cable = pd->int_cables[net_i];
			for (int jack_i = 0; jack_i < MAX_CONNECTIONS_PER_NODE - 1; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				if (input_jack.module_id < 0)
					num_int_cable_ins[net_i] = jack_i;
			}
		}
	}

	// Map all the panel jack connections into in_conns[] and out_conns[]
	// which are indexed by panel_jack_id.
	// This speeds up propagating I/O from user to virtual modules
	void calc_panel_jack_connections() {
		for (auto const &cable : pd->mapped_ins) {
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id < 0 || panel_jack_id >= PanelDef::NumUserFacingInJacks)
				break;
			for (int j = 0; j < MAX_CONNECTIONS_PER_NODE - 1; j++) {
				if (cable.ins[j].module_id < 0 || cable.ins[j].jack_id < 0)
					break;
				int dup_int_cable = find_int_cable_input_jack(cable.ins[j]);
				if (dup_int_cable == -1)
					in_conns[panel_jack_id].push_back(cable.ins[j]);
				else {
					// TODO: handle a mapped and patched input jack:
					// - ? Create a module that outputs the sum of two inputs, and adjust int_cables and in_mappings?
					// - ? Keep the mapping and remove the int_cable entry?
					// - ? Keep it as-is (ignore the mapping and keep the int_cable)
				}
			}
		}

		for (auto const &cable : pd->mapped_outs) {
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id < 0 || panel_jack_id >= PanelDef::NumUserFacingOutJacks)
				break;
			out_conns[panel_jack_id] = cable.out;
		}
	}

	// Map all the panel knob mappings into knob_conns[] which is indexed by panel_knob_id.
	void calc_panel_knob_connections() {
		for (auto const &k : pd->mapped_knobs) {
			knob_conns[k.panel_knob_id].push_back(k);
		}
	}

	// Check for multiple instances of same module type, and cache the results
	// This is used to create unique names for modules (e.g. LFO#1, LFO#2,...)
	void calc_multiple_module_indicies() {
		// Todo: this is a naive implementation, perhaps can be made more efficient
		for (int i = 0; i < pd->module_slugs.size(); i++) {
			auto &this_slug = pd->module_slugs[i];

			unsigned found = 1;
			unsigned this_index = 0;
			for (int j = 0; j < pd->module_slugs.size(); j++) {
				if (i == j) {
					this_index = found;
					continue;
				}
				auto &that_slug = pd->module_slugs[j];
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
