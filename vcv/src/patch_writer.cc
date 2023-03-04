#include "patch_writer.hh"
#include "patch_convert/patch_to_yaml.hh"
#include <algorithm>

#include "patch_convert/ryml/ryml_serial.hh"

PatchFileWriter::PatchFileWriter(std::vector<ModuleID> modules) { setModuleList(modules); }

void PatchFileWriter::setPatchName(std::string patchName) { pd.patch_name = patchName.c_str(); }

void PatchFileWriter::setPatchDesc(std::string patchDesc) { pd.description = patchDesc.c_str(); }

void PatchFileWriter::setModuleList(std::vector<ModuleID> &modules)
{
	std::vector<int64_t> vcv_mod_ids;

	// Reserved for PANEL
	vcv_mod_ids.push_back(-1);
	pd.module_slugs.push_back("");

	for (auto &mod : modules) {
		if (mod.slug.is_equal("PANEL_8") || mod.slug.is_equal("PanelMedium")) {
			pd.module_slugs[0] = mod.slug;
			vcv_mod_ids[0] = mod.id;
		} else {
			pd.module_slugs.push_back(mod.slug);
			vcv_mod_ids.push_back(mod.id);
		}
	}
	if (vcv_mod_ids[0] < 0)
		return;
	// error: no panel!

	idMap = squash_ids(vcv_mod_ids);
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
				// If an int_cable entry exists for this output jack, add a new input jack to the ins vector
				found->ins.push_back({
					.module_id = static_cast<uint16_t>(in_mod),
					.jack_id = static_cast<uint16_t>(in_jack),
				});
			} else {
				// Make a new entry:
				pd.int_cables.push_back({
					.out = {static_cast<uint16_t>(out_mod), static_cast<uint16_t>(out_jack)},
					.ins = {{
						{
							.module_id = static_cast<uint16_t>(in_mod),
							.jack_id = static_cast<uint16_t>(in_jack),
						},
					}},
				});
			}
		}
	}
}

void PatchFileWriter::setParamList(std::vector<ParamStatus> &params)
{
	pd.static_knobs.clear();
	for (auto &param : params) {
		pd.static_knobs.push_back({
			.module_id = idMap[param.moduleID],
			.param_id = static_cast<uint16_t>(param.paramID),
			.value = param.value,
		});
	}
}

// void rectify_midi_maps(std::vector<Mapping> &maps)
//{
//	int num_midinote_mappings = std::count_if(
//		maps.begin(), maps.end(), [](auto &m) { return m.src.objType == LabelButtonID::Types::MidiNote; });
//	int num_midigate_mappings = std::count_if(
//		maps.begin(), maps.end(), [](auto &m) { return m.src.objType == LabelButtonID::Types::MidiGate; });

//	int num_midi_mappings = std::max(num_midinote_mappings, num_midigate_mappings);
//	//polyphony number

//	uint16_t note_src_id = 256;//first MidiNote
//	for(auto &m :maps) {
//		if (m.src.objType == LabelButtonID::Types::MidiNote)
//			m.src.objID = note_src_id;
//	}
//}

void PatchFileWriter::addMaps(std::vector<Mapping> &maps)
{
	pd.mapped_knobs.clear();
	pd.mapped_ins.clear();
	pd.mapped_outs.clear();

	for (const auto &m : maps) {
		if (m.dst.objType == LabelButtonID::Types::Knob) {
			pd.mapped_knobs.push_back({
				.panel_knob_id = static_cast<uint16_t>(m.src.objID),
				.module_id = idMap[m.dst.moduleID],
				.param_id = static_cast<uint16_t>(m.dst.objID),
				.curve_type = 0,
				.min = m.range_min,
				.max = m.range_max,
				.alias_name = m.alias_name.c_str(),
			});
		}

		if (m.dst.objType == LabelButtonID::Types::InputJack) {
			// Look for an existing entry:
			auto found = std::find_if(pd.mapped_ins.begin(),
									  pd.mapped_ins.end(),
									  [panel_jack = static_cast<uint32_t>(m.src.objID)](const auto &x) {
										  return x.panel_jack_id == panel_jack;
									  });

			if (found != pd.mapped_ins.end()) {
				// If we already have an entry for this panel jack, append a new module input jack to the ins vector
				found->ins.push_back({
					.module_id = static_cast<uint16_t>(idMap[m.dst.moduleID]),
					.jack_id = static_cast<uint16_t>(m.dst.objID),
				});
			} else {
				// Make a new entry:
				pd.mapped_ins.push_back({
					.panel_jack_id = static_cast<uint32_t>(m.src.objID),
					.ins = {{
						{
							.module_id = static_cast<uint16_t>(idMap[m.dst.moduleID]),
							.jack_id = static_cast<uint16_t>(m.dst.objID),
						},
					}},
				});
			}
		}

		if (m.dst.objType == LabelButtonID::Types::OutputJack) {
			// Update the mapped_outs entry if there already is one with the same panel_jack_id (Note that this is
			// an error, since we can't have multiple outs assigned to a net, but we're going to roll with it).
			// otherwise push it to the vector

			// Look for an existing entry:
			auto found = std::find_if(pd.mapped_outs.begin(),
									  pd.mapped_outs.end(),
									  [panel_jack = static_cast<uint32_t>(m.src.objID)](const auto &x) {
										  return x.panel_jack_id == panel_jack;
									  });

			if (found != pd.mapped_outs.end()) {
				// Update:
				found->out.module_id = static_cast<uint16_t>(idMap[m.dst.moduleID]);
				found->out.jack_id = static_cast<uint16_t>(m.dst.objID);
				// Todo: Log error: multiple module outputs mapped to same panel output jack
			} else {
				// Make a new entry:
				pd.mapped_outs.push_back({
					.panel_jack_id = static_cast<uint32_t>(m.src.objID),
					.out =
						{
							.module_id = static_cast<uint16_t>(idMap[m.dst.moduleID]),
							.jack_id = static_cast<uint16_t>(m.dst.objID),
						},
				});
			}
		}
	}
}

std::string PatchFileWriter::printPatchYAML() { return patch_to_yaml_string(pd); }

std::map<int64_t, uint16_t> PatchFileWriter::squash_ids(std::vector<int64_t> ids)
{
	std::map<int64_t, uint16_t> s;

	int i = 0;
	for (auto id : ids) {
		s[id] = i++;
	}
	return s;
}

PatchData &PatchFileWriter::get_data() { return pd; }
