#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/twoOpFMOscillator.h"

using namespace MathTools;

class FmoscCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		mainOutput = fm.update();
	}

	FmoscCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				fm.freq = map_value(val, 0.0f, 1.0f, 20.0f, 800.0f);
				break;
			case 1:
				fm.modAmount = map_value(val, 0.0f, 1.0f, 0.0f, 10.0f);
				break;
			case 2:
				fm.ratioCoarse = map_value(val, 0.0f, 1.0f, 1, 16);
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
	float mainOutput;
};
