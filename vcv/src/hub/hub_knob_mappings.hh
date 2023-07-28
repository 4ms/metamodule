#pragma once
#include "mapping/MappableObject.h"
#include "mapping/map_palette.hh"
#include "mapping/mapping.hh"
#include "util/static_string.hh"

template<size_t NumKnobs, size_t MaxMapsPerPot, size_t MaxKnobSets = 8>
struct HubKnobMappings {

	struct KnobMapping {
		rack::ParamHandle paramHandle;
		std::array<Mapping, MaxKnobSets> sets;
	};

	using KnobMultiMap = std::array<KnobMapping, MaxMapsPerPot>;

	std::array<KnobMultiMap, NumKnobs> mappings;

	// Structure:
	// A Knob Set is a group of multi-mappings for all the knobs
	// There are up to 8 (MaxKnobSets) Knob Sets
	// Only one Knob Set is active at a time
	//
	// Each KnobSet contains 12 (NumKnobs) KnobMultiMap's
	//
	// Each KnobMultiMap contains up to 8 (MaxMapsPerPot) possible Mapping's
	// from that hub knob to 0 or more other knobs
	//
	// activeParamHandles are VCV-native objects that are registered with VCV

	struct KnobSet {
		std::string name;
		std::array<KnobMultiMap, NumKnobs> set;
	};

	std::array<KnobSet, MaxKnobSets> knobSets;

	// FIXME: Aliases should be inside KnobSet?
	std::array<StaticString<31>, NumKnobs> aliases;

	using ParamHandleMultiMap = std::array<rack::ParamHandle, MaxMapsPerPot>;
	std::array<ParamHandleMultiMap, NumKnobs> activeParamHandles;

private:
	int64_t hubModuleId = -1;
	unsigned activeSetId = 0;

public:
	HubKnobMappings(int64_t hubModuleId)
		: hubModuleId{hubModuleId} {
		for (unsigned i = 0; auto &knob_phs : activeParamHandles) {
			auto color = PaletteHub::color(i++);
			for (auto &ph : knob_phs) {
				ph.color = color;
				APP->engine->addParamHandle(&ph);
			}
		}
	}

	~HubKnobMappings() {
		for (auto &knob_phs : activeParamHandles) {
			for (auto &ph : knob_phs)
				APP->engine->removeParamHandle(&ph);
		}
	}

	// Sets of Knob Mappings:
	std::string_view getKnobSetName(unsigned idx) {
		if (idx < knobSets.size())
			return knobSets[idx].name;
		else
			return "";
	}

	void setKnobSetName(unsigned idx, std::string &name) {
		if (idx < knobSets.size())
			knobSets[idx].name = name;
	}

	unsigned getActiveKnobSetIdx() {
		return activeSetId;
	}

	void setActiveKnobSetIdx(unsigned setId) {
		if (setId == activeSetId || setId < knobSets.size())
			return;

		//Clear paramHandle links from old active set
		// for (auto &knob : knobSets[activeSetId].set) {
		// 	for (auto &map : knob) {
		// 		map.paramHandle = nullptr; //?
		// 	}
		// }

		// Connect new active set to paramHandles
		activeSetId = setId;
		for (auto [knob, phs] : zip(knobSets[activeSetId].set, activeParamHandles)) {
			for (auto [map, ph] : zip(knob, phs)) {
				map.paramHandle.moduleId = ph.moduleId;
				map.paramHandle.module = ph.module;
				map.paramHandle.paramId = ph.paramId;
				map.paramHandle.text = ph.text;
			}
		}
	}

	// Mapping Range:

