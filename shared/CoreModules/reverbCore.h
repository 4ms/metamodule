#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/freeverb/allpass.h"
#include "processors/freeverb/comb.h"

using namespace MathTools;

class ReverbCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float wetSignal = 0;

		for (int i = 0; i < numComb; i++) {
			wetSignal += combFilter[i].process(signalIn);
		}

		wetSignal /= static_cast<float>(numComb);

		for (int i = 0; i < numAll; i++) {
			wetSignal = apFilter[i].process(wetSignal);
		}

		signalOut = interpolate(signalIn, wetSignal, mix);
	}

	ReverbCore()
	{
		for (int i = 0; i < numAll; i++) {
			apFilter[i].setLength(allTuning[i]);
			apFilter[i].setFeedback(0.6f);
			currentAllTunning[i] = allTuning[i];
		}

		for (int i = 0; i < numComb; i++) {
			combFilter[i].setFeedback(0);
			combFilter[i].setLength(combTuning[i]);
			currentCombTuning[i] = combTuning[i];
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: // size
				for (int i = 0; i < numComb; i++) {
					currentCombTuning[i] = combTuning[i] * val;
					if (currentCombTuning[i] < 1)
						currentCombTuning[i] = 1;
						combFilter[i].setLength(currentCombTuning[i]);
				}
				for (int i = 0; i < numAll; i++) {
					currentAllTunning[i] = allTuning[i] * val;
					if (currentAllTunning[i] < 1)
						currentAllTunning[i] = 1;
						apFilter[i].setLength(currentAllTunning[i]);
				}
				break;
			case 1: // damp
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setDamp(val);
				}
				break;
			case 2:
				mix = val;
				break;
			case 3: // time
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setFeedback(map_value(val,0.0f,1.0f,0.8f,0.99f));
				}
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalIn = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ReverbCore>();
	}
	static constexpr char typeID[20] = "REVERB";
	static constexpr char description[] = "Reverb";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float signalIn = 0;
	float signalOut = 0;

	static const int numComb = 8;
	static const int numAll = 4;

	static constexpr int allTuning[numAll] = {1248, 812, 358, 125};
	static constexpr int combTuning[numComb] = {3000, 4003, 4528, 5217, 1206, 2108, 3337, 5003};

	int currentAllTunning[numAll];
	int currentCombTuning[numComb];

	Comb combFilter[numComb];
	allpass apFilter[numAll];

	float mix = 0;
};
