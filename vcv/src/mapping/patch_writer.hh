#pragma once
#include "JackMap.hh"
#include "ModuleID.h"
#include "ParamMap.hh"
#include "mapping/Mapping2.h"
#include "patch/patch.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "util/byte_block.hh"
#include <map>
#include <span>
#include <vector>

class PatchFileWriter {
	PatchData pd;
	std::map<int64_t, uint16_t> idMap; // idMap[64 bit VCV module id] -> 16 bit MM-patch module id

public:
	PatchFileWriter(std::vector<ModuleID> modules);
	void setModuleList(std::vector<ModuleID> &modules);
	void setPatchName(std::string patchName);
	void setPatchDesc(std::string patchDesc);
	void setJackList(std::vector<JackMap> &jacks);
	void setParamList(std::vector<ParamMap> &params);

	void addKnobMaps(unsigned panelKnobId, std::span<Mapping2> maps);

	template<size_t N>
	void addAllKnobMaps(std::array<std::span<Mapping2>, N> maps) {
		for (unsigned panelKnobId = 0; auto &knobmaps : maps) {
			addKnobMaps(panelKnobId, knobmaps);
			panelKnobId++;
		}
	}

	std::string printPatchYAML();

	PatchData &get_data();
	static std::map<int64_t, uint16_t> squash_ids(std::vector<int64_t> ids);

private:
	void mapInputJack(const JackMap &map);
	void mapOutputJack(const JackMap &map);
};
