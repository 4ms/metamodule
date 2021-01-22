#pragma once
#include "CommData.h"
#include "patch/patch.hh"
#include <map>

class PatchWriter {

public:
	PatchWriter(Patch &patch)
		: p{patch}
	{}

	void copyModuleList(std::vector<ModuleID> &modules)
	{
		moduleData = modules;
	}
	void copyJackList(std::vector<JackStatus> &jacks)
	{
		jackData = jacks;
	}
	void copyParamList(std::vector<ParamStatus> &params)
	{
		paramData = params;
	}

	void addMaps(std::vector<Mapping> maps)
	{
		for (auto &m : maps) {
			if (m.dst.objType == LabelButtonID::Types::Knob) {
				mapData.push_back(m);
			}
			if (m.dst.objType == LabelButtonID::Types::InputJack) {
				jackData.push_back({
					.sendingJackId = m.dst.objID,
					.receivedJackId = m.src.objID,
					.sendingModuleId = m.dst.moduleID,
					.receivedModuleId = m.src.moduleID,
					.connected = true,
				});
			}
			if (m.dst.objType == LabelButtonID::Types::OutputJack) {
				jackData.push_back({
					.sendingJackId = m.src.objID,
					.receivedJackId = m.dst.objID,
					.sendingModuleId = m.src.moduleID,
					.receivedModuleId = m.dst.moduleID,
					.connected = true,
				});
			}
		}
	}

	void generateModuleList()
	{
		std::vector<int> vcv_mod_ids;

		int i = 1;
		vcv_mod_ids.push_back(-1);
		for (auto &mod : moduleData) {
			if (strcmp(mod.typeID.name, "PANEL_8") == 0) {
				p.modules_used[0] = mod.typeID;
				vcv_mod_ids[0] = mod.id;
			} else {
				p.modules_used[i] = mod.typeID;
				vcv_mod_ids.push_back(mod.id);
				i++;
			}
		}
		p.num_modules = i;

		if (vcv_mod_ids[0] < 0)
			return;
		// error: no panel!

		idMap = squash_ids(vcv_mod_ids);
		// printf("p.modules_used: [");
		// for (auto &m : p.modules_used) {
		// 	printf("%s, ", m.name);
		// }
		// printf("]\n");

		// printf("vcv_mod_ids (before): [");
		// for (auto v : vcv_mod_ids) {
		// 	printf("%d, ", v);
		// }
		// printf("]\n");

		// printf("idMap (after): [");
		// for (auto v : idMap) {
		// 	printf("%d: %d, ", v.first, v.second);
		// }
		// printf("]\n");
	}

	void generateStaticKnobList()
	{
		int i = 0;
		for (auto &param : paramData) {
			p.static_knobs[i].module_id = idMap[param.moduleID];
			p.static_knobs[i].param_id = param.paramID;
			p.static_knobs[i].value = param.value;
			i++;
		}
		p.num_static_knobs = i;
	}

	void generateMappedKnobList()
	{
		int i = 0;
		for (auto &map : mapData) {
			if ((map.src.objType == LabelButtonID::Types::Knob) && (map.dst.objType == map.src.objType)) {
				p.mapped_knobs[i].module_id = idMap[map.dst.moduleID];
				p.mapped_knobs[i].param_id = map.dst.objID;
				p.mapped_knobs[i].panel_knob_id = map.src.objID;
				i++;
			}
		}
		p.num_mapped_knobs = i;
	}

	void generateNodeList()
	{
		for (auto &mn : p.module_nodes) {
			for (int i = 0; i < MAX_JACKS_PER_MODULE; i++)
				mn[i] = 0;
		}

		int node_i = 1;
		p.num_nets = 0;
		auto jackInRange = [](int jackid) { return (jackid >= 0) && (jackid < MAX_JACKS_PER_MODULE); };
		for (auto &cable : jackData) {
			if (cable.connected && jackInRange(cable.receivedJackId) && jackInRange(cable.sendingJackId) &&
				cable.receivedModuleId >= 0 && cable.sendingModuleId >= 0)
			{
				auto out_mod = idMap[cable.receivedModuleId];
				auto out_jack = cable.receivedJackId + ModuleFactory::getOutJackOffset(p.modules_used[out_mod]);
				auto in_mod = idMap[cable.sendingModuleId];
				auto in_jack = cable.sendingJackId;

				auto &out_node = p.module_nodes[out_mod][out_jack];
				auto &in_node = p.module_nodes[in_mod][in_jack];

				if (out_node > 0 && in_node > 0) {
					mergeNodes(in_node, out_node);
				} else if (in_node > 0) {
					out_node = in_node;
				} else if (out_node > 0) {
					in_node = out_node;
				} else {
					out_node = node_i;
					in_node = node_i;
					node_i++;
				}

				// FixMe: non-node code:
				out_jack = cable.receivedJackId;
				// scan existing nets for same output jack
				bool found = false;
				for (int j = 0; j < p.num_nets; j++) {
					if (p.nets[j].jacks[0].jack_id == out_jack && p.nets[j].jacks[0].module_id == out_mod) {
						auto num_jacks = p.nets[j].num_jacks;
						p.nets[j].jacks[num_jacks].jack_id = in_jack;
						p.nets[j].jacks[num_jacks].module_id = in_mod;
						p.nets[j].num_jacks++;
						found = true;
						break;
					}
				}
				if (!found) {
					p.nets[p.num_nets].jacks[0].jack_id = out_jack;
					p.nets[p.num_nets].jacks[0].module_id = out_mod;
					p.nets[p.num_nets].jacks[1].jack_id = in_jack;
					p.nets[p.num_nets].jacks[1].module_id = in_mod;
					p.nets[p.num_nets].num_jacks = 2;
					p.num_nets++;
				}
			}
		}
		// Todo: fix this function to only assign unique nums for jacks that exist on the module
		// Or, do it in the patch reader?
		// assignUniqueNumToEmptyNodes(node_i);
	}

