#pragma once
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
	// std::vector<Mapping *> maps;
	std::vector<std::unique_ptr<Mapping>> maps;
	// Todo: if we use a
	// then we can't do knobMaps.push_back() or emplace_back() because knobMaps is vector
	// and thus is relocates elements as the size increases

	KnobMap()
		: paramId{-1}
	{
		printf("KnobMap ctor %d\n", paramId);
	}

	KnobMap(int param_id)
		: paramId{param_id}
	{
		printf("KnobMap ctor %d\n", paramId);
	}

	bool create(int otherModuleId, int otherParamId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		auto &m = maps.emplace_back(std::make_unique<Mapping>());
		// auto &m = maps.emplace_back(new Mapping);

		auto &ph = m->paramHandle;
		color = mapColor;
		ph.color = mapColor;
		ph.text = "Mapped to MetaModule";

		// Check for existing, and clear it
		auto existingPh = APP->engine->getParamHandle(otherModuleId, otherParamId);
		if (existingPh) {
			existingPh->moduleId = -1;
			APP->engine->removeParamHandle(existingPh);
		}
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, otherModuleId, otherParamId, true);

		m->range = {min, max};
		return true;
	}

	~KnobMap()
	{
		printf("~KnobMap dtor %d\n", paramId);
		for (auto &map : maps) {
			if (APP->engine->getParamHandle(map->paramHandle.moduleId, map->paramHandle.paramId)) {
				APP->engine->removeParamHandle(&map->paramHandle);
			}
			printf("~deleted a map %d %d\n", map->paramHandle.moduleId, map->paramHandle.paramId);
		}
	}

	int getNumMaps()
	{
		int num = 0;
		for (auto &map : maps) {
			if (map->paramHandle.moduleId != -1) {
				num++;
			}
		}
		return num;
	}

	NVGcolor get_color()
	{
		return color;
	}

private:
	// Mapping *find_mapping(int otherModuleId, int otherParamId)
	// {
	// 	for (auto &m : maps) {
	// 		if ((m->paramHandle.moduleId == otherModuleId) && (m->paramHandle.paramId == otherParamId)) {
	// 			return &m->get();
	// 		}
	// 	}
	// 	return nullptr;
	// }
};
