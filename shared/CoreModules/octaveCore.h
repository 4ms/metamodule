#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class OctaveCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		voltOutput = voltInput + octave;
	}

	OctaveCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				octave = map_value(val, 0.0f, 1.0f, 0, 5);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				voltInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = voltOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<OctaveCore>();
	}
	static constexpr char typeID[20] = "OCTAVE";
	static constexpr char description[] = "Octave";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int octave = 0;
	float voltInput = 0;
	float voltOutput = 0;
};
