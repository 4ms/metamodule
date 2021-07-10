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
#endif
#include "conf/hsem_conf.hh"
#include "drivers/smp.hh"
#include "patch/patch.hh"
#include "smp_api.hh"
#include "sys/alloc_buffer.hh"
#include <cstdint>

namespace MetaModule
{
using PanelT = Panel;

class PatchPlayer {

	struct Knob {
		uint16_t module_id;
		uint16_t param_id;
	};

	enum {
		NumInConns = Panel::NumOutJacks,
		NumOutConns = Panel::NumInJacks,
	};

public:
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	Jack out_conns[NumOutConns] __attribute__((aligned(4))) = {{0, 0}}; // [5]: OutL OutR CVOut1 CVOut2 ClockOut
	Jack in_conns[NumInConns] = {{0, 0}}; // [9]: InL InR CVA CVB CVC CVD GateIn1 GateIn2 ClockIn
	Knob knob_conns[Panel::NumKnobs]{{0, 0}};

	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

private:
	bool is_loaded = false;
	PatchHeader *header;
	static const inline ModuleTypeSlug no_patch_loaded = "(Not Loaded)";

	ModuleTypeSlug *module_slugs;
	InternalCable *int_cables;
	MappedInputJack *mapped_ins;
	MappedOutputJack *mapped_outs;
	StaticParam *static_knobs;
	MappedKnob *mapped_knobs;

public:
	PatchPlayer()
	{
		clear_cache();
	}

	const ModuleTypeSlug &get_patch_name()
	{
		if (is_loaded)
			return header->patch_name;
		else
			return no_patch_loaded;
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

		// TODO: fill these arrays with the data from ph + sizeof(PatchHeader)
	}

	// Loads the given patch as the active patch, and caches some pre-calculated values
	bool load_patch(PatchHeader *ph)
	{
		SMPThread::init();
		clear_cache();

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
		// it's a little faster to combine these two functions so we only do one loop over nets/jacks
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

		// Note: we are skipping mapped ins/outs!
		for (int net_i = 0; net_i < header->num_int_cables; net_i++) {
			auto &cable = int_cables[net_i];

			float out_val = modules[cable.out.module_id]->get_output(cable.out.jack_id);

			for (int jack_i = 0; jack_i < MAX_CONNECTIONS_PER_NODE - 1; jack_i++) {
				auto &input_jack = cable.ins[jack_i];
				if (input_jack.module_id < 0)
					break;
				modules[input_jack.module_id]->set_input(input_jack.jack_id, out_val);
			}
		}
	}

	void unload_patch()
	{
		SMPThread::join();
		is_loaded = false;
		for (int i = 0; i < p.num_modules; i++) {
			modules[i].reset(nullptr);
		}

		delete[] module_slugs;
		delete[] int_cables;
		delete[] mapped_ins;
		delete[] mapped_outs;
		delete[] static_knobs;
		delete[] mapped_knobs;

		clear_cache();
		BigAllocControl::reset();
	}

	// Getters and Setters:

	void set_panel_param(int param_id, float val)
	{
		if (!is_loaded)
			return;
		auto &k = knob_conns[param_id];
		modules[k.module_id]->set_param(k.param_id, val);
	}

	void set_panel_input(int jack_id, float val)
	{
		if (!is_loaded)
			return;
		static_cast<PanelT *>(modules[0].get())->set_panel_input(jack_id, val);
	}

	float get_panel_output(int jack_id)
	{
		if (!is_loaded)
			return 0.f;
		return static_cast<PanelT *>(modules[0].get())->get_panel_output(jack_id);
	}

	// float get_panel_param(int param_id)
	// {
	// 	if (!is_loaded)
	// 		return 0.f;
	// 	return static_cast<PanelT *>(modules[0].get())->get_param(param_id);
	// }

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
		if constexpr (USE_NODES == true)
			return;

		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];

