#pragma once
#include "coreProcessor.h"
#include "lfoCore.h"
#include "mixer4core.h"
#include "moduleTypes.h"
#include "panel.hh"
#include "patch.hh"
#include <cstdint>

class PatchPlayer {
private:
	bool is_loaded = false;
	std::array<float, MAX_NODES_IN_PATCH> net_val;
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

	// Todo: we will hard fault if modules[0] is not of type Panel*.
	// Maybe the Panel is not the module list, and when we encounter it
	// in the netlist, we manually set/get from panel

public:
	void set_panel_input(int input_id, float val)
	{
		if (!is_loaded)
			return;
		//"inputs" as seen by the outside world == "outputs" as seen by other modules
		static_cast<Panel *>(modules[0].get())->outputs[input_id] = val;
	}

	void set_panel_param(int param_id, float val)
	{
		if (!is_loaded)
			return;
		static_cast<Panel *>(modules[0].get())->set_param(param_id, val);
	}

	float get_panel_param(int param_id)
	{
		if (!is_loaded)
			return 0.f;
		return static_cast<Panel *>(modules[0].get())->params[param_id];
	}

	float get_panel_output(int output_id)
	{
		//"outputs" as seen by the outside world == "inputs" as seen by other modules
		return static_cast<Panel *>(modules[0].get())->inputs[output_id];
	}

	void load_patch(const Patch &p)
	{
		// Todo: safety checks: num_modules = 0 or num_nets = 0, return with error
		// check if any node, static_knob or mapped_knob has an invalid module_id
		// check all modules_used are valid (could just check for nullptrs after creating modules)

		// Requirement of the patch format: first module must be PANEL (Todo: extend this to different PANELs)
		// if (p.modules_used[0] != "PANEL")
		// 	return;

		for (int i = 0; i < p.num_modules; i++) {
			modules[i] = ModuleFactory::create(p.modules_used[i]);

			if (modules[i] == nullptr) {
				is_loaded = true;
				return; // Todo: return an error so that we don't try to run the patch
			}

			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
		}

		// Mark patched jacks:
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];

			for (int node_i = 0; node_i < net.num_nodes; node_i++) {
				auto &node = net.nodes[node_i];
				if (node_i == 0)
					modules[node.module_id]->mark_output_patched(node.jack_id);
				else
					modules[node.module_id]->mark_input_patched(node.jack_id);
			}
		}

		// Set static params
		for (int i = 0; i < p.num_static_knobs; i++) {
			auto &k = p.static_knobs[i];
			modules[k.module_id]->set_param(k.param_id, k.value);
		}
	}

	void update_patch(const Patch &p)
	{
		// Set mapped knobs
		for (int i = 0; i < p.num_mapped_knobs; i++) {
			auto &k = p.mapped_knobs[i];
			auto val = get_panel_param(k.panel_knob_id);
			modules[k.module_id]->set_param(k.param_id, val);
		}

		// update each module
		for (int i = 0; i < p.num_modules; i++) {
			modules[i]->update();
		}

		// Copy outs to ins
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];
			auto &output = net.nodes[0];
			float out_val = modules[output.module_id]->get_output(output.jack_id);

			for (int node_i = 1; node_i < net.num_nodes; node_i++) {
				auto &node = net.nodes[node_i];
				modules[node.module_id]->set_input(node.jack_id, out_val);
			}
		}
	}
};

// Todo: try the node approach (inputs/outputs are essentially ptrs to nodes)
// Perhaps a class system where inputs have read-only access and outputs have write-only access
// to the node elements.
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
