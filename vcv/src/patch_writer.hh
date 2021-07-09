#pragma once
#include "CommData.h"
#include "patch/patch.hh"
#include <map>
#include <vector>

struct PatchData {
	ModuleTypeSlug patch_name;
	std::vector<ModuleTypeSlug> module_slugs;
	std::vector<InternalCable> int_cables;
	std::vector<MappedInputJack> mapped_ins;
	std::vector<MappedOutputJack> mapped_outs;
	std::vector<StaticParam> static_knobs;
	std::vector<MappedKnob> mapped_knobs;
};

class PatchFileWriter {
	PatchHeader ph;
	PatchData pd;
	std::map<int, int> idMap;

public:
	PatchFileWriter() = default;

	PatchFileWriter(std::vector<ModuleID> modules)
	{
		setModuleList(modules);
	}

	void setPatchName(std::string patchName)
	{
		ph.name_strlen = std::min(patchName.size(), pd.patch_name.capacity);
		pd.patch_name = patchName.c_str();
	}

	void setModuleList(std::vector<ModuleID> &modules)
	{
		std::vector<int> vcv_mod_ids;

		// Reserved for PANEL
		vcv_mod_ids.push_back(-1);
		pd.module_slugs.push_back("");

		for (auto &mod : modules) {
			if (strcmp(mod.typeID.cstr(), "PANEL_8") == 0) {
				pd.module_slugs[0] = mod.typeID;
				vcv_mod_ids[0] = mod.id;
			} else {
				pd.module_slugs.push_back(mod.typeID);
				vcv_mod_ids.push_back(mod.id);
			}
		}
		ph.num_modules = pd.module_slugs.size();

		if (vcv_mod_ids[0] < 0)
			return;
		// error: no panel!

		idMap = squash_ids(vcv_mod_ids);
		ph.num_modules = modules.size();
	}

	void setJackList(std::vector<JackStatus> &jacks)
	{
		auto validJackId = [](int jackid) { return (jackid >= 0) && (jackid < MAX_JACKS_PER_MODULE); };

		for (auto &cable : jacks) {
			if (cable.connected && validJackId(cable.receivedJackId) && validJackId(cable.sendingJackId) &&
				cable.receivedModuleId >= 0 && cable.sendingModuleId >= 0)
			{
				auto out_mod = idMap[cable.receivedModuleId];
				auto out_jack = cable.receivedJackId;
				auto in_mod = idMap[cable.sendingModuleId];
				auto in_jack = cable.sendingJackId;

				// Look for an existing entry:
				auto found = std::find_if(pd.int_cables.begin(), pd.int_cables.end(), [=](const auto &x) {
					return x.out.jack_id == out_jack && x.out.module_id == out_mod;
				});

				if (found != pd.int_cables.end()) {
					// If int_cable entry exists, count number of in Jacks already in this entry
					int num_ins = 0;
					for (const auto &in : found->ins) {
						if (in.jack_id == -1 || in.module_id == -1)
							break;
						num_ins++;
					}
					// If there's room, append this new entry, otherwise do nothing
					if (num_ins < (MAX_CONNECTIONS_PER_NODE - 1)) {
						found->ins[num_ins] = {
							.module_id = static_cast<int16_t>(in_mod),
							.jack_id = static_cast<int16_t>(in_jack),
						};
						if ((num_ins + 1) < (MAX_CONNECTIONS_PER_NODE - 1)) {
							found->ins[num_ins + 1] = {-1, -1}; // terminator
						}
					}
					// else log error: too many jacks stacked together
				} else {
					// Make a new entry:
					pd.int_cables.push_back({
						.out = {static_cast<int16_t>(out_mod), static_cast<int16_t>(out_jack)},
						.ins = {{
							{
								.module_id = static_cast<int16_t>(in_mod),
								.jack_id = static_cast<int16_t>(in_jack),
							},
							{-1, -1}, // terminator
						}},
					});
				}
			}
		}
		ph.num_int_cables = jacks.size();
	}

	void setParamList(std::vector<ParamStatus> &params)
	{
		// paramData = params;
		pd.static_knobs.clear();
		for (auto &param : params) {
			pd.static_knobs.push_back({
				.module_id = static_cast<int16_t>(idMap[param.moduleID]),
				.param_id = static_cast<int16_t>(param.paramID),
				.value = param.value,
			});
		}
		ph.num_static_knobs = pd.static_knobs.size();
	}

