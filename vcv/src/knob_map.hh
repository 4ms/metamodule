#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	int paramId{};
	struct Mapping {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;

		Mapping()
		{
			printf("Mapping ctor\n");
		}
		~Mapping()
		{
			printf("~Mapping dtor\n");
		}
	};
	std::array<Mapping, NUM_MAPPINGS_PER_KNOB> maps;

	KnobMap(int param_id)
		: paramId{param_id}
	{
		printf("KnobMap ctor %d\n", paramId);
	}

	void create(int otherModuleId, int otherParamId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		int new_idx = firstAvailable();
		if (new_idx == -1)
			return;

		auto &ph = maps[new_idx].paramHandle;
		ph.color = mapColor;
		ph.text = "Hub knob";
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, otherModuleId, otherParamId, true);

		maps[new_idx].range = {min, max};

		printf("knobMap[%d]: Added Mapping: maps[%zu] moduleId: %d, paramId: %d, module: &%p, ph:&%p\n",
			   paramId,
			   maps.size() - 1,
			   ph.moduleId,
			   ph.paramId,
			   ph.module,
			   &ph);
	}

	Mapping *find_mapping(int otherModuleId, int otherParamId)
	{
		printf("knobMap[%d].find_mapping: maps size is %zu\n", paramId, maps.size());
		for (auto &m : maps) {
			printf("find_mapping(module %d, param %d)... checking m:%d p:%d, module:%p\n",
				   otherModuleId,
				   otherParamId,
				   m.paramHandle.moduleId,
				   m.paramHandle.paramId,
				   m.paramHandle.module);
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
		printf("KnobMap[%d] dtor():\n", paramId);
		for (auto &map : maps) {
			printf("Map: m: %d p %d: ", map.paramHandle.moduleId, map.paramHandle.paramId);
			if (APP->engine->getParamHandle(map.paramHandle.moduleId, map.paramHandle.paramId)) {
				APP->engine->removeParamHandle(&map.paramHandle);
				printf("removeParamHandle %p.\n", &map.paramHandle);
			} else {
				printf("getParamHandle was null.\n");
			}
		}

		printf("end KnobMap dtor()\n");
	}

	int getNumMaps()
	{
		int num = 0;
		for (auto &map : maps) {
			if (map.paramHandle.moduleId != -1) {
				num++;
			}
		}
		// printf("getNumMaps() = %d\n", num);
		return num;
	}

	int firstAvailable()
	{
		int availableSlot = -1;
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			if (maps[i].paramHandle.moduleId == -1) {
				availableSlot = i;
				break;
			}
		}
		printf("firstAvailable() = %d\n", availableSlot);
		return availableSlot;
	}
};
