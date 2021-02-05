#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class MinmaxCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		maxOut = max<float>(inA, inB);
		minOut = min<float>(inA, inB);
	}

	MinmaxCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				inA = val;
				break;
			case 1:
				inB = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = minOut;
				break;
			case 1:
				output = maxOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<MinmaxCore>();
	}
	static constexpr char typeID[20] = "MINMAX";
	static constexpr char description[] = "Minimum/Maximum";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float inA = 0;
	float inB = 0;

	float maxOut = 0;
	float minOut = 0;
};
