#pragma once
#include "JackMap.hh"
#include "ModuleID.h"
#include "ParamMap.hh"
#include "mapping/mapping.hh"
#include "patch/patch.hh"
#include "patch_convert/patch_to_yaml.hh"
#include <map>
#include <rack.hpp>
#include <span>
#include <vector>

class PatchFileWriter {
	PatchData pd;
	int64_t hubModuleId;
	std::map<int64_t, uint16_t> idMap; // idMap[64 bit VCV module id] -> 16 bit MM-patch module id

public:
	PatchFileWriter(std::vector<ModuleID> modules, int64_t hubModuleId);
	void setPatchName(std::string patchName);
	void setPatchDesc(std::string patchDesc);
	void setCableList(std::vector<CableMap> &jacks);
	void setParamList(std::vector<ParamMap> &params);

	void addKnobMaps(unsigned panelKnobId, unsigned knobSetId, const std::span<const Mapping> maps);
	void addKnobMapSet(unsigned knobSetId, std::string_view knobSetName);

	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int64_t, uint16_t> squash_ids(std::vector<int64_t> ids);

private:
	void mapInputJack(const CableMap &map);
	void mapOutputJack(const CableMap &map);
	void setModuleList(std::vector<ModuleID> &modules);
};
