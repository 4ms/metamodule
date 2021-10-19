#pragma once
#include "plugin.hpp"
#include <array>
#include <rack.hpp>

class KnobMap {
public:
	int paramId{};
	NVGcolor color;
	struct Mapping {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;
	};
	std::vector<std::unique_ptr<Mapping>> maps;

	KnobMap()
		: paramId{-1}
	{
		// printf("KnobMap ctor %d\n", paramId);
	}

	KnobMap(int param_id)
		: paramId{param_id}
	{
		// printf("KnobMap ctor %d\n", paramId);
	}

	bool create(int otherModuleId, int otherParamId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		auto &m = maps.emplace_back(std::make_unique<Mapping>());

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

	~KnobMap()
	{
		// Must remove all paramHandles from APP->engine before module is destructed
		for (auto &map : maps) {
			map->paramHandle.moduleId = -1;
			APP->engine->removeParamHandle(&map->paramHandle);
		}
	}

	int getNumMaps()
	{
		return std::count_if(maps.begin(), maps.end(), [](auto &m) { return m->paramHandle.moduleId != -1; });
	}

	NVGcolor get_color()
	{
		return color;
	}
};
