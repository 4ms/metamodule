#pragma once
#include "CommData.h"
#include <vector>

class CentralData {
public:
	void registerModule(ModuleID mod)
	{
		// lock mutex
		moduleData.push_back(mod);
		// unlock
	}

	void unregisterModule(ModuleID mod)
	{
		auto position = std::find(moduleData.begin(), moduleData.end(), mod);
		if (position != moduleData.end())
			moduleData.erase(position);
	}

	unsigned int getNumModules()
	{
		return moduleData.size();
	}

	//		 private :
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<LabelButtonID> mappings;
};

