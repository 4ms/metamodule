#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	int paramId{};
	struct Mapping {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;
	};
	std::vector<Mapping> maps;

	KnobMap(int param_id)
		: paramId{param_id}
	{}

	void create(int otherModuleId, int otherParamId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		printf("knobMap[%d].create() start: map size is %d\n", paramId, maps.size());
		maps.emplace_back(); //{}, std::make_pair(0.f, 1.f));
		printf("knobMap[%d].create() emplace_back: map size is %d\n", paramId, maps.size());

		auto &ph = maps.back().paramHandle;
		ph.color = mapColor;
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, otherModuleId, otherParamId, true);
		printf("knobMap[%d].create() after updateParamHandle: map size is %d\n", paramId, maps.size());

		maps.back().range = {min, max};

		printf("knobMap[%d]: Added Mapping: maps[%d] moduleId: %d, paramId: %d, &%p\n",
			   paramId,
			   maps.size() - 1,
			   otherModuleId,
			   otherParamId,
			   &ph);
	}

	Mapping *find_mapping(int otherModuleId, int otherParamId)
	{
		printf("knobMap[%d].find_mapping: maps size is %d\n", paramId, maps.size());
		for (auto &m : maps) {
			printf("find_mapping(module %d, param %d)... checking m:%d p:%d\n",
				   otherModuleId,
				   otherParamId,
				   m.paramHandle.moduleId,
				   m.paramHandle.paramId);
			if ((m.paramHandle.moduleId == otherModuleId) && (m.paramHandle.paramId == otherParamId)) {
				printf("Mapping for module %d, param %d found\n", otherModuleId, otherParamId);
				return &m;
			}
		}
		// printf("Mapping not found\n");
		return nullptr;
	}

	void update_range(int otherModuleId, int otherParamId, float min, float max)
	{
		auto m = find_mapping(otherModuleId, otherParamId);
		if (m)
			m->range = {min, max};
	}

	bool mapping_already_exists(int otherModuleId, int otherParamId)
	{
		return find_mapping(otherModuleId, otherParamId) != nullptr;
	}

	~KnobMap()
	{
		printf("KnobMap[%d] dtor()\n", paramId);
		// 	for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
		// 		if (APP->engine->getParamHandle(paramHandles[i].moduleId, paramHandles[i].paramId)) {
		// 			APP->engine->removeParamHandle(&paramHandles[i]);
		// 			printf("KnobMap dtor(): removeParamHandle %x\n", &paramHandles[i]);
		// 		}
		// 	}
		printf("end KnobMap dtor()\n");
	}

	int getNumMaps()
	{
		return maps.size();
	}
};
