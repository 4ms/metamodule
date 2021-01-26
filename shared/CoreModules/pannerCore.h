#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class PannerCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		leftOut = signalInput * (1.0f - panPosition);
		rightOut = signalInput * panPosition;
	}

	PannerCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				panPosition = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

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
				output = leftOut;
				break;
			case 1:
				output = rightOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<PannerCore>();
	}
	static constexpr char typeID[20] = "PANNER";
	static constexpr char description[] = "Panner";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float panPosition = 0;
	float signalInput = 0;
	float leftOut = 0;
	float rightOut = 0;
};
