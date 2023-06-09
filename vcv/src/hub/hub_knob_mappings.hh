#pragma once
#include "mapping/MappableObject.h"
#include "mapping/Mapping2.h"

template<size_t NumKnobs, size_t MaxMapsPerPot>
struct HubKnobMappings {

	using KnobParamHandles = std::array<Mapping2, MaxMapsPerPot>;

	std::array<KnobParamHandles, NumKnobs> mappings;
	int64_t hubModuleId = -1;

	HubKnobMappings(int64_t hubModuleId)
		: hubModuleId{hubModuleId} {
	}

	void setRangeMin(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					map.range_min = val;
			}
		}
	}

	void setRangeMax(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					map.range_max = val;
			}
		}
	}

	std::pair<float, float> getRange(const MappableObj paramObj) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					return {map.range_min, map.range_max};
			}
		}
		return {0, 1}; //not found --> default value
	}

	void setMapAliasName(MappableObj paramObj, std::string newname) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					map.alias_name = newname;
			}
		}
	}

	std::string getMapAliasName(MappableObj paramObj) {
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				if (paramObj.moduleID == map.paramHandle.moduleId && paramObj.objID == map.paramHandle.paramId)
					return map.alias_name;
			}
		}
		return "";
	}

	unsigned getNumMappings(int hubParamId) {
		unsigned num = 0;

		if (hubParamId >= (int)NumKnobs)
			return 0;

		for (auto &map : mappings[hubParamId]) {
			if (is_valid(map))
				num++;
		}
		return num;
	}

	auto &getMappings(int hubParamId) {
		if (hubParamId >= (int)NumKnobs)
			return nullmap;

		return mappings[hubParamId];
	}

	Mapping2 *nextFreeMap(unsigned hubParamId) {
		// Find first unused paramHandle
		for (auto &p : mappings[hubParamId]) {
			if (p.paramHandle.moduleId < 0) {
				return &p;
			}
		}
		// If all are used, then overwrite the last one
		return &mappings[hubParamId][MaxMapsPerPot - 1];
	}

	json_t *encodeJson() {
		json_t *rootJ = json_object();
		json_t *mapsJ = json_array();

		unsigned hubParamId = 0;
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				if (!is_valid(map))
					continue;
				json_t *thisMapJ = json_object();
				json_object_set_new(thisMapJ, "DstModID", json_integer(map.paramHandle.moduleId));
				json_object_set_new(thisMapJ, "DstObjID", json_integer(map.paramHandle.paramId));
				json_object_set_new(thisMapJ, "SrcModID", json_integer(hubModuleId));
				json_object_set_new(thisMapJ, "SrcObjID", json_integer(hubParamId));
				json_object_set_new(thisMapJ, "RangeMin", json_real(map.range_min));
				json_object_set_new(thisMapJ, "RangeMax", json_real(map.range_max));
				json_object_set_new(thisMapJ, "AliasName", json_string(map.alias_name.c_str()));

				json_array_append(mapsJ, thisMapJ);
				json_decref(thisMapJ);
			}
			hubParamId++;
		}
		json_object_set_new(rootJ, "Mappings", mapsJ);
		return rootJ;
	}

	void decodeJson(json_t *rootJ) {
		auto mapsJ = json_object_get(rootJ, "Mappings");

		if (json_is_array(mapsJ)) {
			clear_all();

			for (size_t i = 0; i < json_array_size(mapsJ); i++) {
				auto mappingJ = json_array_get(mapsJ, i);

				if (json_is_object(mappingJ)) {
					json_t *val;

					// Verify its for this module (there may be more than one hub)
					val = json_object_get(mappingJ, "SrcModID");
					auto moduleId = json_is_integer(val) ? json_integer_value(val) : -1;
					if (moduleId != hubModuleId)
						continue;

					val = json_object_get(mappingJ, "SrcObjID");
					auto hubParamId = json_is_integer(val) ? json_integer_value(val) : -1;
					if (hubParamId >= (int)NumKnobs)
						continue;

					auto *map = nextFreeMap(hubParamId);

					val = json_object_get(mappingJ, "DstModID");
					map->paramHandle.moduleId = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "DstObjID");
					map->paramHandle.paramId = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "RangeMin");
					map->range_min = json_is_real(val) ? json_real_value(val) : 0.f;

					val = json_object_get(mappingJ, "RangeMax");
					map->range_max = json_is_real(val) ? json_real_value(val) : 1.f;

					val = json_object_get(mappingJ, "AliasName");
					map->alias_name = json_is_string(val) ? json_string_value(val) : "";
				}
			}
		}
	}

	bool is_valid(Mapping2 map) {
		return (map.paramHandle.module && map.paramHandle.moduleId >= 0);
	}

	void clear_all() {
		// invalidate all maps
		for (auto &knob : mappings) {
			for (auto &map : knob) {
				// TODO: Do we need to unregister the paramHandle with engine?
				map.paramHandle.module = nullptr;
				map.paramHandle.moduleId = -1;
			}
		}
	}

	// Helpers

	auto begin() {
		return mappings.begin();
	}
	auto end() {
		return mappings.end();
	}
	auto &operator[](size_t n) {
		return mappings[std::min(n, NumKnobs - 1)];
	}
	auto &operator[](size_t n) const {
		return mappings[std::min(n, NumKnobs - 1)];
	}

	KnobParamHandles nullmap{};
};
