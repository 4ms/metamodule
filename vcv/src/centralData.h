#pragma once
#include "CommData.h"
#include <iostream>
#include <map>
#include <mutex>
#include <vector>

class CentralData {
	static inline std::mutex mtx;

public:
	enum MessageType {
		None,
		RequestAllParamData,
	};

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

	void updateJackStatus(JackStatus updatedJack)
	{
		mtx.lock();
		bool found = false;
		for (auto &j : jackData) {
			if (j.isSameJack(updatedJack)) {
				j.connected = updatedJack.connected;
				if (j.connected) {
					j.receivedJackId = updatedJack.receivedJackId;
					j.receivedModuleId = updatedJack.receivedModuleId;
				} else {
					j.receivedJackId = -1;
					j.receivedModuleId = -1;
				}
				found = true;
			}
		}
		if (!found) {
			jackData.push_back(updatedJack);
		}
		mtx.unlock();
	}

	MessageType getMyMessage(int module_id)
	{
		auto m = messages.find(module_id);
		if (m == messages.end())
			return MessageType::None;
		auto msg = messages[module_id];
		messages[module_id] = MessageType::None;
		return msg;
	}

	void requestAllParamDataAllModules()
	{
		for (auto &m : moduleData) {
			messages[m.id] = MessageType::RequestAllParamData;
		}
	}

	void startMappingProcedure(LabelButtonID src)
	{
		currentMapState = MappingState::MappingPending;
		currentMap.src = src;
	}

	void abortMappingProcedure()
	{
		currentMapState = MappingState::Normal;
	}

	MappingState getMappingState()
	{
		return currentMapState;
	}

	void registerMapDest(LabelButtonID dest)
	{
		if (currentMapState != MappingState::MappingPending)
			return;

		currentMap.dst = dest;

		bool found = false;
		for (auto &m : maps) {
			if (m.src == currentMap.src) {
				found = true;
				m.dst = currentMap.dst;
				break;
			}
		}
		if (!found)
			maps.push_back(currentMap);

		currentMap.dst.moduleID = -1;
		currentMap.src.moduleID = -1;

		currentMapState = MappingState::Normal;
	}

	void unregisterMapDest(LabelButtonID dest)
	{
		// Todo: find this dest in the data

		maps.erase(std::remove_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dest); }),
				   maps.end());
	}

	//		 private :
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;

	std::map<int, MessageType> messages;

	struct Mapping {
		LabelButtonID src;
		LabelButtonID dst; // Todo: vector of destinations
						   // Todo: vector of amounts
	};

	MappingState currentMapState = MappingState::Normal;
	Mapping currentMap;

	std::vector<Mapping> maps;
};

// Todo for mappings:
/*

   Mapped labels show some display depending on the map source
   --- ButtonLabel needs to store more than just MappingState, also something about the display type

   Can start a mapping by clicking on a dest (non-hub module)

   If you add a new mapping that ends in a dest which is already part of a mapping, the mapping gets removed and no new
   one is added. Fix this to replace the old mapping

	Source label button should change display during MappingPending state
 */
