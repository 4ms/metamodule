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
		// search moduleData for matching mod
		// remove it
	}

	//		 private :
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<LabelButtonID> mappings;
};

