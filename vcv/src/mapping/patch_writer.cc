#include "patch_writer.hh"
#include "mapping/midi_modules.hh"
#include "mapping/module_directory.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "patch_convert/ryml/ryml_serial.hh"
#include <algorithm>

PatchFileWriter::PatchFileWriter(std::vector<ModuleID> modules, int64_t hubModuleId)
	: hubModuleId{hubModuleId} {
	setModuleList(modules);
	pd.knob_sets.clear();
	pd.mapped_ins.clear();
	pd.mapped_outs.clear();

	moduleStateDataJ = json_object();
	moduleArrayJ = json_array();
}

PatchFileWriter::~PatchFileWriter() {
	json_decref(moduleStateDataJ);
}

void PatchFileWriter::setPatchName(std::string patchName) {
	pd.patch_name = patchName.c_str();
}

void PatchFileWriter::setPatchDesc(std::string patchDesc) {
	pd.description = patchDesc.c_str();
}

void PatchFileWriter::setMidiSettings(MidiModuleIds &ids, MetaModule::MIDI::Settings const &settings) {
	midiModuleIds = ids;
	midiSettings = settings;
}

void PatchFileWriter::setModuleList(std::vector<ModuleID> &modules) {
	std::vector<int64_t> vcv_mod_ids;

	// Reserved for PANEL
	vcv_mod_ids.push_back(-1);
	pd.module_slugs.push_back("");

	for (auto &mod : modules) {
		if (ModuleDirectory::isHub(mod.slug)) {
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

void PatchFileWriter::setCableList(std::vector<CableMap> &cables) {
	pd.int_cables.clear();

	for (auto &cable : cables) {
		auto in_jack = cable.receivedJackId;
		auto out_jack = cable.sendingJackId;

		if (out_jack < 0 || in_jack < 0)
			continue;

		if (cable.sendingModuleId == hubModuleId) {
			mapInputJack(cable);
			continue;

		} else if (cable.receivedModuleId == hubModuleId) {
			mapOutputJack(cable);
			continue;

		} else if (cable.sendingModuleId == midiModuleIds.midiCV) {
			mapMidiCVJack(cable);
			continue;

		} else if (cable.sendingModuleId == midiModuleIds.midiGate) {
			mapMidiGateJack(cable);
			continue;

		} else if (cable.sendingModuleId == midiModuleIds.midiCC) {
			mapMidiCCJack(cable);
			continue;

		} else if (cable.sendingModuleId == midiModuleIds.midiMaps) {
			//MIDI Maps has no jacks!
			continue;
		}

		if (!idMap.contains(cable.receivedModuleId) || !idMap.contains(cable.sendingModuleId))
			continue;

		auto in_mod = idMap[cable.receivedModuleId];
		auto out_mod = idMap[cable.sendingModuleId];

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
				.color = cable.lv_color_full,
			});
		}
	}
}

void PatchFileWriter::setParamList(std::vector<ParamMap> &params) {
	pd.static_knobs.clear();
	for (auto &param : params) {
		pd.static_knobs.push_back({
			.module_id = idMap[param.moduleID],
			.param_id = static_cast<uint16_t>(param.paramID),
			.value = param.value,
		});
	}
}

void PatchFileWriter::addModuleStateJson(rack::Module *module) {
	if (!module)
		return; //invalid moduel

	if (!idMap.contains(module->id))
		return; //module not recognized

	json_t *dataJ = module->dataToJson();

	if (!dataJ)
		return; // Do nothing if module has no state to store

	json_t *moduleJ = json_object();

	auto id = idMap[module->id];
	json_object_set_new(moduleJ, "id", json_integer(id));

	if (module->model && module->model->plugin)
		json_object_set_new(moduleJ, "plugin", json_string(module->model->plugin->slug.c_str()));

	if (module->model)
		json_object_set_new(moduleJ, "model", json_string(module->model->slug.c_str()));

	if (module->model && module->model->plugin)
		json_object_set_new(moduleJ, "version", json_string(module->model->plugin->version.c_str()));

	json_object_set_new(moduleJ, "data", dataJ);

	json_array_append_new(moduleArrayJ, moduleJ);
}

void PatchFileWriter::addKnobMapSet(unsigned knobSetId, std::string_view knobSetName) {
	if (knobSetId >= pd.knob_sets.size())
		pd.knob_sets.resize(knobSetId + 1);
	pd.knob_sets[knobSetId].name = knobSetName;
}

void PatchFileWriter::addKnobMaps(unsigned panelKnobId, unsigned knobSetId, const std::span<const Mapping> maps) {
	if (knobSetId >= pd.knob_sets.size())
		pd.knob_sets.resize(knobSetId + 1);

	for (const auto &m : maps) {
		if (!idMap.contains(m.moduleId)) {
			printf("Skipping knob mapping to module not supported by MetaModule: %lld\n", (long long)m.moduleId);
			continue;
		}
		pd.knob_sets[knobSetId].set.push_back({
			.panel_knob_id = static_cast<uint16_t>(panelKnobId),
			.module_id = idMap[m.moduleId],
			.param_id = static_cast<uint16_t>(m.paramId),
			.curve_type = 0,
			.min = m.range_min,
			.max = m.range_max,
			.alias_name = "", //TODO
		});
	}
}

