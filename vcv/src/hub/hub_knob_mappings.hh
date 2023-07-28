#pragma once
#include "mapping/MappableObject.h"
#include "mapping/map_palette.hh"
#include "mapping/mapping.hh"
#include "util/countzip.hh"
#include "util/static_string.hh"

template<size_t NumKnobs, size_t MaxMapsPerPot, size_t MaxKnobSets = 8>
struct HubKnobMappings {

	struct KnobMappingSet {
		rack::ParamHandle paramHandle;
		std::array<Mapping, MaxKnobSets> maps;
	};

	using KnobMultiMap = std::array<KnobMappingSet, MaxMapsPerPot>;

	std::array<KnobMultiMap, NumKnobs> mappings;
	std::array<std::string, MaxKnobSets> knobSetNames;

	std::array<std::array<StaticString<31>, MaxKnobSets>, NumKnobs> aliases;

private:
	int64_t hubModuleId = -1;
	unsigned activeSetId = 0;

public:
	HubKnobMappings(int64_t hubModuleId)
		: hubModuleId{hubModuleId} {
		for (unsigned i = 0; auto &knob_multimap : mappings) {
			auto color = PaletteHub::color(i++);
			for (auto &map : knob_multimap) {
				map.paramHandle.color = color;
				APP->engine->addParamHandle(&map.paramHandle);
				for (auto &m : map.maps)
					m.clear();
			}
		}
	}

	~HubKnobMappings() {
		for (auto &knob_multimap : mappings) {
			for (auto &map : knob_multimap)
				APP->engine->removeParamHandle(&map.paramHandle);
		}
	}

	Mapping &activeMap(KnobMappingSet &mapset) {
		return mapset.maps[activeSetId];
	}

	// Sets of Knob Mappings:
	std::string_view getKnobSetName(unsigned idx) {
		if (idx < knobSetNames.size())
			return knobSetNames[idx];
		else
			return "";
	}

	void setKnobSetName(unsigned idx, std::string &name) {
		if (idx < knobSetNames.size())
			knobSetNames[idx] = name;
	}

	unsigned getActiveKnobSetIdx() {
		return activeSetId;
	}

	void setActiveKnobSetIdx(unsigned setId) {
		if (setId == activeSetId || setId >= MaxKnobSets)
			return;

		activeSetId = setId;
		refreshParamHandles();
	}

private:
	void refreshParamHandles() {
		for (auto &knob : mappings) {
			for (auto &mapset : knob) {
				Mapping map = mapset.maps[activeSetId];
				APP->engine->updateParamHandle(&mapset.paramHandle, map.moduleId, map.paramId, true);
				if (!mapset.paramHandle.module) {
					map.moduleId = -1;
					map.paramId = -1;
				}
			}
		}
	}

public:
	// Mapping Range:

	void setRangeMin(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &mapset : knob) {
				Mapping &map = mapset.maps[activeSetId];
				if (is_valid(map) && paramObj.moduleID == mapset.paramHandle.moduleId &&
					paramObj.objID == mapset.paramHandle.paramId)
				{
					map.range_min = val;
					return;
				}
			}
		}
	}

	void setRangeMax(const MappableObj paramObj, float val) {
		for (auto &knob : mappings) {
			for (auto &mapset : knob) {
				Mapping &map = mapset.maps[activeSetId];
				if (is_valid(map) && paramObj.moduleID == mapset.paramHandle.moduleId &&
					paramObj.objID == mapset.paramHandle.paramId)
					map.range_max = val;
			}
		}
	}

	std::pair<float, float> getRange(const MappableObj paramObj) {
		for (auto &knob : mappings) {
			for (auto &mapset : knob) {
				Mapping &map = mapset.maps[activeSetId];
				if (is_valid(map) && paramObj.moduleID == mapset.paramHandle.moduleId &&
					paramObj.objID == mapset.paramHandle.paramId)
				{
					return {map.range_min, map.range_max};
				}
			}
		}
		return {0, 1}; //not found --> default value
	}

	// Mapping Alias:

	void setMapAliasName(MappableObj paramObj, std::string newname) {
		if (paramObj.objID < (int)NumKnobs) {
			aliases[paramObj.objID][activeSetId].copy(newname);
		}
	}

	std::string getMapAliasName(MappableObj paramObj) {
		if (paramObj.objID < (int)NumKnobs) {
			return std::string{aliases[paramObj.objID][activeSetId]};
		}
		return "";
	}

	// Add mappings to a knob in the active set:
	Mapping *addMap(unsigned hubParamId, int64_t destModuleId, int destParamId) {
		auto &knob = nextFreeMap(hubParamId, activeSetId);

		APP->engine->updateParamHandle(&knob.paramHandle, destModuleId, destParamId, true);

		auto *map = &knob.maps[activeSetId];
		map->moduleId = destModuleId;
		map->paramId = destParamId;
		return map;
	}

