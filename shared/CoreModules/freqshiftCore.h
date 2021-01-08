#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/fShift.h"

using namespace MathTools;

class FreqshiftCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		fShift.shift.setValue(shiftCoarse + shiftFine);
		fShift.mix.setValue(mix);
		signalOutput = fShift.update(signalInput);
	}

	FreqshiftCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				shiftCoarse = map_value(val, 0.0f, 1.0f, -10000.0f, 10000.0f);
				break;
			case 1:
				shiftFine = map_value(val, 0.0f, 1.0f, -5.0f, 5.0f);
				break;
			case 2:
				mix = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		fShift.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FreqshiftCore>();
	}
	static constexpr char typeID[20] = "FREQSHIFT";
	static constexpr char description[] = "Frequency Shifter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	FreqShift fShift;

	float shiftCoarse = 0;
	float shiftFine = 0;

	float mix = 0;

	float signalInput = 0;
	float signalOutput = 0;
};
