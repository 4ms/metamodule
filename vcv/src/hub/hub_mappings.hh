#pragma once
#include "CoreModules/meta-module-hub/panel_medium_defs.hh"
#include "mapping/MappableObject.h"
#include "mapping/Mapping2.h"

template<size_t NumKnobs, size_t MaxMapsPerPot>
struct HubKnobMappings {

	using KnobParamHandles = std::array<Mapping2, MaxMapsPerPot>;

	std::array<KnobParamHandles, NumKnobs> mappings;

	void setRangeMin(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!map.paramHandle.module || map.paramHandle.moduleId < 0)
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					map.range_min = val;
			}
		}
	}

	void setRangeMax(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!map.paramHandle.module || map.paramHandle.moduleId < 0)
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					map.range_max = val;
			}
		}
	}
	std::pair<float, float> getRange(const MappableObj paramObj) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!map.paramHandle.module || map.paramHandle.moduleId < 0)
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					return {map.range_min, map.range_max};
			}
		}
		return {0, 1}; //not found --> default value
	}

	// Helpers

	auto begin() {
		return mappings.begin();
	}
	auto end() {
		return mappings.end();
	}
	auto &operator[](size_t n) {
		return mappings[n];
	}
	auto &operator[](size_t n) const {
		return mappings[n];
	}
};
