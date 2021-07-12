#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_node.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#ifndef TESTPROJECT
	#include "debug.hh"
#else
	#include "../stubs/debug.hh"
	#include <iostream>
#endif
#include "conf/hsem_conf.hh"
#include "drivers/smp.hh"
#include "patch/patch.hh"
#include "smp_api.hh"
#include "sys/alloc_buffer.hh"
#include <cstdint>
#include <vector>

namespace MetaModule
{
using PanelT = Panel;

class PatchPlayer {
	enum {
		NumInConns = Panel::NumOutJacks,
		NumOutConns = Panel::NumInJacks,
	};

public:
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// out_conns[]: OutL OutR CVOut1 CVOut2 ClockOut, each element is a Jack
	Jack out_conns[NumOutConns] __attribute__((aligned(4))) = {{0, 0}};

	// in_conns[]: InL InR CVA CVB CVC CVD GateIn1 GateIn2 ClockIn, each element is a vector of Jacks it's connected to
	std::array<std::vector<Jack>, NumInConns> in_conns;

	// knob_conns[]: A B C D a b c d, each element is a vector of knobs it's mapped to
	std::array<std::vector<MappedKnob>, Panel::NumKnobs> knob_conns;

	ModuleTypeSlug *module_slugs;
	InternalCable *int_cables;
	MappedInputJack *mapped_ins;
	MappedOutputJack *mapped_outs;
	StaticParam *static_knobs;
	MappedKnob *mapped_knobs;

	int *num_int_cable_ins;

	bool is_loaded = false;

private:
	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

	PatchHeader *header;
	static const inline ModuleTypeSlug no_patch_loaded = "(Not Loaded)";

public:
	PatchPlayer()
	{
		clear_cache();
	}

	void load_patch_from_header(PatchHeader *ph)
	{
		header = ph;
		module_slugs = new ModuleTypeSlug[ph->num_modules];
		int_cables = new InternalCable[ph->num_int_cables];
		mapped_ins = new MappedInputJack[ph->num_mapped_ins];
		mapped_outs = new MappedOutputJack[ph->num_mapped_outs];
		static_knobs = new StaticParam[ph->num_static_knobs];
		mapped_knobs = new MappedKnob[ph->num_mapped_knobs];

		auto slugs_ptr = reinterpret_cast<ModuleTypeSlug *>(ph + 1);
		for (int i = 0; i < ph->num_modules; i++)
			module_slugs[i] = slugs_ptr[i];

		auto int_cables_ptr = reinterpret_cast<InternalCable *>(slugs_ptr + ph->num_modules);
		for (int i = 0; i < ph->num_int_cables; i++)
			int_cables[i] = int_cables_ptr[i];

		auto mapped_ins_ptr = reinterpret_cast<MappedInputJack *>(int_cables_ptr + ph->num_int_cables);
		for (int i = 0; i < ph->num_mapped_ins; i++)
			mapped_ins[i] = mapped_ins_ptr[i];

		auto mapped_outs_ptr = reinterpret_cast<MappedOutputJack *>(mapped_ins_ptr + ph->num_mapped_ins);
		for (int i = 0; i < ph->num_mapped_outs; i++)
			mapped_outs[i] = mapped_outs_ptr[i];

		auto static_knobs_ptr = reinterpret_cast<StaticParam *>(mapped_outs_ptr + ph->num_mapped_outs);
		for (int i = 0; i < ph->num_static_knobs; i++)
			static_knobs[i] = static_knobs_ptr[i];

		auto mapped_knobs_ptr = reinterpret_cast<MappedKnob *>(static_knobs_ptr + ph->num_static_knobs);
		for (int i = 0; i < ph->num_mapped_knobs; i++)
			mapped_knobs[i] = mapped_knobs_ptr[i];

		num_int_cable_ins = new int[ph->num_int_cables];
		calc_int_cable_connections();
	}

