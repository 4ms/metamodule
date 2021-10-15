#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	// Todo: use a vector not an array
	rack::ParamHandle paramHandles[NUM_MAPPINGS_PER_KNOB];
	std::pair<float, float> mapRange[NUM_MAPPINGS_PER_KNOB];
	int paramId{};

	KnobMap(NVGcolor mapColor)
	{
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			paramHandles[i].color = mapColor;
			APP->engine->addParamHandle(&paramHandles[i]);
			mapRange[i] = {0, 1};
		}
	}

	~KnobMap()
	{
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			APP->engine->removeParamHandle(&paramHandles[i]);
		}
	}

	// Todo: with a vector this is just .size()
	int getNumMaps()
	{
		int num = 0;
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			if (paramHandles[i].moduleId != -1) {
				num++;
			}
		}
		return num;
	}

	// Todo: with a vector this is just .push_back()
	int firstAvailable()
	{
		int availableSlot = -1;
		int tempNum = NUM_MAPPINGS_PER_KNOB;
		if (getNumMaps() < 8) {
			for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
				if (paramHandles[i].moduleId == -1) {
					tempNum = std::min<int>(tempNum, i);
				}
			}
			availableSlot = tempNum;
		}
		return availableSlot;
	}
};