private:
	// Add a map to any set, but don't update the ParamHandle
	void populateMap(unsigned hubParamId, int64_t destModuleId, int destParamId, unsigned setId, float min, float max) {
		auto &knob = nextFreeMap(hubParamId, setId);

		auto *map = &knob.maps[setId];
		map->moduleId = destModuleId;
		map->paramId = destParamId;
		map->range_min = min;
		map->range_max = max;
	}

	KnobMappingSet &nextFreeMap(unsigned hubParamId, unsigned set_idx) {
		// Find first unused paramHandle
		for (auto &mapset : mappings[hubParamId]) {
			if (mapset.paramHandle.moduleId < 0) {
				// Clear our local copy if VCV's paramHandle was cleared (ie. modules was removed)
				if (mapset.maps[set_idx].moduleId >= 0) {
					mapset.maps[set_idx].moduleId = -1;
					mapset.maps[set_idx].paramId = -1;
					printf("Found a mapset out of sync with VCV paramHandle\n");
				}
				return mapset;
			}
		}
		// If all are used, then overwrite the last one
		return mappings[hubParamId][MaxMapsPerPot - 1];
	}

public:
	// Return a reference to an array of KnobMappingSets of a knob
	auto &getAllMappings(int hubParamId) {
		if (hubParamId >= (int)NumKnobs)
			return nullmap;

		return mappings[hubParamId];
	}

	unsigned getNumActiveMappings(int hubParamId) {
		unsigned num = 0;

		if (hubParamId >= (int)NumKnobs)
			return 0;

		for (auto &mapset : mappings[hubParamId]) {
			if (is_valid(mapset.maps[activeSetId]))
				num++;
		}
		return num;
	}

	auto collate_mappings() {
		std::array<std::array<std::array<Mapping, MaxMapsPerPot>, NumKnobs>, MaxKnobSets> knobSets;

		for (auto [knob_idx, knob] : enumerate(mappings)) {
			for (auto [map_idx, mapset] : enumerate(knob)) {
				for (auto [set_idx, map] : enumerate(mapset.maps)) {
					auto &ks = knobSets[set_idx][knob_idx][map_idx];
					ks = map;
				}
			}
		}
		return knobSets;
	}

	// Save/restore VCV rack patch

	json_t *encodeJson() {
		// Translate from mappings to knobSets
		auto knobSets = collate_mappings();

		json_t *rootJ = json_object();
		json_t *knobSetsJ = json_array();

		for (unsigned knobSetId = 0; auto &mappings : knobSets) {

			json_t *mapsJ = json_array();

			for (unsigned hubParamId = 0; auto &knob : mappings) {
				for (auto &map : knob) {

					if (!is_valid(map))
						continue;

					json_t *thisMapJ = json_object();
					json_object_set_new(thisMapJ, "DstModID", json_integer(map.moduleId));
					json_object_set_new(thisMapJ, "DstObjID", json_integer(map.paramId));
					json_object_set_new(thisMapJ, "SrcModID", json_integer(hubModuleId));
					json_object_set_new(thisMapJ, "SrcObjID", json_integer(hubParamId));
					json_object_set_new(thisMapJ, "RangeMin", json_real(map.range_min));
					json_object_set_new(thisMapJ, "RangeMax", json_real(map.range_max));
					json_object_set_new(thisMapJ, "AliasName", json_string(aliases[hubParamId][knobSetId].c_str()));

					json_array_append(mapsJ, thisMapJ);
					json_decref(thisMapJ);
				}
				hubParamId++;
			}
			json_array_append(knobSetsJ, mapsJ);
			json_decref(mapsJ);
			knobSetId++;
		}
		json_object_set_new(rootJ, "Mappings", knobSetsJ);
		return rootJ;
	}

	void decodeJson(json_t *rootJ) {
		auto knobSetsJ = json_object_get(rootJ, "Mappings");

		if (json_is_array(knobSetsJ)) {
			clear_all();

			for (size_t set_i = 0; set_i < json_array_size(knobSetsJ); set_i++) {
				auto mapsJ = json_array_get(knobSetsJ, set_i);

				if (json_is_array(mapsJ)) {
					setActiveKnobSetIdx(set_i);

					for (size_t i = 0; i < json_array_size(mapsJ); i++) {
						auto mappingJ = json_array_get(mapsJ, i);

						if (json_is_object(mappingJ)) {
							json_t *val;

							// Verify its for this module (there may be more than one hub)
							// val = json_object_get(mappingJ, "SrcModID");
							// auto moduleId = json_is_integer(val) ? json_integer_value(val) : -1;
							// if (moduleId != hubModuleId)
							// 	continue;

							val = json_object_get(mappingJ, "SrcObjID");
							auto hubParamId = json_is_integer(val) ? json_integer_value(val) : -1;
							if (hubParamId >= (int)NumKnobs)
								continue;

							val = json_object_get(mappingJ, "DstModID");
							auto destModuleId = json_is_integer(val) ? json_integer_value(val) : -1;

							val = json_object_get(mappingJ, "DstObjID");
							auto destModuleParamId = json_is_integer(val) ? json_integer_value(val) : -1;

							auto *map = addMap(hubParamId, destModuleId, destModuleParamId);

							val = json_object_get(mappingJ, "RangeMin");
							map->range_min = json_is_real(val) ? json_real_value(val) : 0.f;

							val = json_object_get(mappingJ, "RangeMax");
							map->range_max = json_is_real(val) ? json_real_value(val) : 1.f;

							printf("add map k:%d m:%d p:%d s:%d %f %f\n",
								   hubParamId,
								   destModuleId,
								   destModuleParamId,
								   set_i,
								   map->range_min,
								   map->range_max);

							val = json_object_get(mappingJ, "AliasName");
							aliases[hubParamId][set_i] = json_is_string(val) ? json_string_value(val) : "";
						}
					}

					refreshParamHandles();
				}
			}
		}
		setActiveKnobSetIdx(0); //TODO: save the default in json
	}

	bool is_valid(Mapping map) {
		//TODO: check if module exists in patch still?
		return map.moduleId >= 0;
	}

	void clear_all() {
		// invalidate all maps
		for (auto &knob : mappings) {
			for (auto &mapset : knob) {
				APP->engine->updateParamHandle(&mapset.paramHandle, -1, 0, true);
				for (auto &map : mapset.maps) {
					map.clear();
				}
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
	// auto &operator[](size_t n) {
	// 	auto &mappings = mappings[knobSets[activeSetId].set;
	// 	return mappings[std::min(n, NumKnobs - 1)];
	// }
	// auto &operator[](size_t n) const {
	// 	auto &mappings = knobSets[activeSetId].set;
	// 	return mappings[std::min(n, NumKnobs - 1)];
	// }

	KnobMultiMap nullmap{};
};
