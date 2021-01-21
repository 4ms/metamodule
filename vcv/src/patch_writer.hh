#pragma once
#include "CommData.h"
#include "patch/patch.hh"

class PatchWriter {

public:
	PatchWriter(Patch &patch)
		: p{patch}
	{}

	void addCable(JackStatus cable)
	{
		jackData.push_back(cable);
	}
	void addMappedParam(Mapping map)
	{
		mapData.push_back(map);
	}

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
				addMappedParam(m);
			}
			if (m.dst.objType == LabelButtonID::Types::InputJack) {
				addCable({
					.sendingJackId = m.dst.objID,
					.receivedJackId = m.src.objID,
					.sendingModuleId = m.dst.moduleID,
					.receivedModuleId = m.src.moduleID,
					.connected = true,
				});
			}
			if (m.dst.objType == LabelButtonID::Types::OutputJack) {
				addCable({
					.sendingJackId = m.src.objID,
					.receivedJackId = m.dst.objID,
					.sendingModuleId = m.src.moduleID,
					.receivedModuleId = m.dst.moduleID,
					.connected = true,
				});
			}
		}
	}

	void createPatch()
	{
		// Todo: map module IDs from VCV's unique ID to sequential IDs where panel = 0

		int i = 0;
		for (auto &mod : moduleData) {
			p.modules_used[i] = mod.typeID;
			i++;
		}
		p.num_modules = i;

		i = 0;
		for (auto &param : paramData) {
			p.static_knobs[i].module_id = param.moduleID;
			p.static_knobs[i].param_id = param.paramID;
			p.static_knobs[i].value = param.value;
			i++;
		}
		p.num_static_knobs = i;

		i = 0;
		for (auto &map : mapData) {
			if ((map.src.objType == LabelButtonID::Types::Knob) && (map.dst.objType == map.src.objType)) {
				p.mapped_knobs[i].module_id = map.dst.moduleID;
				p.mapped_knobs[i].param_id = map.dst.objID;
				p.mapped_knobs[i].panel_knob_id = map.src.objID;
				i++;
			}
		}
		p.num_mapped_knobs = i;

		for (auto &mn : p.module_nodes) {
			for (int i = 0; i < MAX_JACKS_PER_MODULE; i++)
				mn[i] = 0;
		}

		int node_i = 1;
		auto jackInRange = [](int jackid) { return (jackid >= 0) && (jackid < MAX_JACKS_PER_MODULE); };
		for (auto &cable : jackData) {
			if (cable.connected && jackInRange(cable.receivedJackId) && jackInRange(cable.sendingJackId) &&
				cable.receivedModuleId >= 0 && cable.sendingModuleId >= 0)
			{
				auto out_mod = cable.receivedModuleId;
				auto out_jack = cable.receivedJackId + ModuleFactory::getOutJackOffset(p.modules_used[out_mod]);
				auto in_mod = cable.sendingModuleId;
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
			}
		}

		// Todo: fix this function to only assign unique nums for jacks that exist on the module
		// Or, do it in the patch reader?
		// assignUniqueNumToEmptyNodes(node_i);
	}

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

	static std::string printPatchStructText(std::string patchName, const Patch &patch)
	{
		std::string s;
		s = "#include \"patch.hh\"\n";
		s += "static const Patch " + patchName +
			 " = { \n"
			 "    .modules_used = {\n";
		for (int i = 0; i < patch.num_modules; i++) {
			s += "        \"";
			s += patch.modules_used[i].name;
			s += "\",\n";
		}
		s += "    },\n";
		s += "    .num_modules = " + std::to_string(patch.num_modules) + ",\n";
		s += "\n";

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

private:
	Patch &p;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<Mapping> mapData;

	// squashes module ids so that 0 = panel and increments upwards
	void _cleanup_module_ids();

	// void _addModule(int id, ModuleTypeSlug slug);
	// void _addCable(Jack out, Jack in);
	// void _addStaticParam(StaticParam pr);
	// void _addMappedParam(MappedParam pr);
};

