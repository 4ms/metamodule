#include <rack.hpp>

template<int NUM_MAPPINGS_PER_KNOB = 8>
class KnobMap {
public:
	int paramId{};
	// Todo: use a vector not an array
	rack::ParamHandle paramHandles[NUM_MAPPINGS_PER_KNOB];
	std::pair<float, float> mapRange[NUM_MAPPINGS_PER_KNOB];

	KnobMap(int param_id, NVGcolor mapColor)
		: paramId{param_id}
	{
		// printf("KnobMap ctor()\n");
		// for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
		// 	paramHandles[i].color = mapColor;
		// 	APP->engine->addParamHandle(&paramHandles[i]);
		// 	mapRange[i] = {0, 1};
		// 	printf("KnobMap ctor(): addParamHandle %x\n", &paramHandles[i]);
		// }
		// printf("end KnobMap ctor()\n");
	}

	void create()
	{
		paramHandles[lowestEmpty].color = PaletteHub::color[knobToMap];
		printf("Adding paramhandle &%x", &paramHandles[lowestEmpty]);
		APP->engine->addParamHandle(&paramHandles[lowestEmpty]);
		APP->engine->updateParamHandle(&paramHandles[lowestEmpty], moduleId, paramId, true);
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
