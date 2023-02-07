#pragma once
#include "CommData.hh"
#include "patch/patch.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "util/byte_block.hh"
#include <map>
#include <vector>

class PatchFileWriter {
	PatchData pd;
	std::map<int64_t, uint16_t> idMap; // idMap[64 bit VCV module id] -> 16 bit MM-patch module id

public:
	PatchFileWriter(std::vector<ModuleID> modules);
	void setModuleList(std::vector<ModuleID> &modules);
	void setPatchName(std::string patchName);
	void setPatchDesc(std::string patchDesc);
	void setJackList(std::vector<JackStatus> &jacks);
	void setParamList(std::vector<ParamStatus> &params);
	void addMaps(std::vector<Mapping> maps);
	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int64_t, uint16_t> squash_ids(std::vector<int64_t> ids);
};
