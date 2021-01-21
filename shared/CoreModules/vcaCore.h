#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "util/math.hh"
#include "util/parameter.h"

using namespace MathTools;

class VCACore : public CoreProcessor {
public:
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;
	virtual int get_num_inputs() const override
	{
		return NumInJacks;
	}
	virtual int get_num_outputs() const override
	{
		return NumOutJacks;
	}
	virtual int get_num_params() const override
	{
		return NumKnobs;
	}

	VCACore() {}

	VCACore(float &in, float &CV, float &output)
		: input{in}
		, cv{CV}
		, vcaOutput{output}
	{}

	virtual void update(void) override
	{
		auto clippedOutput = constrain(input * preGain, -1.0f, 1.0f);
		auto vcaCtrl = constrain(offset + cv * cvAmount, -1.0f, 1.0f) * postGain;
		vcaOutput = clippedOutput * vcaCtrl;
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				preGain = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
				break;
			case 1:
				postGain = val;
				break;
			case 2:
				offset = val;
				break;
			case 3:
				cvAmount = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				input = val;
				break;
			case 1:
				cv = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = vcaOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<VCACore>();
	}
	static constexpr char typeID[20] = "VCA";
	static constexpr char description[] = "Basic VCA";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	RefParameter<float> input = nodes[0];
	RefParameter<float> cv = nodes[1];
	RefParameter<float> vcaOutput = nodes[2];

	float preGain = 1;
	float postGain = 1;
	float offset = 0;
	float cvAmount;
};
