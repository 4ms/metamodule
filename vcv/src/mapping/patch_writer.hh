#pragma once
#include "JackMap.hh"
#include "ModuleID.h"
#include "ParamMap.hh"
#include "mapping/Mapping2.h"
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
	void setCableList(std::vector<JackMap> &jacks);
	void setParamList(std::vector<ParamMap> &params);

	void addKnobMaps(unsigned panelKnobId, const std::span<const Mapping2> maps);

	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int64_t, uint16_t> squash_ids(std::vector<int64_t> ids);

private:
	void mapInputJack(const JackMap &map);
	void mapOutputJack(const JackMap &map);
	void setModuleList(std::vector<ModuleID> &modules);
};
