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
#include "sys/alloc_buffer.hh"
#include <cstdint>

namespace MetaModule
{
using PanelT = Panel;

class PatchPlayer {
public:
	std::array<float, MAX_NODES_IN_PATCH> nodes;
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// cached data:
	enum {
		NumInConns = Panel::NumOutJacks,
		NumOutConns = Panel::NumInJacks,
	};
	Jack out_conns[NumOutConns] __attribute__((aligned(4))) = {{0, 0}}; // [5]: OutL OutR CVOut1 CVOut2 ClockOut
	Jack in_conns[NumInConns] = {{0, 0}}; // [9]: InL InR CVA CVB CVC CVD GateIn1 GateIn2 ClockIn

	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

	bool is_loaded = false;

public:
	PatchPlayer()
	{
		clear_cache();
	}

	// Loads the given patch as the active patch, and caches some pre-calculated values
	bool load_patch(const Patch &p)
	{
		clear_cache();
		for (auto &n : nodes)
			n = 0.f;

		for (int i = 0; i < p.num_modules; i++) {
			if constexpr (USE_NODES)
				modules[i] = ModuleFactory::createWithParams(p.modules_used[i], nodes.data(), p.module_nodes[i]);
			else
				modules[i] = ModuleFactory::create(p.modules_used[i]);

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
		mark_patched_jacks(p);
		calc_panel_jack_connections(p);

		// Set all initial knob values:
		for (int i = 0; i < p.num_static_knobs; i++) {
			const auto &k = p.static_knobs[i];
			modules[k.module_id]->set_param(k.param_id, k.value);
		}

		is_loaded = true;

		calc_multiple_module_indicies(p);
		return true;
	}

	// Runs the patch
	void update_patch(const Patch &p)
	{
		// Todo: possible to use refs for knobs?
		for (int i = 0; i < p.num_mapped_knobs; i++) {
			auto &k = p.mapped_knobs[i];
			auto val = get_panel_param(k.panel_knob_id);
			modules[k.module_id]->set_param(k.param_id, val);
		}

		if constexpr (target::TYPE == mdrivlib::SupportedTargets::stm32mp1_ca7) {

			for (int i = 1; i < p.num_modules; i++) {
				if (i == 1) {
					// mdrivlib::SystemCache::clean_dcache();
					SMPControl::write(i);
					SMPControl::notify(1);
				} else {
					Debug::Pin1::high();
					modules[i]->update();
					Debug::Pin1::low();
				}
			}
			Debug::Pin2::high();
			while (SMPControl::read() != 0)
				;
			Debug::Pin2::low();

			// Tell aux core to flush its cache (so we can copy outs->ins)
			// SMPControl::write(2);
			// SMPControl::notify(2);
			// while (SMPControl::read() != 0)
			// 	;

		} else {
			for (int i = 1; i < p.num_modules; i++) {
				modules[i]->update();
			}
		}

		if constexpr (USE_NODES == false) {
			for (int net_i = 0; net_i < p.num_nets; net_i++) {
				auto &net = p.nets[net_i];
				auto &output = net.jacks[0];

				float out_val;
				out_val = modules[output.module_id]->get_output(output.jack_id);

				for (int jack_i = 1; jack_i < net.num_jacks; jack_i++) {
					auto &jack = net.jacks[jack_i];
					modules[jack.module_id]->set_input(jack.jack_id, out_val);
				}
			}
		}
	}

	void unload_patch(const Patch &p)
	{
		is_loaded = false;
		for (int i = 0; i < p.num_modules; i++) {
			modules[i].reset(nullptr);
		}
		clear_cache();
		BigAllocControl::reset();
	}

	void mark_patched_jacks(const Patch &p)
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

	// Getters and Setters:

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

	void set_panel_param(int param_id, float val)
	{
		if (!is_loaded)
			return;
		static_cast<PanelT *>(modules[0].get())->set_param(param_id, val);
	}

	float get_panel_param(int param_id)
	{
		if (!is_loaded)
			return 0.f;
		return static_cast<PanelT *>(modules[0].get())->get_param(param_id);
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
	}

	// Cache all the panel jack connections
	void calc_panel_jack_connections(const Patch &p)
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
	void calc_multiple_module_indicies(const Patch &p)
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