	void addMaps(std::vector<Mapping> maps)
	{
		pd.mapped_knobs.clear();
		pd.mapped_ins.clear();
		pd.mapped_outs.clear();

		for (auto &m : maps) {
			if (m.dst.objType == LabelButtonID::Types::Knob) {
				pd.mapped_knobs.push_back({
					.panel_knob_id = static_cast<int16_t>(m.src.objID),
					.module_id = static_cast<int16_t>(idMap[m.dst.moduleID]),
					.param_id = static_cast<int16_t>(m.dst.objID),
				});
			}

			if (m.dst.objType == LabelButtonID::Types::InputJack) {
				// Look for an existing entry:
				auto found =
					std::find_if(pd.mapped_ins.begin(), pd.mapped_ins.end(), [panel_jack = m.src.objID](const auto &x) {
						return x.panel_jack_id == panel_jack;
					});

				if (found != pd.mapped_ins.end()) {
					// Count number of entries in ins
					int num_ins = 0;
					for (const auto &in : found->ins) {
						if (in.jack_id == -1 || in.module_id == -1)
							break;
						num_ins++;
					}
					// If there's room, append this new entry, otherwise do nothing
					if (num_ins < (MAX_CONNECTIONS_PER_NODE - 1)) {
						found->ins[num_ins] = {
							.module_id = static_cast<int16_t>(idMap[m.dst.moduleID]),
							.jack_id = static_cast<int16_t>(m.dst.objID),
						};
						if ((num_ins + 1) < (MAX_CONNECTIONS_PER_NODE - 1)) {
							found->ins[num_ins + 1] = {-1, -1}; // terminator
						}
					}
					// else log error: too many jacks stacked together
				} else {
					// Make a new entry:
					pd.mapped_ins.push_back({
						.panel_jack_id = m.src.objID,
						.ins = {{
							{
								.module_id = static_cast<int16_t>(idMap[m.dst.moduleID]),
								.jack_id = static_cast<int16_t>(m.dst.objID),
							},
							{-1, -1}, // terminator
						}},
					});
				}
			}

			if (m.dst.objType == LabelButtonID::Types::OutputJack) {
				// Update the mapped_outs entry if there already is one with the same panel_jack_id (Note that this is
				// an error, since we can't have multiple outs assigned to a net, but we're going to roll with it).
				// otherwise push it to the vector

				// Look for an existing entry:
				auto found =
					std::find_if(pd.mapped_outs.begin(),
								 pd.mapped_outs.end(),
								 [panel_jack = m.src.objID](const auto &x) { return x.panel_jack_id == panel_jack; });

				if (found != pd.mapped_outs.end()) {
					// Update:
					found->out.module_id = static_cast<int16_t>(idMap[m.dst.moduleID]);
					found->out.jack_id = static_cast<int16_t>(m.dst.objID);
					// Todo: Log error: multiple module outputs mapped to same panel output jack
				} else {
					// Make a new entry:
					pd.mapped_outs.push_back({
						.panel_jack_id = m.src.objID,
						.out =
							{
								.module_id = static_cast<int16_t>(idMap[m.dst.moduleID]),
								.jack_id = static_cast<int16_t>(m.dst.objID),
							},
					});
				}
			}
		}

		ph.num_mapped_knobs = pd.mapped_knobs.size();
		ph.num_mapped_ins = pd.mapped_ins.size();
		ph.num_mapped_outs = pd.mapped_outs.size();
	}

	struct ByteBlock {
		using DataType = std::vector<unsigned char>;
		DataType data;

		ByteBlock()
		{
			data.clear();
		}
		void print(uint32_t x)
		{
			printU32LE(x);
		}
		void printU32LE(uint32_t x)
		{
			data.push_back((x >> 0) & 0xFF);
			data.push_back((x >> 8) & 0xFF);
			data.push_back((x >> 16) & 0xFF);
			data.push_back((x >> 24) & 0xFF);
		}
	};

	ByteBlock::DataType printPatchBinary()
	{
		ByteBlock v;
		v.printU32LE(0x12345678);
		v.printU32LE(0x0A0B0C0D);
		return v.data;
	}

	std::string printJack(Jack &jack, std::string separator)
	{
		return "module_id: " + std::to_string(jack.module_id) + "\n" + separator +
			   "jack_id: " + std::to_string(jack.jack_id);
	}