// Presumes the map has already been verified that the sendingModuleId is the hub we're using
// And the jack ids are valid
// and the receivedModuleId is in our module list
void PatchFileWriter::mapInputJack(const CableMap &map) {

	// Look for an existing entry to this panel input jack
	auto found = std::find_if(pd.mapped_ins.begin(), pd.mapped_ins.end(), [=](const auto &x) {
		return x.panel_jack_id == (uint32_t)map.sendingJackId;
	});

	if (found != pd.mapped_ins.end()) {
		// If we already have an entry for this panel jack, append a new module input jack to the ins vector
		found->ins.push_back({
			.module_id = static_cast<uint16_t>(idMap[map.receivedModuleId]),
			.jack_id = static_cast<uint16_t>(map.receivedJackId),
		});
	} else {
		// Make a new entry:
		pd.mapped_ins.push_back({
			.panel_jack_id = static_cast<uint32_t>(map.sendingJackId),
			.ins = {{
				{
					.module_id = static_cast<uint16_t>(idMap[map.receivedModuleId]),
					.jack_id = static_cast<uint16_t>(map.receivedJackId),
				},
			}},
			.alias_name = "",
		});
	}
}

// Presumes the map has already been verified that the sendingModuleId is the hub we're using
// And the jack ids are valid
// and the receivedModuleId is in our module list
void PatchFileWriter::mapOutputJack(const CableMap &map) {

	// Update the mapped_outs entry if there already is one with the same panel_jack_id (Note that this is
	// an error, since we can't have multiple outs assigned to a net, but we're going to roll with it).
	// otherwise push it to the vector

	// Look for an existing entry:
	auto found = std::find_if(pd.mapped_outs.begin(), pd.mapped_outs.end(), [=](const auto &x) {
		return x.panel_jack_id == (uint32_t)map.receivedJackId;
	});

	if (found != pd.mapped_outs.end()) {
		found->out.module_id = static_cast<uint16_t>(idMap[map.sendingModuleId]);
		found->out.jack_id = static_cast<uint16_t>(map.sendingJackId);
		// Todo: Log error: multiple module outputs mapped to same panel output jack
	} else {
		// Make a new entry:
		pd.mapped_outs.push_back({
			.panel_jack_id = static_cast<uint32_t>(map.receivedJackId),
			.out =
				{
					.module_id = static_cast<uint16_t>(idMap[map.sendingModuleId]),
					.jack_id = static_cast<uint16_t>(map.sendingJackId),
				},
			.alias_name = "",
		});
	}
}

void PatchFileWriter::mapMidiCVJack(CableMap &cable) {
	// if (midiSettings.CV.channels == 1) {
	if (cable.sendingJackId == 0)
		cable.sendingJackId = MidiMonoNoteJack;

	else if (cable.sendingJackId == 1)
		cable.sendingJackId = MidiMonoGateJack;

	else if (cable.sendingJackId == 2)
		cable.sendingJackId = MidiMonoVelJack;

	else if (cable.sendingJackId == 3)
		cable.sendingJackId = MidiMonoAftertouchJack;
	// }
	//TODO handle polyphony (midiSettings.CV.channels > 1)

	else if (cable.sendingJackId == 4)
		cable.sendingJackId = MidiPitchWheelJack;

	else if (cable.sendingJackId == 5)
		cable.sendingJackId = MidiModWheelJack;

	//MidiRetriggerJack (896 = VCV module jack 6) to MidiContinueJack (901 = VCV module jack 11)
	else if (cable.sendingJackId < 12)
		cable.sendingJackId = MidiRetriggerJack + (cable.sendingJackId - 6);

	mapInputJack(cable);
}

void PatchFileWriter::mapMidiGateJack(CableMap &cable) {
	if (cable.sendingJackId <= (int)midiSettings.gate.notes.size()) {
		auto notenum = midiSettings.gate.notes[cable.sendingJackId];
		printf("Gate module: jack %d is note %d\n", cable.sendingJackId, notenum);
		cable.sendingJackId = MidiGateNote0 + notenum;
		mapInputJack(cable);
	}
}

void PatchFileWriter::mapMidiCCJack(CableMap &cable) {
	if (cable.sendingJackId <= (int)midiSettings.CCCV.CCnums.size()) {
		auto ccnum = midiSettings.CCCV.CCnums[cable.sendingJackId];
		printf("CC CV module: jack %d is CC %d\n", cable.sendingJackId, ccnum);
		cable.sendingJackId = MidiCC0 + ccnum;
		mapInputJack(cable);
	}
}

std::string PatchFileWriter::printPatchYAML() {
	auto patch_yml = patch_to_yaml_string(pd);
	json_object_set_new(moduleStateDataJ, "vcvModuleStates", moduleArrayJ);

	std::string moduleStateStr;
	auto sz = json_dumpb(moduleStateDataJ, nullptr, 0, JSON_INDENT(0));
	if (sz > 0) {
		moduleStateStr.resize(sz + 1);
		json_dumpb(moduleStateDataJ, moduleStateStr.data(), sz, JSON_INDENT(0));
	}
	auto data_yml = json_to_yml(moduleStateStr);

	patch_yml.append("\n");
	patch_yml.append(data_yml);

	return patch_yml;
}

std::map<int64_t, uint16_t> PatchFileWriter::squash_ids(std::vector<int64_t> ids) {
	std::map<int64_t, uint16_t> s;

	int i = 0;
	for (auto id : ids) {
		s[id] = i++;
	}
	return s;
}

PatchData &PatchFileWriter::get_data() {
	return pd;
}
