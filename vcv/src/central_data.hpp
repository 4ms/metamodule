#pragma once
#include "CommData.hpp"
#include "paletteHub.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <rack.hpp>
#include <unordered_map>
#include <vector>

class CentralData {
	static inline std::mutex mtx;
	static inline std::mutex paramHandleQmtx;
	static inline std::mutex mappedParamHandlemtx;
	static inline std::mutex mapsmtx;
	static inline const std::array<ModuleTypeSlug, 2> ValidHubSlugs = {"PANEL_8", "PanelMedium"};

public:
	CentralData() = default;

	~CentralData()
	{
		// Must remove all paramHandles from APP->engine before module is destructed
		printf("~CentralData\n");
		// for (auto &phvec : mappedParamHandles) {
		// 	for (auto &ph : phvec.second) {
		// 		printf("Removing paramHandle at %p\n", ph.get());
		// 		ph->moduleId = -1;
		// 		APP->engine->removeParamHandle(ph.get());
		// 	}
		// }
	}
	enum MessageType {
		None,
		RequestAllParamData,
	};

	// Modules
	void registerModule(ModuleID mod)
	{
		std::lock_guard mguard{mtx};
		moduleData.push_back(mod);
	}

	void unregisterModule(ModuleID mod)
	{
		std::lock_guard mguard{mtx};

		auto module_it = std::find(moduleData.begin(), moduleData.end(), mod);
		if (module_it != moduleData.end())
			moduleData.erase(module_it);

		std::erase_if(paramData, [=](const auto &p) { return (p.moduleID == mod.id); });
		std::erase_if(jackData,
					  [&](const auto &j) { return j.receivedModuleId == mod.id || j.sendingModuleId == mod.id; });
		std::erase_if(maps, [&](const auto &m) { return m.dst.moduleID == mod.id || m.src.moduleID == mod.id; });
	}

	unsigned int getNumModules()
	{
		std::lock_guard mguard{mtx};

		auto sz = moduleData.size();
		return sz;
	}