	// std::string printJackItem(Jack &jack, std::string separator)
	// {
	// 	return "m: " + std::to_string(jack.module_id) + "\n" + separator + "j: " + std::to_string(jack.jack_id);
	// }
	std::string printPatchYAML()
	{
		std::string s;
		s = "PatchHeader:\n";
		s += "  header_version: " + std::to_string(ph.header_version) + "\n";
		s += "  name_strlen: " + std::to_string(ph.name_strlen) + "\n";
		s += "  num_modules: " + std::to_string(ph.num_modules) + "\n";
		s += "  num_int_cables: " + std::to_string(ph.num_int_cables) + "\n";
		s += "  num_mapped_ins: " + std::to_string(ph.num_mapped_ins) + "\n";
		s += "  num_mapped_outs: " + std::to_string(ph.num_mapped_outs) + "\n";
		s += "  num_static_knobs: " + std::to_string(ph.num_static_knobs) + "\n";
		s += "  num_mapped_knobs: " + std::to_string(ph.num_mapped_knobs) + "\n";
		s += "\n";
		s += "PatchData:\n";
		s += "  patch_name: ";
		s += pd.patch_name;
		s += "\n";

		s += "  module_slugs:\n";
		int i = 0;
		for (auto &x : pd.module_slugs) {
			s += "    " + std::to_string(i) + ": ";
			s += x.cstr();
			s += "\n";
			i++;
		}
		s += "\n";

		s += "  int_cables: \n";
		for (auto &x : pd.int_cables) {
			s += "      - out: \n";
			s += "          " + printJack(x.out, "          ") + "\n";
			s += "        ins: \n";
			for (auto &in : x.ins) {
				if (in.jack_id == -1 || in.module_id == -1)
					break;
				s += "          - " + printJack(in, "            ") + "\n";
			}
		}
		s += "\n";

		s += "  mapped_ins: \n";
		for (auto &x : pd.mapped_ins) {
			s += "      - panel_jack_id: " + std::to_string(x.panel_jack_id) + "\n";
			s += "        ins: \n";
			for (auto &in : x.ins) {
				if (in.jack_id == -1 || in.module_id == -1)
					break;
				s += "          - " + printJack(in, "            ") + ", \n";
			}
		}
		s += "\n";

		s += "  mapped_outs: \n";
		for (auto &x : pd.mapped_outs) {
			s += "    - panel_jack_id: " + std::to_string(x.panel_jack_id) + "\n";
			s += "      out: \n";
			s += "        " + printJack(x.out, "        ") + "\n";
		}
		s += "\n";

		s += "  static_knobs: \n";
		for (auto &x : pd.static_knobs) {
			s += "    - module_id: " + std::to_string(x.module_id) + "\n";
			s += "      param_id: " + std::to_string(x.param_id) + "\n";
			s += "      value: " + std::to_string(x.value) + "\n";
		}
		s += "\n";

		s += "  mapped_knobs: \n";
		for (auto &x : pd.mapped_knobs) {
			s += "    - panel_knob_id: " + std::to_string(x.panel_knob_id) + "\n";
			s += "      module_id: " + std::to_string(x.module_id) + "\n";
			s += "      param_id: " + std::to_string(x.param_id) + "\n";
			s += "      curve_type: " + std::to_string(x.curve_type) + "\n";
			s += "      range: " + std::to_string(x.range) + "\n";
			s += "      offset: " + std::to_string(x.offset) + "\n";
		}
		s += "\n";

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
};

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

	void createPatch()
	{
		generateModuleList();
		generateStaticKnobList();
		generateMappedKnobList();
		generateNodeList();
	}

	void generateModuleList()
	{
		std::vector<int> vcv_mod_ids;

		int i = 1;
		vcv_mod_ids.push_back(-1); // Reserved for PANEL
		for (auto &mod : moduleData) {
			if (strcmp(mod.typeID.cstr(), "PANEL_8") == 0) {
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
		auto validJackId = [](int jackid) { return (jackid >= 0) && (jackid < MAX_JACKS_PER_MODULE); };
		for (auto &cable : jackData) {
			if (cable.connected && validJackId(cable.receivedJackId) && validJackId(cable.sendingJackId) &&
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

		// Fill unused nodes
		unsigned unique_node_idx = MAX_NODES_IN_PATCH - 1;
		for (int mod_i = 0; mod_i < p.num_modules; mod_i++) {
			for (int node_i = 0; node_i < ModuleFactory::getNumJacks(p.modules_used[mod_i]); node_i++) {
				if (p.module_nodes[mod_i][node_i] == 0)
					p.module_nodes[mod_i][node_i] = unique_node_idx--;
			}
		}
	}

	static std::string printPatchStructText(std::string patchStructName, const Patch &patch)
	{
		std::string s;
		s = "#include \"patch.hh\"\n";
		s += "static const Patch " + patchStructName + " = { \n";

		// Patch name
		s += "    .patch_name = \"";
		s += patch.patch_name;
		s += "\",\n";

		// Module List
		s += "    .modules_used = {\n";
		for (int i = 0; i < patch.num_modules; i++) {
			s += "        \"";
			s += patch.modules_used[i].cstr();
			s += "\",\n";
		}
		s += "    },\n";
		s += "    .num_modules = " + std::to_string(patch.num_modules) + ",\n";
		s += "\n";

		// Nodes
		s += "    .module_nodes = {{\n";
		for (int i = 0; i < patch.num_modules; i++) {
			s += "        // ";
			s += patch.modules_used[i].cstr();
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

			for (unsigned j = 0; j < patch.nets[i].num_jacks; j++) {
				s += "                {";
				auto mod_id = patch.nets[i].jacks[j].module_id;
				auto jack_id = patch.nets[i].jacks[j].jack_id;
				s += ".module_id = " + std::to_string(mod_id) + ", ";
				s += ".jack_id = " + std::to_string(jack_id) + "},";
				s += "    // ";
				s += patch.modules_used[mod_id].cstr();
				s += ": ";
				// s += p
				s += "\n";
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
