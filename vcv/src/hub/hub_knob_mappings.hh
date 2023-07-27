#pragma once
#include "mapping/MappableObject.h"
#include "mapping/map_palette.hh"
#include "mapping/mapping.hh"
#include "util/static_string.hh"

template<size_t NumKnobs, size_t MaxMapsPerPot, size_t MaxKnobSets = 8>
struct HubKnobMappings {

	using KnobParamHandles = std::array<Mapping, MaxMapsPerPot>;
	struct KnobSet {
		std::string name;
		std::array<KnobParamHandles, NumKnobs> set;
	};

	std::array<KnobSet, MaxKnobSets> knobSets;
	std::array<StaticString<31>, NumKnobs> aliases;

private:
	int64_t hubModuleId = -1;
	unsigned activeSetId = 0;

public:
	HubKnobMappings(int64_t hubModuleId)
		: hubModuleId{hubModuleId} {
		for (auto &mappings : knobSets) {
			for (unsigned i = 0; auto &knob : mappings.set) {
				auto color = PaletteHub::color(i++);
				for (auto &map : knob) {
					map.paramHandle.color = color;
					APP->engine->addParamHandle(&map.paramHandle);
				}
			}
		}
	}

	~HubKnobMappings() {
		for (auto &mappings : knobSets) {
			for (auto &pot : mappings.set) {
				for (auto &map : pot)
					APP->engine->removeParamHandle(&map.paramHandle);
			}
		}
	}

	// Sets of Knob Mappings:

	void setKnobSetName(std::string &name) {
		knobSets[activeSetId].name = name;
	}

	unsigned getActiveKnobSetIdx() {
		return activeSetId;
	}

	void setActiveKnobSetIdx(unsigned setId) {
		if (setId < knobSets.size())
			activeSetId = setId;
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
		auto *map = nextFreeMap(hubParamId);
		APP->engine->updateParamHandle(&map->paramHandle, destModuleId, destParamId, true);
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

	Mapping *nextFreeMap(unsigned hubParamId) {
		// Find first unused paramHandle
		auto &mappings = knobSets[activeSetId].set;

		for (auto &p : mappings[hubParamId]) {
			if (p.paramHandle.moduleId < 0) {
				return &p;
			}
		}
		// If all are used, then overwrite the last one
		return &mappings[hubParamId][MaxMapsPerPot - 1];
	}

	// Get all mappings to a knob in the active set

	auto &getMappings(int hubParamId) {
		if (hubParamId >= (int)NumKnobs)
			return nullmap;

		auto &mappings = knobSets[activeSetId].set;
		return mappings[hubParamId];
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

							auto *map = nextFreeMap(hubParamId);

							val = json_object_get(mappingJ, "DstModID");
							auto destModuleId = json_is_integer(val) ? json_integer_value(val) : -1;

							val = json_object_get(mappingJ, "DstObjID");
							auto destModuleParamId = json_is_integer(val) ? json_integer_value(val) : -1;

							APP->engine->updateParamHandle(&map->paramHandle, destModuleId, destModuleParamId, true);

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
		return map.paramHandle.module && map.paramHandle.moduleId >= 0;
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

	KnobParamHandles nullmap{};
};
