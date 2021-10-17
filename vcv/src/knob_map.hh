#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	int paramId{};
	struct Mapping {
		rack::ParamHandle paramHandle;
		std::pair<float, float> range;
	};
	// Note: While a vector makes adding and removing mappings simple, VCV doesn't support this since it keeps a raw
	// pointer to the vector element, and appending to a vector can cause re-location of previous elements
	// So we have to use an array, and we have a fixed # of maximum mappings per knob
	std::array<Mapping, NUM_MAPPINGS_PER_KNOB> maps;

	KnobMap(int param_id)
		: paramId{param_id}
	{}

	bool create(int otherModuleId, int otherParamId, NVGcolor mapColor, float min = 0.f, float max = 1.0f)
	{
		int new_idx = firstAvailable();
		if (new_idx == -1)
			return false;

		auto &ph = maps[new_idx].paramHandle;
		ph.color = mapColor;
		ph.text = "Hub knob"; // TODO, something meaningful
		APP->engine->addParamHandle(&ph);
		APP->engine->updateParamHandle(&ph, otherModuleId, otherParamId, true);

		maps[new_idx].range = {min, max};
		return true;
	}

	Mapping *find_mapping(int otherModuleId, int otherParamId)
	{
		for (auto &m : maps) {
			if ((m.paramHandle.moduleId == otherModuleId) && (m.paramHandle.paramId == otherParamId)) {
				return &m;
			}
		}
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
		for (auto &map : maps) {
			if (APP->engine->getParamHandle(map.paramHandle.moduleId, map.paramHandle.paramId)) {
				APP->engine->removeParamHandle(&map.paramHandle);
			}
		}
	}

	int getNumMaps()
	{
		int num = 0;
		for (auto &map : maps) {
			if (map.paramHandle.moduleId != -1) {
				num++;
			}
		}
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
		return availableSlot;
	}
};
