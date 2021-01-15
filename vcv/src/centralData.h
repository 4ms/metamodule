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

	struct Mapping {
		LabelButtonID src;
		LabelButtonID dst; // Todo: vector of destinations
						   // Todo: vector of amounts
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
		_isMappingInProgress = true;
		currentMap.src = src;
	}

	void abortMappingProcedure()
	{
		_isMappingInProgress = false;
	}

	bool isMappingInProgress()
	{
		return _isMappingInProgress;
	}

	const LabelButtonID &getMappingSource()
	{
		return currentMap.src;
	}

	const Mapping &getLastMapping()
	{
		return lastMapping;
	}

private:
	void clearMapping(Mapping &m)
	{
		m.dst.moduleID = -1;
		m.src.moduleID = -1;
		m.dst.objID = -1;
		m.src.objID = -1;
		m.dst.objType = LabelButtonID::Types::None;
		m.src.objType = LabelButtonID::Types::None;
	}

public:
	void clearLastMapping()
	{
		clearMapping(lastMapping);
	}

	void registerMapDest(LabelButtonID dest)
	{
		if (!_isMappingInProgress)
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

		lastMapping = currentMap;
		clearMapping(currentMap);

		_isMappingInProgress = false;
	}

	void unregisterMapDest(LabelButtonID dest)
	{
		maps.erase(std::remove_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dest); }),
				   maps.end());
	}

	bool isLabelButtonMapped(LabelButtonID &b)
	{
		return maps.end() !=
			   std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == b || m.dst == b); });
	}
	bool isLabelButtonSrcMapped(LabelButtonID &b)
	{
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
	}
	bool isLabelButtonDstMapped(LabelButtonID &b)
	{
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
	}

	//		 private :
	std::map<int, MessageType> messages;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;

	// Todo: move the mapping stuff to its own class

	std::vector<Mapping> maps;

private:
	bool _isMappingInProgress = false;
	Mapping currentMap;
	Mapping lastMapping;
};

// Todo for mappings:
/*

   Should be able to start a mapping by clicking on a dest (non-hub module)

   If you add a new mapping that ends in a dest which is already part of a mapping, the mapping gets removed and no new
   one is added. Fix this to replace the old mapping if the source is different than the existing mapping

   Bug: src labels still show up as mapped even if you remove a map and then abort
 */
