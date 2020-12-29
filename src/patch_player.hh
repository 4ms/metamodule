#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel.hh"
#include "patch.hh"
#include <cstdint>

struct PatchPlayer {
	std::vector<std::unique_ptr<CoreProcessor>> modules;
	std::vector<float> net_val;

	void load_patch(Patch &p)
	{
		for (auto type_id : p.modules_used) {
			modules.emplace_back(ModuleFactory::create(type_id));
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
		// Mark jacks as patched/unpatched
		for (auto &m : modules) {
			m->mark_all_inputs_unpatched();
			m->mark_all_outputs_unpatched();
		}
		for (auto &net : p.nets) {
			auto endpt = net.begin();
			modules[endpt->module_id]->mark_output_patched(endpt->jack_id);
			while (++endpt < net.end()) {
				modules[endpt->module_id]->mark_input_patched(endpt->jack_id);
			}
		}

		// Set static params
		for (auto &k : p.knobs) {
			modules[k.module_id]->set_param(k.param_id, k.value);
		}
	}

	void update_patch(Patch &p)
	{
		// Copy outs to ins
		for (auto &net : p.nets) {
			auto endpt = net.begin();
			float out_val = modules[endpt->module_id]->get_output(endpt->jack_id);

			while (++endpt < net.end()) {
				auto in_modid = endpt->module_id;
				auto in_jackid = endpt->jack_id;
				modules[in_modid]->set_input(in_jackid, out_val);
			}
		}

		// update each module
		for (auto &m : modules) {
			m->update();
		}
	}
};