			for (int jack_i = 0; jack_i < net.num_jacks; jack_i++) {
				auto &jack = net.jacks[jack_i];
				if (jack_i == 0)
					modules[jack.module_id]->mark_output_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
			}
		}
	}

	void set_input_jack_patched_status(int panel_in_jack_id, bool is_patched)
	{
		if (panel_in_jack_id >= NumInConns)
			return;
		auto &jack = in_conns[panel_in_jack_id];
		if (jack.module_id > 0) {
			if (is_patched)
				modules[jack.module_id]->mark_input_patched(jack.jack_id);
			else
				modules[jack.module_id]->mark_input_unpatched(jack.jack_id);
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
			in_conn = {0, 0};

		for (auto &knob_conn : knob_conns)
			knob_conn = {0, 0};
	}

	// Cache all the panel jack connections
	void calc_panel_jack_connections()
	{
		if constexpr (USE_NODES == true)
			return;

		const int panelId = 0;
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];
			for (int jack_i = 0; jack_i < net.num_jacks; jack_i++) {
				auto &jack = net.jacks[jack_i];
				if (jack.module_id == panelId) {
					if (jack_i == 0) {
						// panel jack is producer, which means it's a user-facing input (e.g. Audio In L)
						if (jack.jack_id < Panel::NumUserFacingInJacks)
							in_conns[jack.jack_id] = net.jacks[1];
					} else {
						// panel jack is consumer, which means it's a user-facing output (e.g. CV Out 3)
						if (jack.jack_id < Panel::NumUserFacingOutJacks)
							out_conns[jack.jack_id] = net.jacks[0];
					}
				}
			}
		}
	}

	void calc_panel_knob_connections()
	{
		for (int i = 0; i < p.num_mapped_knobs; i++) {
			auto &k = p.mapped_knobs[i];
			knob_conns[k.panel_knob_id].module_id = k.module_id;
			knob_conns[k.panel_knob_id].param_id = k.param_id;
		}
	}

	// Given the user-facing output jack id (0 = Audio Out L, 1 = Audio Out R, etc)
	// Return the Jack {module_id, jack_id} that it's connected to
	// {0,0} means not connected, or index out of range
	Jack get_panel_output_connection(unsigned jack_id, unsigned multiple_connection_id = 0)
	{
		// Todo: support multiple jacks connected to one net
		if (jack_id >= Panel::NumUserFacingOutJacks || multiple_connection_id > 0)
			return {.module_id = 0, .jack_id = 0};

		return out_conns[jack_id];
	}

	// Given the user-facing input jack id (0 = Audio In L, 1 = Audio In R, etc)
	// Return the Jack {module_id, jack_id} that it's connected to
	// {0,0} means not connected, or index out of range
	Jack get_panel_input_connection(unsigned jack_id, unsigned multiple_connection_id = 0)
	{
		// Todo: support multiple jacks connected to one net
		if (jack_id >= Panel::NumUserFacingInJacks || multiple_connection_id > 0)
			return {.module_id = 0, .jack_id = 0};

		return in_conns[jack_id];
	}

	// Check for multiple instances of same module type, and cache the results
	void calc_multiple_module_indicies()
	{
		// Todo: this is a naive implementation, perhaps can be made more efficient
		for (int i = 0; i < p.num_modules; i++) {
			auto &this_slug = p.modules_used[i];

			unsigned found = 1;
			unsigned this_index = 0;
			for (int j = 0; j < p.num_modules; j++) {
				if (i == j) {
					this_index = found;
					continue;
				}
				auto &that_slug = p.modules_used[j];
				if (that_slug == this_slug) {
					found++;
				}
			}
			if (found == 1)
				this_index = 0;
			dup_module_index[i] = this_index;
		}
	}

	// Return the mulitple-module-same-type index of the given module index
	// 0 ==> this is the only module of its type
	// >0 ==> a number to append to the module name, e.g. 1 ==> LFO#1, 2 ==> LFO#2, etc
	uint8_t get_multiple_module_index(uint8_t idx)
	{
		return dup_module_index[idx];
	}
};
} // namespace MetaModule