	void setRangeMin(const MappableObj paramObj, float val) {
		auto &mappings = knobSets[activeSetId].set;
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
		auto &mappings = knobSets[activeSetId].set;
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
		auto &mappings = knobSets[activeSetId].set;
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

	// Mapping Alias:

	void setMapAliasName(MappableObj paramObj, std::string newname) {
		if (paramObj.objID < (int)NumKnobs) {
			aliases[paramObj.objID].copy(newname);
		}
	}

	std::string getMapAliasName(MappableObj paramObj) {
		if (paramObj.objID < (int)NumKnobs) {
			return std::string{aliases[paramObj.objID]};
		}
		return "";
	}

	// Add mappings to a knob:

	Mapping *addMap(unsigned hubParamId, int64_t destModuleId, int destParamId) {
		auto map_i = nextFreeMap(hubParamId);

		APP->engine->updateParamHandle(&activeParamHandles[hubParamId][map_i], destModuleId, destParamId, true);

		Mapping *map = &knobSets[activeSetId].set[hubParamId][map_i];
		map->paramHandle.moduleId = destModuleId;
		map->paramHandle.paramId = destParamId;
		// map->paramHandle.text = ; //?
		return map;
	}

	unsigned getNumMappings(int hubParamId) {
		unsigned num = 0;

		if (hubParamId >= (int)NumKnobs)
			return 0;

		auto &mappings = knobSets[activeSetId].set;

		for (auto &map : mappings[hubParamId]) {
			if (is_valid(map))
				num++;
		}
		return num;
	}

	unsigned nextFreeMap(unsigned hubParamId) {
		// Find first unused paramHandle
		for (unsigned map_i = 0; auto &ph : activeParamHandles[hubParamId]) {
			if (ph.moduleId < 0) {
				return map_i;
			}
			map_i++;
		}
		// If all are used, then overwrite the last one
		return MaxMapsPerPot - 1;
	}

	// Return a ptr to an array of the ParamHandles of a knob
	auto &getActiveParamHandles(int hubParamId) {
		if (hubParamId >= (int)NumKnobs)
			return nullmap;

		return activeParamHandles[hubParamId];
	}

	// Save/restore VCV rack patch

	json_t *encodeJson() {
		json_t *rootJ = json_object();
		json_t *knobSetsJ = json_array();

		unsigned hubParamId = 0;
		for (auto &mappings : knobSets) {

			json_t *mapsJ = json_array();

			for (auto &knob : mappings.set) {
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
					json_object_set_new(thisMapJ, "AliasName", json_string(aliases[hubParamId].c_str()));

					json_array_append(mapsJ, thisMapJ);
					json_decref(thisMapJ);
				}
				hubParamId++;
			}
			json_array_append(knobSetsJ, mapsJ);
			json_decref(mapsJ);
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

							val = json_object_get(mappingJ, "DstModID");
							auto destModuleId = json_is_integer(val) ? json_integer_value(val) : -1;

							val = json_object_get(mappingJ, "DstObjID");
							auto destModuleParamId = json_is_integer(val) ? json_integer_value(val) : -1;

							auto *map = addMap(hubParamId, destModuleId, destModuleParamId);

							val = json_object_get(mappingJ, "RangeMin");
							map->range_min = json_is_real(val) ? json_real_value(val) : 0.f;

							val = json_object_get(mappingJ, "RangeMax");
							map->range_max = json_is_real(val) ? json_real_value(val) : 1.f;

							val = json_object_get(mappingJ, "AliasName");
							aliases[hubParamId] = json_is_string(val) ? json_string_value(val) : "";
						}
					}
				}
			}
		}
	}

	bool is_valid(Mapping map) {
		//TODO: check if moduleIf exists in patch still?
		return map.paramHandle.moduleId >= 0;
	}

	void clear_all() {
		// invalidate all maps
		for (auto &mappings : knobSets) {
			for (auto &knob : mappings.set) {
				for (auto &map : knob) {
					APP->engine->updateParamHandle(&map.paramHandle, -1, 0, true);
					map.paramHandle.module = nullptr;
					map.paramHandle.moduleId = -1;
				}
			}
		}
	}

	// Helpers

	auto begin() {
		auto &mappings = knobSets[activeSetId].set;
		return mappings.begin();
	}
	auto end() {
		auto &mappings = knobSets[activeSetId].set;
		return mappings.end();
	}
	auto &operator[](size_t n) {
		auto &mappings = knobSets[activeSetId].set;
		return mappings[std::min(n, NumKnobs - 1)];
	}
	auto &operator[](size_t n) const {
		auto &mappings = knobSets[activeSetId].set;
		return mappings[std::min(n, NumKnobs - 1)];
	}

	ParamHandleMultiMap nullmap{};
};
