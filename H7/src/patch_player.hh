#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_node.hh"
#include "patch/patch.hh"
#include "sys/alloc_buffer.hh"
#include <cstdint>

using PanelT = Panel;

class PatchPlayer {
public:
	bool is_loaded = false;
	std::array<float, MAX_NODES_IN_PATCH> nodes;
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// cached data:
	Jack out_conns[Panel::NumInJacks] = {{0}}; // [2]: OutL OutR
	Jack in_conns[Panel::NumOutJacks] = {{0}}; // [6]: InL InR CVA, etc..

	// Index of each module that appears more than once.
	// 0 = only appears once in the patch
	// 1 => reads "LFO #1", 2=> "LFO #2", etc.
	uint8_t dup_module_index[MAX_MODULES_IN_PATCH] = {0};

public:
	PatchPlayer()
	{
		clear_cache();
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

	void unload_patch(const Patch &p)
	{
		is_loaded = false;

		for (int i = 0; i < p.num_modules; i++) {
			modules[i].reset(nullptr);
		}

		clear_cache();

		BigAlloc<Patch>::reset();
	}

	void clear_cache()
	{
		for (int i = 0; i < MAX_MODULES_IN_PATCH; i++)
			dup_module_index[i] = 0;

		for (int i = 0; i < Panel::NumInJacks; i++)
			out_conns[i] = {0, 0};

		for (int i = 0; i < Panel::NumOutJacks; i++)
			in_conns[i] = {0, 0};
	}

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

	void mark_patched_jacks(const Patch &p)
	{
		if constexpr (USE_NODES == true)
			return;

		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];

			for (int jack_i = 0; jack_i < net.num_jacks; jack_i++) {
				auto &jack = net.jacks[jack_i];
				// Todo: add get_num_inputs() etc to CoreProcessor, so we can range-check here
				if (jack_i == 0)
					modules[jack.module_id]->mark_output_patched(jack.jack_id);
				else
					modules[jack.module_id]->mark_input_patched(jack.jack_id);
			}
		}
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
		for (unsigned i = 0; i < p.num_modules; i++) {
			auto &this_slug = p.modules_used[i];

			unsigned found = 1;
			unsigned this_index = 0;
			for (unsigned j = 0; j < p.num_modules; j++) {
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

	void update_patch(const Patch &p)
	{
		// Todo: possible to use refs for knobs?
		for (int i = 0; i < p.num_mapped_knobs; i++) {
			auto &k = p.mapped_knobs[i];
			auto val = get_panel_param(k.panel_knob_id);
			modules[k.module_id]->set_param(k.param_id, val);
		}

		for (int i = 1; i < p.num_modules; i++) {
			modules[i]->update();
		}

		if constexpr (USE_NODES == false) {
			// Copy outs to ins: ~1.3us for 4 nets
			for (int net_i = 0; net_i < p.num_nets; net_i++) {
				auto &net = p.nets[net_i];
				auto &output = net.jacks[0];

				// Todo: instead of this if block, just define Panel::get_output() as get_input()
				// and set_input() as set_output()
				// and then we need to change the audio functions
				float out_val;
				// if (output.module_id == 0)
				// 	out_val = get_panel_input(output.jack_id);
				// else
				out_val = modules[output.module_id]->get_output(output.jack_id);

				for (int jack_i = 1; jack_i < net.num_jacks; jack_i++) {
					auto &jack = net.jacks[jack_i];
					// if (jack.module_id == 0)
					// 	set_panel_output(jack.jack_id, out_val);
					// else
					modules[jack.module_id]->set_input(jack.jack_id, out_val);
				}
			}
		}
	}
};
