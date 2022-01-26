#pragma once
#include "plugin.hpp"
#include <array>
#include <rack.hpp>
#include <vector>

class KnobMap {
public:
	int paramId{};
	NVGcolor color;
	std::string alias_name{""};
	struct MappingDest {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;
		MappingDest() = default;
	};
	// Todo: vector might not be the best container, since we don't need it to be ordered and contigious.
	std::vector<std::unique_ptr<MappingDest>> maps;

	KnobMap()
		: paramId{-1}
	{}

	KnobMap(int param_id)
		: paramId{param_id}
	{}

	~KnobMap()
	{
		// Must remove all paramHandles from APP->engine before module is destructed
		for (auto &map : maps) {
			map->paramHandle.moduleId = -1;
			APP->engine->removeParamHandle(&map->paramHandle);
		}
	}

	void cleanupMaps()
	{
		for (auto &map : maps) {
			if (map->paramHandle.moduleId == -1) {
				APP->engine->removeParamHandle(&map->paramHandle);
			}
		}

		std::erase_if(maps, [](auto &m) { return m->paramHandle.moduleId == -1; });
	}

	bool create(int otherModuleId,
				int otherParamId,
				NVGcolor mapColor,
				float min = 0.f,
				float max = 1.0f,
				std::string alias_name = "")
	{
		printf("NOT SUPPOSED TO CALL THIS\n\n\n");
		cleanupMaps();

		auto &m = maps.emplace_back(std::make_unique<MappingDest>());

		auto &ph = m->paramHandle;
		color = mapColor;
		ph.color = mapColor;
		ph.text = "Mapped to MetaModule knob# " + std::to_string(paramId);

		// Check for existing, and clear it
		auto existingPh = APP->engine->getParamHandle(otherModuleId, otherParamId);
		if (existingPh) {
			APP->engine->updateParamHandle(existingPh, -1, 0, true);
			centralData->unregisterMapByDest({LabelButtonID::Types::Knob, otherParamId, otherModuleId});
		}
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, otherModuleId, otherParamId, true);

		m->range = {min, max};

		return true;
	}

	int getNumMaps()
	{
		return std::count_if(maps.begin(), maps.end(), [](auto &m) { return m->paramHandle.moduleId != -1; });
	}

	NVGcolor get_color()
	{
		return color;
	}

	std::string get_alias_name()
	{
		return alias_name;
	}

	void set_alias_name(std::string_view newname)
	{
		alias_name = newname;
	}
};
