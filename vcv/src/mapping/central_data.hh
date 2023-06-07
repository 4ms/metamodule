#pragma once

#include "JackStatus.h"
#include "Mapping.h"
#include "ModuleID.h"
#include "ParamStatus.h"
#include "map_palette.hh"

#include "patch/midi_def.hh"
#include "util/math.hh"

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <rack.hpp>
#include <vector>

// #define pr_dbg printf

#define pr_dbg(...)

class CentralData {
public:
	CentralData() = default;
	~CentralData() = default;

	// True if module is regular module or hub in 4msCompany plugin
	bool isInPlugin(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		if (!module->model->plugin)
			return false;
		return module->model->plugin->slug == "4msCompany";
	}

	bool isHub(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		return module->model->slug == "PanelMedium";
	}
	bool isModuleInPlugin(rack::Module *module) {
		return isInPlugin(module) && !isHub(module);
	}

	// Modules
	void registerModule(ModuleID mod, rack::Module *module) {
		std::lock_guard mguard{mtx};

		// Check if any maps exist with this module id (happens if we load a patch
		// file), and set the module ptr.
		for (auto &map : maps) {
			if (map.dst.moduleID == mod.id && map.dst_module == nullptr) {
				map.dst_module = module;
			}
		}
	}

	void unregisterModule(ModuleID mod) {
		std::lock_guard mguard{mtx};
		std::erase_if(maps, [&](const auto &m) { return m.dst.moduleID == mod.id || m.src.moduleID == mod.id; });
	}

	rack::Module *getRegisteredModulePtr(int64_t moduleID) {
		auto context = rack::contextGet();
		auto engine = context->engine;
		auto *module = engine->getModule(moduleID);
		if (isModuleInPlugin(module)) {
			return module;
		}
		return nullptr;
	}

	bool isRegisteredHub(int64_t moduleID) {
		auto context = rack::contextGet();
		auto engine = context->engine;
		auto *module = engine->getModule(moduleID);
		return isHub(module);
	}

	void startMappingProcedure(MappableObj src) {
		_isMappingInProgress = true;
		_currentMap.src = src;
	}

	void abortMappingProcedure() {
		_isMappingInProgress = false;
	}

	bool isMappingInProgress() {
		return _isMappingInProgress;
	}

	const MappableObj &getMappingSource() {
		return _currentMap.src;
	}

	void notifyEnterHover(MappableObj obj) {
		_cur_hover_obj = obj;
	}

	void notifyLeaveHover(MappableObj obj) {
		if (_cur_hover_obj == obj)
			_cur_hover_obj = {MappableObj::Type::None, -1, -1};
	}

	// Given an object we want to draw,
	// return true if it's mapped to the mouse-hovered object,
	// so that we can draw this object with a special highlight.
	// Also return true if the mouse-hovered object is mapped to the same hub
	// object as the object we want to draw (multi-map).
	bool isMappedPartnerHovered(const MappableObj obj_to_draw) {
		// If we're hovering a hub (src) object, then highlight all mapped objects
		// on modules
		if (isSrcDstMapped(_cur_hover_obj, obj_to_draw))
			return true;

		// Check if we're hovering a mapped dst (module object that's mapped to a
		// hub object)
		MappableObj src = getMappedSrcFromDst(_cur_hover_obj);
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

	bool registerMapDest(rack::Module *module, int64_t param_id) {
		_currentMap.dst = {
			.objType = MappableObj::Type::Knob, .objID = param_id, .moduleID = static_cast<int64_t>(module->id)};
		_currentMap.dst_module = module;

		pr_dbg("registerMapDest: dest: objID=%lld, moduleID=%lld t:%d\n", dest.objID, dest.moduleID, dest.objType);
		pr_dbg("current src: objID=%lld, moduleID=%lld t:%d\n",
			   _currentMap.src.objID,
			   _currentMap.src.moduleID,
			   _currentMap.src.objType);

		{ // start mapsmtx lock
			std::lock_guard mguard{mapsmtx};

			// Look for an existing map to the dst
			bool found = false;
			for (auto &m : maps) {
				if (m.dst == _currentMap.dst) {
					found = true;
					pr_dbg("Found an existing map to dst (src was m:%lld p:%lld t:%d\n",
						   m.src.moduleID,
						   m.src.objID,
						   m.src.objType);
					m.src = _currentMap.src;
					break;
				}
			}
			if (!found) {
				pr_dbg("Didn't find an existing map to dst, adding it to centralData.\n");

				// Rule: hub output jacks can only be mapped to one dst
				if (_currentMap.src.objType == MappableObj::Type::OutputJack) {
					auto num_erased = std::erase_if(maps, [&](auto const &m) { return m.src == _currentMap.src; });
					pr_dbg("Removed %lu mappings from centralData, with src on hub: "
						   "m=%lld out-jack=%lld\n",
						   num_erased,
						   _currentMap.src.moduleID,
						   _currentMap.src.objID);
					(void)num_erased;
				}

				pr_dbg("Added: dest: objID=%lld, moduleID=%lld (ptr->id=%lld) t=%d. src: objID=%lld, moduleID=%lld , "
					   "t=%d\n",
					   _currentMap.dst.objID,
					   _currentMap.dst.moduleID,
					   _currentMap.dst_module->id,
					   _currentMap.dst.objType,
					   _currentMap.src.objID,
					   _currentMap.src.moduleID,
					   _currentMap.src.objType);
				maps.push_back(_currentMap);
			}

			_currentMap.clear();
			_isMappingInProgress = false;
		} // end mapsmtx lock

		return true;
	}

	// Can be called by UI Thread on "Unmap" menuitem
	void unregisterMapByDest(MappableObj dest) {
		// Remove from CD::maps
		{
			std::lock_guard mguard{mapsmtx};
			std::erase_if(maps, [&](const auto &m) { return (m.dst == dest); });
		}
	}

	// This is called in HubBase destructor
	void unregisterKnobMapsBySrcModule(int64_t moduleId) {
		// Remove CD::maps
		{
			std::lock_guard mguard{mtx};
			std::erase_if(maps, [=](const auto &m) {
				return (m.src.objType == MappableObj::Type::Knob && m.src.moduleID == moduleId);
			});
		}
	}

	//
	// Knob Mapping Range
	//

	void setMapRange(MappableObj src, MappableObj dst, float rmin, float rmax) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	void setMapRangeMin(MappableObj dst, float rmin) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_min = MathTools::constrain(rmin, 0.f, 1.f);
	}

