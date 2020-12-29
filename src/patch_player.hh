#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel.hh"
#include "patch.hh"
#include <cstdint>

class PatchPlayer {
private:
	std::array<float, MAX_NODES_IN_PATCH> net_val;
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;
	const int _Panel = 0;

public:
	void set_panel_input(int input_id, float val)
	{
		modules[_Panel]->set_input(input_id, val);
	}
	void set_panel_param(int param_id, float val)
	{
		modules[_Panel]->set_param(param_id, val);
	}
	float get_panel_output(int output_id)
	{
		return modules[_Panel]->get_output(output_id);
	}

	void load_patch(const Patch &p)
	{
		// Todo: safety checks: num_modules = 0 or num_nets = 0, return with error

		for (int i = 0; i < p.num_modules; i++) {
			modules[i] = (ModuleFactory::create(p.modules_used[i]));
			// Todo: other safety checks, ie only one PANEL
			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
		}

		// nodes:
		// for (int net_i = 0; net_i < p.num_nets; net_i++) {
		// int net_i = 0;
		// for (auto &net : p.nets) {
		// 	net_val[net_i] = 0.f;
		// 	for (auto &endpt : net) {
		// 		auto mod_id = endpt.module_id;
		// 		auto jack_id = endpt.jack_id;
		// 		if (mod_id < modules.size() && jack_id < modules[mod_id].jacks.size())
		// 			modules[mod_id]->jack[jack_id].node_value = &(net_val[net_i]);
		// 	}
		// 	net_i++;
		// }

		// get/set functions:
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];

			for (int node_i = 0; node_i < net.num_nodes; node_i++) {
				auto &node = net.nodes[node_i];
				if (node.module_id > p.num_modules)
					continue;
				if (node_i == 0)
					modules[node.module_id]->mark_output_patched(node.jack_id);
				else
					modules[node.module_id]->mark_input_patched(node.jack_id);
			}
		}

		// Set static params
		for (int i = 0; i < p.num_knobs; i++) {
			auto &k = p.knobs[i];
			modules[k.module_id]->set_param(k.param_id, k.value);
		}
	}

	void update_patch(const Patch &p)
	{
		// Copy outs to ins
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];
			auto &output = net.nodes[0];
			if (output.module_id >= p.num_modules)
				continue;
			float out_val = modules[output.module_id]->get_output(output.jack_id);

			for (int node_i = 1; node_i < net.num_nodes; node_i++) {
				auto &node = net.nodes[node_i];
				if (node.module_id >= p.num_modules)
					continue;
				modules[node.module_id]->set_input(node.jack_id, out_val);
			}
		}

		// update each module
		for (int i = 0; i < p.num_modules; i++) {
			modules[i]->update();
		}
	}
};

