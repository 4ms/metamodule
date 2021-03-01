#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/allpass.h"
#include "processors/comb.h"

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

		for (int i = 0; i < numAllpass; i++) {
			wetSignal = apFilter[i].process(wetSignal);
		}

		signalOut = interpolate(signalIn, wetSignal, mix);
	}

	ReverbCore()
	{
		globalAllpassAtten = 1.0f;
		globalCombAtten = 1.0f;
		for (int i = 0; i < numAllpass; i++) {
			manualKnobAllpassAtten[i] = 1.0f;
			ratioKnobAllpassAtten[i] = 1.0f;
			apFilter[i].setLength(maxAllpassTuning[i]);
			apFilter[i].setFeedback(0.6f);
			apFilter[i].setFadeSpeed(0.001f);
		}

		for (int i = 0; i < numComb; i++) {
			manualKnobCombAtten[i] = 1.0f;
			ratioKnobCombAtten[i] = 1.0f;
			combFilter[i].setFeedback(0);
			combFilter[i].setLength(maxCombTuning[i]);
			combFilter[i].setFadeSpeed(0.001f);
		}
	}

	enum Knobs {
		Size = 0,
		Damp = 1,
		Mix = 2,
		Time = 3,
		AllpassRatio = 4,
		CRatio = 5,
		Allpass1,
		Allpass2,
		Allpass3,
		Allpass4,
		C1,
		C2,
		C3,
		C4,
		C5,
		C6,
		C7,
		C8,
	};

	float getAllpassTuning(const int id)
	{
		return currentAllpassTuning[id];
	}
	float getCombTuning(const int id)
	{
		return currentCombTuning[id];
	}
	void updateAllpassTuning(const int id)
	{
		currentAllpassTuning[id] =
			maxAllpassTuning[id] * globalAllpassAtten * manualKnobAllpassAtten[id] * ratioKnobAllpassAtten[id];
		if (currentAllpassTuning[id] < 1.f)
			currentAllpassTuning[id] = 1.f;
		apFilter[id].setLength(currentAllpassTuning[id]);
	}

	void updateCombTuning(const int id)
	{
		currentCombTuning[id] = maxCombTuning[id] * globalCombAtten * manualKnobCombAtten[id] * ratioKnobCombAtten[id];
		if (currentCombTuning[id] < 1.f)
			currentCombTuning[id] = 1.f;
		combFilter[id].setLength(currentCombTuning[id]);
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case Size:
				globalAllpassAtten = val;
				globalCombAtten = val;
				for (int i = 0; i < numComb; i++) {
					updateCombTuning(i);
				}
				for (int i = 0; i < numAllpass; i++) {
					updateAllpassTuning(i);
				}
				break;

			case Damp:
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setDamp(val);
				}
				break;

			case Mix:
				mix = val;
				break;

			case Time:
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setFeedback(map_value(val, 0.0f, 1.0f, 0.8f, 0.99f));
				}
				break;

			case AllpassRatio: {
				int ival = (int)(val * 48);		// 0...48
				float fval = ival / 12.f + 1.f; // 1..5, steps of 0.08333
				for (int i = 0; i < numAllpass; i++) {
					ratioKnobAllpassAtten[i] = i == 0 ? 1.f : ratioKnobAllpassAtten[i - 1] / fval;
					updateAllpassTuning(i);
				}
			} break;

			case CRatio: {
				int ival = (int)(val * 48);
				float fval = ival / 12.f + 1.f;
				for (int i = 0; i < numComb; i++) {
					ratioKnobCombAtten[i] = i == 0 ? 1.f : ratioKnobCombAtten[i - 1] / fval;
					updateCombTuning(i);
				}
			} break;

			case Allpass1:
			case Allpass2:
			case Allpass3:
			case Allpass4: {
				int i = param_id - Allpass1;
				manualKnobAllpassAtten[i] = val;
				updateAllpassTuning(i);
			} break;

			case C1:
			case C2:
			case C3:
			case C4:
			case C5:
			case C6:
			case C7:
			case C8: {
				int i = param_id - C1;
				manualKnobCombAtten[i] = val;
				updateCombTuning(i);
			} break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		// Todo: adjust fade speed for Comb and AllPass, when samplerate changes
	}

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

	static constexpr int numAllpass = 4;
	static constexpr int numComb = 8;

	// static constexpr int defaultAllpassTuning[numAllpass] = {1248, 812, 358, 125};
	// static constexpr int defaultCombTuning[numComb] = {3000, 4003, 4528, 5217, 1206, 2108, 3337, 5003};
	static constexpr int maxAllpassTuning[numAllpass] = {6000, 6000, 6000, 6000};
	static constexpr int maxCombTuning[numComb] = {6000, 6000, 6000, 6000, 6000, 6000, 6000, 6000};

	float globalAllpassAtten;
	float globalCombAtten;
	float manualKnobAllpassAtten[numAllpass];
	float manualKnobCombAtten[numComb];

	float ratioKnobAllpassAtten[numAllpass];
	float ratioKnobCombAtten[numComb];
	// Todo: Add CV
	// float ratioCvAllpassAtten[numAllpass];
	// float ratioCvCombAtten[numAllpass];

	float currentAllpassTuning[numAllpass];
	float currentCombTuning[numComb];

	AllPass<6000> apFilter[numAllpass];
	Comb<6000> combFilter[numComb];

	float mix = 0;
};