	void setMapRangeMax(MappableObj dst, float rmax) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.dst == dst); });
		if (m == maps.end())
			return;
		m->range_max = MathTools::constrain(rmax, 0.f, 1.f);
	}

	std::pair<float, float> getMapRange(MappableObj src, MappableObj dst) {
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

	std::pair<float, float> getMapRange(MappableObj dst) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == dst; });
		float min, max;
		if (m == maps.end()) {
			min = 0.f;
			max = 1.f;
			pr_dbg("Not found\n");
		} else {
			min = m->range_min;
			max = m->range_max;
		}
		return {min, max};
	}

	void setMapAliasName(MappableObj src, std::string newname) {
		std::lock_guard mguard{mapsmtx};
		// TODO: update all maps with matching src
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
		if (m == maps.end())
			return;
		m->alias_name = newname;
	}

	std::string getMapAliasName(MappableObj src) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
		if (m == maps.end())
			return "";
		return m->alias_name;
	}

	void setMapAliasName(MappableObj src, MappableObj dst, std::string newname) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return;
		m->alias_name = newname;
	}

	std::string getMapAliasName(MappableObj src, MappableObj dst) {
		std::lock_guard mguard{mapsmtx};
		auto m = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
		if (m == maps.end())
			return "";
		return m->alias_name;
	}

	//
	// State queries
	//

	bool isLabelButtonMapped(MappableObj const &b) {
		return maps.end() !=
			   std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == b || m.dst == b); });
	}

	bool isLabelButtonSrcMapped(MappableObj const &b) {
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
	}

	bool isLabelButtonDstMapped(MappableObj const &b) {
		return maps.end() != std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
	}

	MappableObj getMappedSrcFromDst(MappableObj const &b) {
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.dst == b; });
		if (obj != maps.end())
			return obj->src;
		return {MappableObj::Type::None, -1, -1};
	}

	bool isSrcDstMapped(MappableObj const &src, MappableObj const &dst) {
		return maps.end() !=
			   std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return (m.src == src && m.dst == dst); });
	}

	// TODO: only allow this if type is not Knob (because it's not multi-map
	// friendly)
	MappableObj getMappedDstFromSrc(MappableObj const &b) {
		auto obj = std::find_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == b; });
		if (obj != maps.end())
			return obj->dst;
		return {MappableObj::Type::None, -1, -1};
	}

	unsigned getNumMappingsFromSrc(MappableObj const &src) {
		return std::count_if(maps.begin(), maps.end(), [&](const auto &m) { return m.src == src; });
	}

	auto getMappingsFromSrc(MappableObj const &src) {
		std::vector<MappingExt> copied_maps;
		std::lock_guard mguard{mtx};
		for (auto &m : maps) {
			if (m.src == src) {
				copied_maps.push_back(m);
			}
		}
		return copied_maps;
	}

	//
	// Jack "touching", used to map jacks
	//

	void registerTouchedJack(MappableObj touched) {
		lastTouchedJack = touched;
	}

	MappableObj getAndClearTouchedJack() {
		auto tmp = lastTouchedJack;
		lastTouchedJack = {MappableObj::Type::None, -1, -1};
		return tmp;
	}

	struct RegisteredModule {
		int64_t id;
		ModuleTypeSlug slug;
		rack::Module *module;
	};
	struct MappingExt : Mapping {
		rack::Module *dst_module;
	};

	// private:
	std::vector<MappingExt> maps;

private:
	bool _isMappingInProgress = false;
	MappingExt _currentMap;
	MappableObj _cur_hover_obj;

	MappableObj lastTouchedJack{MappableObj::Type::None, -1, -1};

	static inline std::mutex mtx;
	static inline std::mutex paramHandleQmtx;
	static inline std::mutex mappedParamHandlemtx;
	static inline std::mutex mapsmtx;
	static inline const std::array<ModuleTypeSlug, 2> ValidHubSlugs = {"PANEL_8", "PanelMedium"};
};

extern std::unique_ptr<CentralData> centralData;
void initializeCentralData();
