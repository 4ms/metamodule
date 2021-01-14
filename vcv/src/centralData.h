#pragma once
#include "CommData.h"
#include <mutex>
#include <vector>

class CentralData {
	static inline std::mutex mtx;

public:
	void registerModule(ModuleID mod)
	{
		mtx.lock();
		moduleData.push_back(mod);
		mtx.unlock();
	}

	void unregisterModule(ModuleID mod)
	{
		mtx.lock();
		auto module_it = std::find(moduleData.begin(), moduleData.end(), mod);
		if (module_it != moduleData.end())
			moduleData.erase(module_it);

		paramData.erase(
			std::remove_if(paramData.begin(), paramData.end(), [&](const auto &p) { return (p.moduleID == mod.id); }),
			paramData.end());
		mtx.unlock();
	}

	unsigned int getNumModules()
	{
		mtx.lock();
		auto sz = moduleData.size();
		mtx.unlock();
		return sz;
	}

	void updateParamStatus(ParamStatus updatedParam)
	{
		mtx.lock();
		bool found = false;
		for (auto &p : paramData) {
			if (p.isSameParam(updatedParam)) {
				p.value = updatedParam.value;
				found = true;
			}
		}
		if (!found) {
			paramData.push_back(updatedParam);
		}
		mtx.unlock();
	}

	//		 private :
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<LabelButtonID> mappings;
};

