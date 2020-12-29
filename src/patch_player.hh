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
	int _num_modules;

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
		int i = 0;
		for (auto type_id : p.modules_used) {
			if (type_id == LAST_MODULE || type_id >= NUM_MODULE_TYPES)
				break;
			modules[i++] = (ModuleFactory::create(type_id));
			// Todo: other safety checks, ie only one PANEL
		}
		if (i)
			_num_modules = i - 1;
		else
			return; // empty patch

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
			if (endpt->module_id == LAST_)
				break;
			modules[endpt->module_id]->mark_output_patched(endpt->jack_id);

			while (++endpt < net.end() && endpt->module_id != LAST_) {
				modules[endpt->module_id]->mark_input_patched(endpt->jack_id);
			}
		}

		// Set static params
		for (auto &k : p.knobs) {
			if (k.module_id == LAST_)
				break;
			modules[k.module_id]->set_param(k.param_id, k.value);
		}
	}

	void update_patch(const Patch &p)
	{
		// Copy outs to ins
		for (auto &net : p.nets) {
			auto endpt = net.begin();
			if (endpt->module_id == LAST_)
				break;
			float out_val = modules[endpt->module_id]->get_output(endpt->jack_id);

			while (++endpt < net.end() && endpt->module_id != LAST_) {
				auto in_modid = endpt->module_id;
				auto in_jackid = endpt->jack_id;
				modules[in_modid]->set_input(in_jackid, out_val);
			}
		}

		// update each module
		for (int i = 0; i < _num_modules; i++) {
			modules[i]->update();
		}
	}
};

