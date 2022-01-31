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

	void notifyEnterHover(LabelButtonID obj)
	{
		_cur_hover_obj = obj;
	}

	void notifyLeaveHover(LabelButtonID obj)
	{
		if (_cur_hover_obj == obj)
			_cur_hover_obj = {LabelButtonID::Types::None, -1, -1};
	}

	// Given an object we want to draw,
	// return true if it's mapped to the mouse-hovered object.
	// This implies we should draw this object with a special highlight.
	// Also return true if the mouse-hovered object is mapped to the same hub object
	// as the object we want to draw (multi-map).
	bool isMappedPartnerHovered(const LabelButtonID obj_to_draw)
	{
		// if we're hovering a hub (src) object, then highlight all mapped objects on modules
		if (isSrcDstMapped(_cur_hover_obj, obj_to_draw))
			return true;

		// At this point, we know the hovered object is either not mapped, or is a dst of a mapping

		LabelButtonID src = getMappedSrcFromDst(_cur_hover_obj);
		// If the hovered object is not a dst of any mapping, return false
		if (src.moduleID == -1)
			return false;

		// Highlight the src of the object we're hovering
		if (src == obj_to_draw)
			return true;

		// Highlight all dst's of the src of the object we're hovering
		if (isSrcDstMapped(src, obj_to_draw))
			return true;

		return false;
	}

	//
	// Registering/Unregistering Mappings
	//

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

	// Called by UI thread so that the Engine thread does the actual registering with APP->enginer
	// This prevents a dead-lock
	void queueRegisterKnobParamHandle(LabelButtonID src, LabelButtonID dst)
	{
		std::lock_guard mguard{paramHandleQmtx};
		paramHandleQueue.push(std::make_pair(src, dst));
	}

	std::pair<LabelButtonID, LabelButtonID> popRegisterKnobParamHandle()
	{
		// Called by engine process thread
		std::lock_guard mguard{paramHandleQmtx};

		if (paramHandleQueue.empty())
			return std::make_pair<LabelButtonID, LabelButtonID>({LabelButtonID::Types::None, -1, -1},
																{LabelButtonID::Types::None, -1, -1});
		auto r = paramHandleQueue.front();
		paramHandleQueue.pop();
		return r;
	}

	// This is called in the Engine thread from HubBase::process() --> processKnobMaps()
	//	[and also in loadmappings when we load a patch file]
	void registerKnobParamHandle(LabelButtonID src, LabelButtonID dst)
	{
		printf("registerKnobParamHandle m:%d p:%d -> m:%d p:%d\n", src.moduleID, src.objID, dst.moduleID, dst.objID);

		std::lock_guard mguard{mappedParamHandlemtx};

		auto &phvec = mappedParamHandles[src];

		// Clear from rack::Engine the paramHandles for this src knob that we've removed in the past
		for (auto &p : phvec) {
			if (p->moduleId == -1) {
				printf("....Removing a paramHandle moduleId == -1. paramId=%d, text=%s\n", p->paramId, p->text.c_str());
				APP->engine->removeParamHandle(p.get());
			}
		}
		// Remove from mappedParamHandles[src]
		std::erase_if(phvec, [&](auto &p) { return p->moduleId == -1; });

		auto &ph = phvec.emplace_back(std::make_unique<rack::ParamHandle>());

		// Debug:
		printf("phvec.emplace_back: addr=%p\n", ph.get());
		for (auto &p : phvec)
			printf("\tphvec[] = addr=%p\n", p.get());

		ph->color = PaletteHub::color[src.objID];
		ph->text = "Mapped to MetaModule knob# " + std::to_string(src.objID);

		if (auto existingPh = APP->engine->getParamHandle(dst.moduleID, dst.objID); existingPh) {
			printf("Found an existing ParamHandle (%p) in engine with same dst module/param id. Updating it to -1, 0\n",
				   existingPh);
			APP->engine->updateParamHandle(existingPh, -1, 0, true);
			// TODO: Why not just remove it here?
		}
		printf("Adding to engine\n");
		ph->moduleId = -1; // From Engine.cpp: "New ParamHandles must be blank"
		APP->engine->addParamHandle(ph.get());
		printf("Updating the paramhandle with new info: moduleId=%d, paramId=%d\n", dst.moduleID, dst.objID);
		APP->engine->updateParamHandle(ph.get(), dst.moduleID, dst.objID, true);

		/// Debug:
		rack::ParamHandle *p = APP->engine->getParamHandle(dst.moduleID, dst.objID);
		printf("getParamHandle = %p\n", p);
		printf("\n");
	}

	// Can be called by UI Thread on "Unmap" menuitem
	void unregisterMapByDest(LabelButtonID dest)
	{
		// Remove from CD::maps
		{
			std::lock_guard mguard{mapsmtx};
			std::erase_if(maps, [&](const auto &m) { return (m.dst == dest); });
		}

		if (auto existingPh = APP->engine->getParamHandle(dest.moduleID, dest.objID); existingPh) {
			printf("APP->engine->getParamHandle(%d, %d) found %p. Updating to -1\n",
				   dest.moduleID,
				   dest.objID,
				   existingPh);
			APP->engine->updateParamHandle(existingPh, -1, 0, true); // module=-1 means "paramHandle controls nothing"
		}
	}

	// This is called in HubBase destructor
	// TODO: Which thread does this run in? UI or Engine or other?
	void unregisterKnobMapsBySrcModule(int moduleId)
	{
		// Remove CD::maps
		{
			std::lock_guard mguard{mtx};
			std::erase_if(maps, [=](const auto &m) {
				return (m.src.objType == LabelButtonID::Types::Knob && m.src.moduleID == moduleId);
			});
		}

		// Remove ParamHandles (from engine and CD)
		{
			std::lock_guard mguard{mappedParamHandlemtx};
			printf("Getting rid of mappedParamHandles[] that match moduleId=%d\n", moduleId);
			for (auto &[lbl, phvec] : mappedParamHandles) {
				if (lbl.moduleID == moduleId && lbl.objType == LabelButtonID::Types::Knob) {
					for (auto &ph : phvec) {
						printf("Removing paramHandle at %p for objId=%d\n", ph.get(), lbl.objID);
						APP->engine->removeParamHandle(ph.get());
					}
					printf("Clearing paramHandle vector\n");
					phvec.clear();
				}
			}
			auto num_erased = std::erase_if(mappedParamHandles, [&](const auto &item) {
				auto &[key, val] = item;
				return key.moduleID == moduleId && key.objType == LabelButtonID::Types::Knob;
			});
			printf("Erased %lu entries from mappedParamHandles\n", num_erased);
		}
	}

	//
	// Knob Mapping Range
	//

	void setMapRange(LabelButtonID src, LabelButtonID dst, float rmin, float rmax)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	void setMapRangeMin(LabelButtonID dst, float rmin)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
	}

	void setMapRangeMax(LabelButtonID dst, float rmax)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	std::pair<float, float> getMapRange(LabelButtonID src, LabelButtonID dst)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		float min, max;
		if (m == maps.end()) {
			min = 0.f;
			max = 1.f;
		} else {
			min = m->range_min;
			max = m->range_max;
		}
		return {min, max};
	}

	std::pair<float, float> getMapRange(LabelButtonID dst)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == dst; });
		float min, max;
		if (m == maps.end()) {
			min = 0.f;
			max = 1.f;
			printf("Not found\n");
		} else {
			min = m->range_min;
			max = m->range_max;
		}
		return {min, max};
	}

	void setMapAliasName(LabelButtonID src, std::string newname)
	{
		std::lock_guard mguard{mapsmtx};
		// TODO: update all maps with matching src
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
		if (m == maps.end())
			return;
		m->alias_name = newname;
	}

	std::string getMapAliasName(LabelButtonID src)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
		if (m == maps.end())
			return "";
		return m->alias_name;
	}

	void setMapAliasName(LabelButtonID src, LabelButtonID dst, std::string newname)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->alias_name = newname;
	}

	std::string getMapAliasName(LabelButtonID src, LabelButtonID dst)
	{
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return "";
		return m->alias_name;
	}

	//
	// State queries
	//

	bool isLabelButtonMapped(LabelButtonID const &b)
	{
		return maps.end() !=
			   std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == b || m.dst == b); });
	}

	bool isLabelButtonSrcMapped(LabelButtonID const &b)
	{
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
	}

	bool isLabelButtonDstMapped(LabelButtonID const &b)
	{
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
	}

	LabelButtonID getMappedSrcFromDst(LabelButtonID const &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
		if (obj != maps.end())
			return obj->src;
		return {LabelButtonID::Types::None, -1, -1};
	}

	bool isSrcDstMapped(LabelButtonID const &src, LabelButtonID const &dst)
	{
		return maps.end() !=
			   std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
	}

	// TODO: only allow this if type is not Knob (because it's not multi-map friendly)
	LabelButtonID getMappedDstFromSrc(LabelButtonID const &b)
	{
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
		if (obj != maps.end())
			return obj->dst;
		return {LabelButtonID::Types::None, -1, -1};
	}

	unsigned getNumMappingsFromSrc(LabelButtonID const &src)
	{
		return std::count_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
	}

	//
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

	//
	// Jack "touching", used to map jacks
	//

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
	LabelButtonID _cur_hover_obj;

	LabelButtonID lastTouchedJack{LabelButtonID::Types::None, -1, -1};

	std::queue<std::pair<LabelButtonID, LabelButtonID>> paramHandleQueue;

	static inline std::mutex mtx;
	static inline std::mutex paramHandleQmtx;
	static inline std::mutex mappedParamHandlemtx;
	static inline std::mutex mapsmtx;
	static inline const std::array<ModuleTypeSlug, 2> ValidHubSlugs = {"PANEL_8", "PanelMedium"};
};
