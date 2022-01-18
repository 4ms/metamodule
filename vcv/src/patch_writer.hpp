#pragma once
#include "CommData.hpp"
#include "patch/patch.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "util/byte_block.hh"
#include <map>
#include <vector>

class PatchFileWriter {
	PatchHeader ph;
	PatchData pd;
	std::map<int, int> idMap;

public:
	PatchFileWriter(std::vector<ModuleID> modules);
	void setModuleList(std::vector<ModuleID> &modules);
	void setPatchName(std::string patchName);
	void setJackList(std::vector<JackStatus> &jacks);
	void setParamList(std::vector<ParamStatus> &params);
	void addMaps(std::vector<Mapping> maps);
	ByteBlock::DataType printPatchBinary();
	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int, int> squash_ids(std::vector<int> ids);
};
