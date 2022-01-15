#include "patch_writer.hpp"
#include "patch_convert/patch_to_yaml.hh"
//#include "util/countzip.hh"
#include <algorithm>

#include "ryml_serial.hh"

PatchFileWriter::PatchFileWriter(std::vector<ModuleID> modules)
{
	ph.header_version = 1;
	setModuleList(modules);
}

void PatchFileWriter::setPatchName(std::string patchName)
{
	ph.patch_name = patchName.c_str();
}

void PatchFileWriter::setModuleList(std::vector<ModuleID> &modules)
{
	std::vector<int> vcv_mod_ids;

	// Reserved for PANEL
	vcv_mod_ids.push_back(-1);
	pd.module_slugs.push_back("");

	for (auto &mod : modules) {
		if (mod.typeID.is_equal("PANEL_8") || mod.typeID.is_equal("PanelMedium")) {
			// if (strcmp(mod.typeID.cstr(), "PANEL_8") == 0) {
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

void PatchFileWriter::setJackList(std::vector<JackStatus> &jacks)
{
	auto validJackId = [](int jackid) { return (jackid >= 0) /*&& (jackid < MAX_JACKS_PER_MODULE)*/; };
	pd.int_cables.clear();

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
	ph.num_int_cables = pd.int_cables.size();
}

void PatchFileWriter::setParamList(std::vector<ParamStatus> &params)
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

void PatchFileWriter::addMaps(std::vector<Mapping> maps)
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
				.curve_type = 0,
				.min = m.range_min,
				.max = m.range_max,
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
				std::find_if(pd.mapped_outs.begin(), pd.mapped_outs.end(), [panel_jack = m.src.objID](const auto &x) {
					return x.panel_jack_id == panel_jack;
				});

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

ByteBlock::DataType PatchFileWriter::printPatchBinary()
{
	ByteBlock v;

	auto *header = reinterpret_cast<unsigned char *>(&ph);
	v.printRaw(header, sizeof(ph));

	for (size_t i = 0; i < pd.module_slugs.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.module_slugs[i]), sizeof(pd.module_slugs[i]));

	for (size_t i = 0; i < pd.int_cables.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.int_cables[i]), sizeof(pd.int_cables[i]));

	for (size_t i = 0; i < pd.mapped_ins.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.mapped_ins[i]), sizeof(pd.mapped_ins[i]));

	for (size_t i = 0; i < pd.mapped_outs.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.mapped_outs[i]), sizeof(pd.mapped_outs[i]));

	for (size_t i = 0; i < pd.static_knobs.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.static_knobs[i]), sizeof(pd.static_knobs[i]));

	for (size_t i = 0; i < pd.mapped_knobs.size(); i++)
		v.printRaw(reinterpret_cast<unsigned char *>(&pd.mapped_knobs[i]), sizeof(pd.mapped_knobs[i]));

	return v.data;
}

std::string PatchFileWriter::printPatchYAML()
{
	return patch_to_yaml_string(ph, pd);

	// ryml::Tree tree;
	// ryml::NodeRef root = tree.rootref();
	// root |= ryml::MAP;

	// root["PatchHeader"] << ph;

	// ryml::NodeRef data = root["PatchData"];
	// data |= ryml::MAP;

	// ryml::NodeRef slugs = data["module_slugs"];
	// slugs |= ryml::MAP;
	// for (auto [i, x] : enumerate(pd.module_slugs)) {
	// 	auto idx_s = std::to_string(i);
	// 	ryml::csubstr idx(idx_s.c_str(), idx_s.length());
	// 	ryml::csubstr slug(x.c_str(), x.length());
	// 	slugs.append_child() << ryml::key(idx) << slug;
	// }

	// ryml::NodeRef int_cables = data["int_cables"];
	// int_cables |= ryml::SEQ;
	// for (auto &x : pd.int_cables) {
	// 	ryml::NodeRef el = int_cables.append_child({ryml::MAP});
	// 	el["out"] << x.out;
	// 	el["ins"] |= ryml::SEQ;
	// 	for (auto [in_i, in] : enumerate(x.ins)) {
	// 		if (in.jack_id < 0 || in.module_id < 0)
	// 			break;
	// 		el["ins"][in_i] << in;
	// 	}
	// }

	// ryml::NodeRef mapped_ins = data["mapped_ins"];
	// mapped_ins |= ryml::SEQ;
	// for (auto &x : pd.mapped_ins) {
	// 	ryml::NodeRef el = mapped_ins.append_child({ryml::MAP});
	// 	el["panel_jack_id"] << x.panel_jack_id;
	// 	el["ins"] |= ryml::SEQ;
	// 	for (auto [in_i, in] : enumerate(x.ins)) {
	// 		if (in.jack_id < 0 || in.module_id < 0)
	// 			break;
	// 		el["ins"][in_i] << in;
	// 	}
	// }

	// ryml::NodeRef mapped_outs = data["mapped_outs"];
	// mapped_outs |= ryml::SEQ;
	// for (auto &x : pd.mapped_outs) {
	// 	ryml::NodeRef el = mapped_outs.append_child({ryml::MAP});
	// 	el["panel_jack_id"] << x.panel_jack_id;
	// 	el["out"] << x.out;
	// }

	// ryml::NodeRef static_knobs = data["static_knobs"];
	// static_knobs |= ryml::SEQ;
	// for (auto &x : pd.static_knobs) {
	// 	ryml::NodeRef el = static_knobs.append_child({ryml::MAP});
	// 	el["module_id"] << x.module_id;
	// 	el["param_id"] << x.param_id;
	// 	el["value"] << x.value;
	// }

	// ryml::NodeRef mapped_knobs = data["mapped_knobs"];
	// mapped_knobs |= ryml::SEQ;
	// for (auto &x : pd.mapped_knobs) {
	// 	ryml::NodeRef el = mapped_knobs.append_child({ryml::MAP});
	// 	el["module_id"] << x.module_id;
	// 	el["param_id"] << x.param_id;
	// 	el["curve_type"] << x.curve_type;
	// 	el["min"] << x.min;
	// 	el["max"] << x.max;
	// }

	// return ryml::emitrs<std::string>(tree);
}

std::map<int, int> PatchFileWriter::squash_ids(std::vector<int> ids)
{
	std::map<int, int> s;

	int i = 0;
	for (auto id : ids) {
		s[id] = i++;
	}
	return s;
}

PatchData &PatchFileWriter::get_data()
{
	return pd;
}