	// Loads the given patch as the active patch, and caches some pre-calculated values
	bool load_patch(PatchHeader *ph)
	{
		SMPThread::init();

		if (is_loaded)
			unload_patch();

		load_patch_from_header(ph);

		for (int i = 0; i < header->num_modules; i++) {
			modules[i] = ModuleFactory::create(module_slugs[i]);

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
		for (int i = 0; i < ph->num_static_knobs; i++) {
			const auto &k = static_knobs[i];
			modules[k.module_id]->set_param(k.param_id, k.value);
		}

		is_loaded = true;

		calc_multiple_module_indicies();
		return true;
	}

	// Runs the patch
	void update_patch()
	{
		for (int module_i = 1; module_i < header->num_modules; module_i++) {
			if (!SMPThread::is_running()) {
				SMPThread::launch_command<SMPCommand::UpdateModule, SMPRegister::ModuleID>(module_i);
			} else {
				modules[module_i]->update();
			}
		}
		SMPThread::join();

		for (int net_i = 0; net_i < header->num_int_cables; net_i++) {
			auto &cable = int_cables[net_i];

			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);

			for (int jack_i = 0; jack_i < num_int_cable_ins[net_i]; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}
	}

	void unload_patch()
	{
		SMPThread::join();
		is_loaded = false;
		for (int i = 0; i < header->num_modules; i++) {
			modules[i].reset(nullptr);
		}

		delete[] module_slugs;
		delete[] int_cables;
		delete[] mapped_ins;
		delete[] mapped_outs;
		delete[] static_knobs;
		delete[] mapped_knobs;
		delete[] num_int_cable_ins;

		clear_cache();
		BigAllocControl::reset();
	}

	// K-rate setters/getters:

	void set_panel_param(int param_id, float val)
	{
		if (!is_loaded)
			return;
		auto &knob_conn = knob_conns[param_id];
		for (auto &k : knob_conn)
			modules[k.module_id]->set_param(k.param_id, k.get_mapped_val(val));
	}

	void set_panel_input(int jack_id, float val)
	{
		if (!is_loaded)
			return;
		// if (jack_id >= NumInConns)
		// 	return;
		auto &jacks = in_conns[jack_id];
		for (auto &jack : jacks)
			modules[jack.module_id]->set_input(jack.jack_id, val);
	}

	float get_panel_output(int jack_id)
	{
		if (!is_loaded)
			return 0.f;
		auto &jack = out_conns[jack_id];
		if (jack.module_id > 0)
			return modules[jack.module_id]->get_output(jack.jack_id);
		else
			return 0.f;
	}

	// General info getters:

	const ModuleTypeSlug &get_patch_name()
	{
		return is_loaded ? header->patch_name : no_patch_loaded;
	}

	int get_num_modules()
	{
		return is_loaded ? header->num_modules : 0;
	}

	int get_num_int_cables()
	{
		return is_loaded ? header->num_int_cables : 0;
	}

	int get_num_mapped_knobs()
	{
		return is_loaded ? header->num_mapped_knobs : 0;
	}

	const ModuleTypeSlug &get_module_name(int idx)
	{
		return (is_loaded && idx < header->num_modules) ? module_slugs[idx] : no_patch_loaded;
	}

	// Given the user-facing output jack id (0 = Audio Out L, 1 = Audio Out R, etc)
	// Return the Jack {module_id, jack_id} that it's connected to
	// {0,0} means not connected, or index out of range
	Jack get_panel_output_connection(unsigned jack_id)
	{
		if (jack_id >= Panel::NumUserFacingOutJacks)
			return {.module_id = 0, .jack_id = 0};

		return out_conns[jack_id];
	}

	// Given the user-facing panel input jack id (0 = Audio In L, 1 = Audio In R, etc)
	// return the Jack {module_id, jack_id} that it's connected to.
	// The optional multiple_connection_id is used if multiple jacks are connected to the panel jack (defaults to 0).
	// {0,0} means not connected, or index out of range
	Jack get_panel_input_connection(unsigned jack_id, unsigned multiple_connection_id = 0)
	{
		// Todo: support multiple jacks connected to one net
		if ((jack_id >= Panel::NumUserFacingInJacks) || (multiple_connection_id >= in_conns[jack_id].size()))
			return {.module_id = 0, .jack_id = 0};

		return in_conns[jack_id][multiple_connection_id];
	}

	static constexpr unsigned get_num_panel_knobs()
	{
		return Panel::NumKnobs;
	}
	static constexpr unsigned get_num_panel_inputs()
	{
		return Panel::NumInJacks;
	}
	static constexpr unsigned get_num_panel_outputs()
	{
		return Panel::NumOutJacks;
	}

	// Jack patched/unpatched status

	void mark_patched_jacks()
	{
		for (int net_i = 0; net_i < header->num_int_cables; net_i++) {
			auto &cable = int_cables[net_i];

			modules[cable.out.module_id]->mark_output_patched(cable.out.jack_id);
			for (int jack_i = 0; jack_i < num_int_cable_ins[net_i]; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				modules[input_jack.module_id]->mark_input_patched(input_jack.jack_id);
			}
		}
	}

	void set_input_jack_patched_status(int panel_in_jack_id, bool is_patched)
	{
		if (panel_in_jack_id >= NumInConns)
			return;
		auto &jacks = in_conns[panel_in_jack_id];
		for (auto &jack : jacks) {
			if (jack.module_id > 0) {
				if (is_patched)
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
			}
		}
	}

	void set_output_jack_patched_status(int panel_out_jack_id, bool is_patched)
	{
		if (panel_out_jack_id >= NumOutConns)
			return;
		auto &jack = out_conns[panel_out_jack_id];
		if (jack.module_id > 0) {
			if (is_patched)
				modules[jack.module_id]->mark_output_patched(jack.jack_id);
			else
				modules[jack.module_id]->mark_output_unpatched(jack.jack_id);
		}
	}

	// Cache functions:
	void clear_cache()
	{
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
	int find_int_cable_input_jack(Jack in)
	{
		for (int net_i = 0; net_i < header->num_int_cables; net_i++) {
			auto &cable = int_cables[net_i];
			for (int jack_i = 0; jack_i < num_int_cable_ins[net_i]; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				if (in == input_jack)
					return net_i;
			}
		}
		return -1;
	}

	void calc_int_cable_connections()
	{
		for (int net_i = 0; net_i < header->num_int_cables; net_i++) {
			num_int_cable_ins[net_i] = MAX_CONNECTIONS_PER_NODE - 1;
			auto &cable = int_cables[net_i];
			for (int jack_i = 0; jack_i < MAX_CONNECTIONS_PER_NODE - 1; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				if (input_jack.module_id < 0)
					num_int_cable_ins[net_i] = jack_i;
			}
		}
	}

	// Cache all the panel jack connections
	void calc_panel_jack_connections()
	{
		for (int net_i = 0; net_i < header->num_mapped_ins; net_i++) {
			auto &cable = mapped_ins[net_i];
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id < 0 || panel_jack_id >= Panel::NumUserFacingInJacks)
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

		for (int net_i = 0; net_i < header->num_mapped_outs; net_i++) {
			auto &cable = mapped_outs[net_i];
			auto panel_jack_id = cable.panel_jack_id;
			if (panel_jack_id < 0 || panel_jack_id >= Panel::NumUserFacingOutJacks)
				break;
			out_conns[panel_jack_id] = cable.out;
		}
	}

	void calc_panel_knob_connections()
	{
		for (int i = 0; i < header->num_mapped_knobs; i++) {
			auto &k = mapped_knobs[i];
			knob_conns[k.panel_knob_id].push_back(k);
		}
	}

	// Check for multiple instances of same module type, and cache the results
	// This is used to create unique names for modules (e.g. LFO#1, LFO#2,...)
	void calc_multiple_module_indicies()
	{
		// Todo: this is a naive implementation, perhaps can be made more efficient
		for (int i = 0; i < header->num_modules; i++) {
			auto &this_slug = module_slugs[i];

			unsigned found = 1;
			unsigned this_index = 0;
			for (int j = 0; j < header->num_modules; j++) {
				if (i == j) {
					this_index = found;
					continue;
				}
				auto &that_slug = module_slugs[j];
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
	uint8_t get_multiple_module_index(uint8_t idx)
	{
		return dup_module_index[idx];
	}
};
} // namespace MetaModule