	void createPatch()
	{
		generateModuleList();
		generateStaticKnobList();
		generateMappedKnobList();
		generateNodeList();
	}

	static std::string printPatchStructText(std::string patchName, const Patch &patch)
	{
		std::string s;
		s = "#include \"patch.hh\"\n";
		s += "static const Patch " + patchName + " = { \n";

		// Module List
		s += "    .modules_used = {\n";
		for (int i = 0; i < patch.num_modules; i++) {
			s += "        \"";
			s += patch.modules_used[i].name;
			s += "\",\n";
		}
		s += "    },\n";
		s += "    .num_modules = " + std::to_string(patch.num_modules) + ",\n";
		s += "\n";

		// Nodes
		s += "    .module_nodes = {{\n";
		for (int i = 0; i < patch.num_modules; i++) {
			s += "        // ";
			s += patch.modules_used[i].name;
			s += "\n";
			s += "        {";
			for (int j = 0; j < MAX_JACKS_PER_MODULE; j++) {
				s += std::to_string(patch.module_nodes[i][j]);
				s += ", ";
			}
			s += "},\n";
		}
		s += "    }},\n";
		s += "\n";

		// FixMe: non-node code:
		// Net List
		s += "    .nets = {{\n";
		for (int i = 0; i < patch.num_nets; i++) {
			s += "        {\n";
			s += "            .num_jacks = " + std::to_string(patch.nets[i].num_jacks) + ",\n";
			s += "            .jacks = {{\n";

			for (int j = 0; j < patch.nets[i].num_jacks; j++) {
				s += "                {";
				s += ".module_id = " + std::to_string(patch.nets[i].jacks[j].module_id) + ", ";
				s += ".jack_id = " + std::to_string(patch.nets[i].jacks[j].jack_id) + "},\n";
			}

			s += "            }},\n";

			s += "        },\n";
		}
		s += "    }},\n";
		s += "    .num_nets = " + std::to_string(patch.num_nets) + ",\n";
		s += "\n";

		// Static knobs
		s += "    .static_knobs = {{\n";
		for (int i = 0; i < patch.num_static_knobs; i++) {
			const auto &knob = patch.static_knobs[i];
			s += "        {";
			s += ".module_id = " + std::to_string(knob.module_id) + ", ";
			s += ".param_id = " + std::to_string(knob.param_id) + ", ";
			s += ".value = " + std::to_string(knob.value) + "f},\n";
		}
		s += "    }},\n";
		s += "    .num_static_knobs = " + std::to_string(patch.num_static_knobs) + ",\n";
		s += "\n";

		s += "    .mapped_knobs = {{\n";
		for (int i = 0; i < patch.num_mapped_knobs; i++) {
			const auto &knob = patch.mapped_knobs[i];
			s += "        {";
			s += ".module_id = " + std::to_string(knob.module_id) + ", ";
			s += ".param_id = " + std::to_string(knob.param_id) + ", ";
			s += ".panel_knob_id = " + std::to_string(knob.panel_knob_id) + "},\n";
		}
		s += "    }},\n";
		s += "    .num_mapped_knobs = " + std::to_string(patch.num_mapped_knobs) + ",\n";
		s += "\n";

		s += "};\n";

		return s;
	}

	static std::map<int, int> squash_ids(std::vector<int> ids)
	{
		std::map<int, int> s;

		int i = 0;
		for (auto id : ids) {
			s[id] = i++;
		}
		return s;
	}

private:
	Patch &p;

	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<Mapping> mapData;
	std::map<int, int> idMap;

	// squashes module ids so that 0 = panel and increments upwards
	void _cleanup_module_ids();

	void mergeNodes(uint8_t old_num, uint8_t new_num)
	{
		for (int mod_i = 0; mod_i < MAX_MODULES_IN_PATCH; mod_i++) {
			for (int jack_i = 0; jack_i < MAX_JACKS_PER_MODULE; jack_i++) {
				if (p.module_nodes[mod_i][jack_i] == old_num)
					p.module_nodes[mod_i][jack_i] = new_num;
			}
		}
	}

	void assignUniqueNumToEmptyNodes(unsigned long starting_node_i)
	{
		for (int mod_i = 0; mod_i < MAX_MODULES_IN_PATCH; mod_i++) {
			// int num_jacks = ModuleFactory::getNumJacks();
			for (int jack_i = 0; jack_i < MAX_JACKS_PER_MODULE; jack_i++) {
				if (p.module_nodes[mod_i][jack_i] == 0) {
					p.module_nodes[mod_i][jack_i] = starting_node_i++;
				}
			}
		}
	}
};

