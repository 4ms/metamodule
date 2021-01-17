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
		void clear()
		{
			dst.moduleID = -1;
			src.moduleID = -1;
			dst.objID = -1;
			src.objID = -1;
			dst.objType = LabelButtonID::Types::None;
			src.objType = LabelButtonID::Types::None;
		}
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
		_currentMap.src = src;
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
		return _currentMap.src;
	}

	const Mapping &getLastMapping()
	{
		return _lastMapping;
	}

	void clearLastMapping()
	{
		_lastMapping.clear();
	}

	void registerMapDest(LabelButtonID dest)
	{
		if (!_isMappingInProgress)
			return;

		_currentMap.dst = dest;

		bool found = false;
		for (auto &m : maps) {
			if (m.src == _currentMap.src) {
				found = true;
				m.dst = _currentMap.dst;
				break;
			}
		}
		if (!found)
			maps.push_back(_currentMap);

		_lastMapping = _currentMap;
		_currentMap.clear();

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
	LabelButtonID getMappedSrcFromDst(LabelButtonID &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
		if (obj == maps.end())
			return {LabelButtonID::Types::None, -1, -1};

		return obj->src;
	}
	LabelButtonID getMappedDstFromSrc(LabelButtonID &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
		if (obj == maps.end())
			return {LabelButtonID::Types::None, -1, -1};

		return obj->dst;
	}
	//		 private :
	std::map<int, MessageType> messages;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;

	std::vector<Mapping> maps;

private:
	bool _isMappingInProgress = false;
	Mapping _currentMap;
	Mapping _lastMapping;
};

// Todo for mappings:
/*
   Allow user to start a mapping by clicking on a dest (non-hub module)

   When a module is removed, delete all its mappings

 */
