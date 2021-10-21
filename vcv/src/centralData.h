#pragma once
#include "CommData.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <rack.hpp>
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
		std::lock_guard mguard{mtx};
		moduleData.push_back(mod);
	}

	template<typename T, typename RT>
	void remove_and_erase(T &vec, RT p)
	{
		vec.erase(std::remove_if(vec.begin(), vec.end(), p), vec.end());
		// std::erase_if(vec, p);
	}

	void unregisterModule(ModuleID mod)
	{
		std::lock_guard mguard{mtx};

		auto module_it = std::find(moduleData.begin(), moduleData.end(), mod);
		if (module_it != moduleData.end())
			moduleData.erase(module_it);

		remove_and_erase(paramData, [=](const auto &p) { return (p.moduleID == mod.id); });
		remove_and_erase(jackData,
						 [&](const auto &j) { return j.receivedModuleId == mod.id || j.sendingModuleId == mod.id; });
		remove_and_erase(maps, [&](const auto &m) { return m.dst.moduleID == mod.id || m.src.moduleID == mod.id; });
	}

	unsigned int getNumModules()
	{
		std::lock_guard mguard{mtx};

		auto sz = moduleData.size();
		return sz;
	}

	void updateParamStatus(ParamStatus updatedParam)
	{
		std::lock_guard mguard{mtx};

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
	}

	void updateJackStatus(JackStatus updatedJack)
	{
		std::lock_guard mguard{mtx};

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
	}

	MessageType getMyMessage(int module_id)
	{
		std::lock_guard mguard{mtx};

		auto m = messages.find(module_id);
		if (m == messages.end())
			return MessageType::None;
		auto msg = messages[module_id];
		messages[module_id] = MessageType::None;
		return msg;
	}

	void requestAllParamDataAllModules()
	{
		std::lock_guard mguard{mtx};

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

	void registerMapDest(LabelButtonID dest)
	{
		std::lock_guard mguard{mtx};

		if (!_isMappingInProgress) {
			printf("??? registerMapDest() called but we aren't mapping!\n");
			return;
		}

		_currentMap.dst = dest;

		// Look for an existing map to the dst knob
		bool found = false;
		for (auto &m : maps) {
			if (m.dst == _currentMap.dst) {
				found = true;
				// printf("Found an existing map to m: %d, p: %d\n", m.dst.moduleID, m.dst.objID);
				m.src = _currentMap.src;
				break;
			}
		}
		if (!found) {
			// printf("Didn't found an existing map to m: %d, p: %d\n", _currentMap.dst.moduleID,
			// _currentMap.dst.objID);
			maps.push_back(_currentMap);
		}

		_currentMap.clear();

		_isMappingInProgress = false;
	}

	bool registerMapping(LabelButtonID src, LabelButtonID dst, float rmin, float rmax)
	{
		std::lock_guard mguard{mtx};

		if (!isLabelButtonDstMapped(dst)) {
			maps.push_back({src, dst, rmin, rmax});
			return true;
		}
		return false;
	}

	void setMapRange(LabelButtonID src, LabelButtonID dst, float rmin, float rmax)
	{
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	std::pair<float, float> getMapRange(LabelButtonID src, LabelButtonID dst)
	{
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		float min, max;
		if (m == maps.end()) {
			min = 0.f;
			max = 0.f;
		} else {
			min = m->range_min;
			max = m->range_max;
		}
		return {min, max};
	}

	void unregisterMapByDest(LabelButtonID dest)
	{
		std::lock_guard mguard{mtx};

		remove_and_erase(maps, [&](const auto &m) { return (m.dst == dest); });
	}

	void unregisterKnobMapsBySrcModule(int moduleId)
	{
		std::lock_guard mguard{mtx};

		remove_and_erase(maps, [=](const auto &m) {
			return (m.src.objType == LabelButtonID::Types::Knob && m.src.moduleID == moduleId);
		});
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
	bool isLabelButtonDstMapped(const LabelButtonID &b)
	{
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
	}

	LabelButtonID getMappedSrcFromDst(LabelButtonID &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
		if (obj != maps.end())
			return obj->src;
		return {LabelButtonID::Types::None, -1, -1};
	}
	// TODO: only allow this if type is not Knob (because it's not multi-map friendly)
	LabelButtonID getMappedDstFromSrc(LabelButtonID &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
		if (obj != maps.end())
			return obj->dst;
		return {LabelButtonID::Types::None, -1, -1};
	}

	void registerTouchedJack(rack::app::PortWidget *touched)
	{
		lastTouchedPort = touched;
	}

	rack::app::PortWidget *getAndClearTouchedJack()
	{
		auto tmp = lastTouchedPort;
		lastTouchedPort = nullptr;
		return tmp;
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

	rack::app::PortWidget *lastTouchedPort = nullptr;
};

// Todo for mappings:
/*
   Allow user to start a mapping by clicking on a dest (non-hub module)


 */
