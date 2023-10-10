#pragma once
#include "JackMap.hh"
#include "ModuleID.h"
#include "ParamMap.hh"
#include "jansson.h"
#include "mapping/mapping.hh"
#include "patch/patch.hh"
#include "patch_convert/patch_to_yaml.hh"
#include <map>
#include <rack.hpp>
#include <span>
#include <vector>

class PatchFileWriter {
public:
	struct MidiModuleIds {
		int64_t midiCV = -1;
		int64_t midiMaps = -1;
		int64_t midiGate = -1;
		int64_t midiCC = -1;
	};

	PatchFileWriter(std::vector<ModuleID> modules, int64_t hubModuleId);
	~PatchFileWriter();

	void setPatchName(std::string patchName);
	void setPatchDesc(std::string patchDesc);
	void setCableList(std::vector<CableMap> &jacks);
	void setParamList(std::vector<ParamMap> &params);
	void addModuleStateJson(rack::Module *module);
	void setMidiModuleIds(MidiModuleIds &ids);

	void addKnobMaps(unsigned panelKnobId, unsigned knobSetId, const std::span<const Mapping> maps);
	void addKnobMapSet(unsigned knobSetId, std::string_view knobSetName);

	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int64_t, uint16_t> squash_ids(std::vector<int64_t> ids);

private:
	void mapInputJack(const CableMap &map);
	void mapOutputJack(const CableMap &map);
	void setModuleList(std::vector<ModuleID> &modules);

	json_t *moduleStateDataJ;
	json_t *moduleArrayJ;

	PatchData pd;
	int64_t hubModuleId = -1;
	MidiModuleIds midiModuleIds;
	std::map<int64_t, uint16_t> idMap; // idMap[64 bit VCV module id] -> 16 bit MM-patch module id
};
