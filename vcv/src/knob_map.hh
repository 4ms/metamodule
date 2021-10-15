#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	int paramId{};
	NVGcolor color;
	struct Mapping {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;
	};
	std::vector<Mapping> maps;

	// rack::ParamHandle paramHandles[NUM_MAPPINGS_PER_KNOB];
	// std::pair<float, float> mapRange[NUM_MAPPINGS_PER_KNOB];

	KnobMap(int param_id, NVGcolor mapColor)
		: paramId{param_id}
		, color{mapColor}
	{
		// for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
		// 	paramHandles[i].color = mapColor;
		// 	APP->engine->addParamHandle(&paramHandles[i]);
		// 	mapRange[i] = {0, 1};
		// 	printf("KnobMap ctor(): addParamHandle %x\n", &paramHandles[i]);
		// }
	}

	void create(int moduleId, int paramId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		maps.push_back({rack::ParamHandle{}, {0.f, 1.f}});

		auto &ph = maps.back().paramHandle;
		ph.color = color;
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, moduleId, paramId, true);

		maps.back().range = {min, max};

		printf("Added paramhandle moduleId: %d, paramId: %d, &%p", moduleId, paramId, &ph);
	}

	Mapping *find_mapping(int moduleId, int paramId)
	{
		for (auto &m : maps) {
			if ((m.paramHandle.moduleId == moduleId) && (m.paramHandle.paramId == paramId))
				return &m;
		}
		return nullptr;
	}

	void update_range(int moduleId, int paramId, float min, float max)
	{
		auto m = find_mapping(moduleId, paramId);
		if (m)
			m->range = {min, max};
	}

	bool mapping_already_exists(int moduleId, int paramId)
	{
		return find_mapping(moduleId, paramId) != nullptr;
	}

	// ~KnobMap()
	// {
	// 	printf("KnobMap dtor()\n");
	// 	for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
	// 		if (APP->engine->getParamHandle(paramHandles[i].moduleId, paramHandles[i].paramId)) {
	// 			APP->engine->removeParamHandle(&paramHandles[i]);
	// 			printf("KnobMap dtor(): removeParamHandle %x\n", &paramHandles[i]);
	// 		}
	// 	}
	// 	printf("end KnobMap dtor()\n");
	// }

	// Todo: with a vector this is just .size()
	int getNumMaps()
	{
		return maps.size();
		// int num = 0;
		// for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
		// 	if (paramHandles[i].moduleId != -1) {
		// 		num++;
		// 	}
		// }
		// return num;
	}

	// Todo: with a vector this is just .push_back()
	// int firstAvailable()
	// {
	// 	int availableSlot = -1;
	// 	int tempNum = NUM_MAPPINGS_PER_KNOB;
	// 	if (getNumMaps() < 8) {
	// 		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
	// 			if (paramHandles[i].moduleId == -1) {
	// 				tempNum = std::min<int>(tempNum, i);
	// 			}
	// 		}
	// 		availableSlot = tempNum;
	// 	}
	// 	return availableSlot;
	// }
};