	bool isRegisteredHub(int moduleId)
	{
		auto module_it = std::find_if(moduleData.begin(), moduleData.end(), [=](auto &m) {
			if (m.id == moduleId) {
				for (auto &hubname : ValidHubSlugs) {
					if (hubname == m.typeID)
						return true;
				}
			}
			return false;
		});
		bool moduleFoundAndIsHub = (module_it != moduleData.end());
		return moduleFoundAndIsHub;
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

	// Called by UI Thread: HubMapButton
	void registerMapDest(LabelButtonID dest)
	{
		printf("registerMapDest: dest: objID=%d, moduleID=%d\n", dest.objID, dest.moduleID);

		LabelButtonID src;

		{ // start mapsmtx lock
			std::lock_guard mguard{mapsmtx};

			if (!_isMappingInProgress) {
				printf("Error: registerMapDest() called but we aren't mapping!\n");
				return;
			}

			_currentMap.dst = dest;

			// Look for an existing map to the dst knob
			bool found = false;
			for (auto &m : maps) {
				if (m.dst == _currentMap.dst) {
					found = true;
					printf("Found an existing map to m: %d, p: %d\n", m.dst.moduleID, m.dst.objID);
					m.src = _currentMap.src;
					break;
				}
			}
			if (!found) {
				printf(
					"Didn't found an existing map to m: %d, p: %d\n", _currentMap.dst.moduleID, _currentMap.dst.objID);
				maps.push_back(_currentMap);
			}

			src = _currentMap.src;
			_currentMap.clear();
			_isMappingInProgress = false;
		} // end mapsmtx lock

		if (dest.objType == LabelButtonID::Types::Knob) {
			queueRegisterKnobParamHandle(src, dest);
		}
	}

	std::queue<std::pair<LabelButtonID, LabelButtonID>> paramHandleQueue;
	void queueRegisterKnobParamHandle(LabelButtonID src, LabelButtonID dst)
	{
		// Called by UI thread
		// Block if other thread is accessing queue
		std::lock_guard mguard{paramHandleQmtx};
		paramHandleQueue.push(std::make_pair(src, dst));
	}

	std::pair<LabelButtonID, LabelButtonID> popRegisterKnobParamHandle()
	{
		// Called by engine process thread. Skip is can't get the lock
		std::lock_guard mguard{paramHandleQmtx};

		if (paramHandleQueue.empty())
			return std::make_pair<LabelButtonID, LabelButtonID>({LabelButtonID::Types::None, -1, -1},
																{LabelButtonID::Types::None, -1, -1});
		auto r = paramHandleQueue.front();
		paramHandleQueue.pop();
		return r;
	}

	void registerKnobParamHandle(LabelButtonID src, LabelButtonID dst)
	{
		printf("registerKnobParamHandle m:%d p:%d -> m:%d p:%d\n", src.moduleID, src.objID, dst.moduleID, dst.objID);

		// Clear from rack::Engine the paramHandles for this src knob that we've removed in the past
		// TODO: does this come up? Maybe when we remove a module?
		std::lock_guard mguard{mappedParamHandlemtx};

		auto &phvec = mappedParamHandles[src];

		for (auto &p : phvec) {
			printf("  Found a ph in phvec\n");
			if (p->moduleId == -1) {
				printf("    Removing a paramHandle that had moduleId == -1. paramId=%d, text=%s\n",
					   p->paramId,
					   p->text.c_str());
				APP->engine->removeParamHandle(p.get());
			}
		}

		// FIXME: if we remap a knob to a different src knob, then move the ph to the new mappedPH[src] vector. Or just
		// remove it from mappedPH[src] (delete the PH obj)
		auto &ph = phvec.emplace_back(std::make_unique<rack::ParamHandle>());
		printf("phvec.emplace_back: addr=%p\n", ph.get());
		for (auto &p : phvec)
			printf("\tphvec[] = addr=%p\n", p.get());

		ph->color = PaletteHub::color[src.objID];
		ph->text = "Mapped to MetaModule knob# " + std::to_string(src.objID);

		auto existingPh = APP->engine->getParamHandle(dst.moduleID, dst.objID);
		if (existingPh) {
			printf("Found an existing ParamHandle (%p) in engine with same dst module/param id. Updating it to -1, 0\n",
				   existingPh);
			APP->engine->updateParamHandle(existingPh, -1, 0, true); // module=-1 means "paramHandle controls nothing"
			// TODO: we did this in KnobMaps, but do we need to do it here?
			// Seems like we already checkd for dups
			// {
			// 	std::lock_guard mguard{mapsmtx};
			// 	std::erase_if(maps, [&](const auto &m) { return (m.dst == dst); });
			// // unregisterMapByDest({LabelButtonID::Types::Knob, dst.objID, dst.moduleID});
			// }
		}
		printf("Adding to engine\n");
		ph->moduleId = -1; // From Engine.cpp: "New ParamHandles must be blank"
		APP->engine->addParamHandle(ph.get());
		printf("Updating the paramhandle with new info: moduleId=%d, paramId=%d\n", dst.moduleID, dst.objID);
		APP->engine->updateParamHandle(ph.get(), dst.moduleID, dst.objID, true);

		rack::ParamHandle *p = APP->engine->getParamHandle(dst.moduleID, dst.objID);
		printf("getParamHandle = %p\n", p);
		printf("\n");
	}

	// // Registers the ParamHandle, and updates CentralData::maps with min/max/alias if an entry exists
	// void registerKnobMapping(LabelButtonID src, LabelButtonID dst, float rmin, float rmax, std::string alias)
	// {
	// 	std::lock_guard mguard{mtx};

	// 	registerKnobParamHandle(src, dst);
	// 	auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
	// 	if (m == maps.end())
	// 		return;
	// 	m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
	// 	m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	// 	m->alias_name = alias;
	// }

	void setMapRange(LabelButtonID src, LabelButtonID dst, float rmin, float rmax)
	{
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	void setMapRangeMin(LabelButtonID dst, float rmin)
	{
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
	}

	void setMapRangeMax(LabelButtonID dst, float rmax)
	{
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	// void setMapAliasName(LabelButtonID src, LabelButtonID dst, std::string newname)
	// {
	// 	auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
	// 	if (m == maps.end())
	// 		return;
	// 	m->alias_name = newname;
	// }

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
		std::lock_guard mguard{mapsmtx};

		std::erase_if(maps, [&](const auto &m) { return (m.dst == dest); });
	}

	void unregisterKnobMapsBySrcModule(int moduleId)
	{
		// FIXME: Also delete the map entry mappedParamHandles[src], where src = {Types::Knob, module_id, *}
		std::lock_guard mguard{mtx};

		std::erase_if(maps, [=](const auto &m) {
			return (m.src.objType == LabelButtonID::Types::Knob && m.src.moduleID == moduleId);
		});

		for (auto &phvec : mappedParamHandles) {
			if (phvec.first.moduleID == moduleId) {
				for (auto &ph : phvec.second) {
					printf("Removing paramHandle at %p\n", ph.get());
					ph->moduleId = -1;
					APP->engine->removeParamHandle(ph.get());
				}
			}
		}
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

	unsigned getNumMappingsFromSrc(LabelButtonID &src)
	{
		return std::count_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
	}

	// Returns a copy of the ParamHandles for the mappings on a given hub knob
	// We use a copy to be more thread-safe
	std::vector<rack::ParamHandle> getParamHandlesFromSrc(LabelButtonID const &src)
	{
		std::lock_guard mguard{mappedParamHandlemtx};

		std::vector<rack::ParamHandle> copied_phs;
		for (auto const &ph : mappedParamHandles[src]) {
			rack::ParamHandle p;
			p.moduleId = ph->moduleId;
			p.paramId = ph->paramId;
			p.module = ph->module;
			p.text = ph->text;
			p.color = ph->color;
			copied_phs.push_back(p);
		}
		return copied_phs;
	}

	void registerTouchedJack(LabelButtonID touched)
	{
		lastTouchedJack = touched;
	}

	LabelButtonID getAndClearTouchedJack()
	{
		auto tmp = lastTouchedJack;
		lastTouchedJack = {LabelButtonID::Types::None, -1, -1};
		return tmp;
	}

	//		 private :
	std::map<int, MessageType> messages;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<Mapping> maps;

	// [Hub ID, Knob ID] --> [vec of paramHandles mapped knobs]
	// We use a vec of ptrs instead of a vec of objects because
	// Rack::Engine stores raw ptrs, and needs their address to be fixed
	// (When a vector re-allocates, the address of the contained objects changes.)
	std::unordered_map<LabelButtonID, std::vector<std::unique_ptr<rack::ParamHandle>>> mappedParamHandles;

private:
	bool _isMappingInProgress = false;
	Mapping _currentMap;

	LabelButtonID lastTouchedJack{LabelButtonID::Types::None, -1, -1};
};
