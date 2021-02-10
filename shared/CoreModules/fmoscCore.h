#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/twoOpFMOscillator.h"
#include "util/math.hh"

using namespace MathTools;

class FmoscCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		fm.set_frequency(basePitch * expTable.interp(constrain(pitchInput, 0.0f, 1.0f)));
		totalIndex = constrain(indexCV*indexAmount + indexKnob, 0.0f, 1.0f);
		float totalShape = constrain(shapeCV*shapeAmount + shapeKnob, 0.0f, 1.0f);
		fm.shape = totalShape;
		fm.modAmount = totalIndex;
		mainOutput = fm.update();
	}

	FmoscCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				basePitch = 20.0f * expTable.interp(val);
				break;
			case 1:
				indexKnob = val;
				break;
			case 2:
				fm.ratioCoarse = map_value(val, 0.0f, 1.0f, 0, 7);
				break;
			case 3: {
				if (val < 0.5f)
					fm.ratioFine = map_value(val, 0.0f, 0.5f, 0.5f, 1.0f);
				else
					fm.ratioFine = map_value(val, 0.5f, 1.0f, 1.0f, 2.0f);
				break;
			}
			case 4:
				shapeKnob = val;
				break;
			case 5:
				shapeAmount = val;
				break;
			case 6:
				indexAmount = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		fm.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				indexCV = val;
				break;
			case 1:
				pitchInput = val;
				break;
			case 2:
				shapeCV = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = mainOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FmoscCore>();
	}
	static constexpr char typeID[20] = "FMOSC";
	static constexpr char description[] = "FM Oscillator";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	TwoOpFM fm;
	float basePitch = 0;
	float mainOutput;
	float indexKnob = 0;
	float indexCV = 0;
	float shapeKnob = 0;
	float shapeCV = 0;
	float totalIndex = 0;
	float pitchInput = 0;
	float shapeAmount = 0;
	float indexAmount = 0;
};
