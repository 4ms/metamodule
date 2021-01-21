#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleTypes.h"
#define USE_NODES
#ifdef USE_NODES
	#include "CoreModules/panel_node.hh"
#else
	#include "CoreModules/panel.hh"
#endif
#include "patch/patch.hh"
#include <cstdint>
#ifdef STM32F7
	#include "debug.hh"
#endif

#ifdef USE_NODES
using PanelT = NodePanel;
#else
using PanelT = Panel;
#endif

class PatchPlayer {
private:
	bool is_loaded = false;
	std::array<float, MAX_NODES_IN_PATCH> nodes;
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> modules;

public:
	void set_panel_input(int jack_id, float val)
	{
		if (!is_loaded)
			return;
#ifdef USE_NODES
		static_cast<PanelT *>(modules[0].get())->set_input(jack_id, val);
#else
		static_cast<PanelT *>(modules[0].get())->set_output(jack_id, val);
#endif
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

	float get_panel_output(int jack_id)
	{
#ifdef USE_NODES
		return static_cast<PanelT *>(modules[0].get())->get_output(jack_id);
#else
		return static_cast<PanelT *>(modules[0].get())->get_input(jack_id);
#endif
	}

	void load_patch(const Patch &p)
	{
		for (auto &n : nodes)
			n = 0.f;

		for (int i = 0; i < p.num_modules; i++) {
#ifdef USE_NODES
			modules[i] = ModuleFactory::createWithParams(p.modules_used[i], nodes.data(), p.module_nodes[i]);
#else
			modules[i] = ModuleFactory::create(p.modules_used[i]);
#endif

			if (modules[i] == nullptr) {
				is_loaded = false;
				return;
			}

			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
		}

		// Mark patched jacks:
#ifdef USE_NODES
// Todo
#else
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
#endif

		for (int i = 0; i < p.num_static_knobs; i++) {
			const auto &k = p.static_knobs[i];
			modules[k.module_id]->set_param(k.param_id, k.value);
		}

		is_loaded = true;
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

#ifdef USE_NODES
#else
		// Copy outs to ins: ~1.3us for 4 nets
		for (int net_i = 0; net_i < p.num_nets; net_i++) {
			auto &net = p.nets[net_i];
			auto &output = net.nodes[0];
			float out_val = modules[output.module_id]->get_output(output.jack_id);

			for (int node_i = 1; node_i < net.num_nodes; node_i++) {
				auto &node = net.nodes[node_i];
				modules[node.module_id]->set_input(node.jack_id, out_val);
			}
		}
#endif
	}
};
