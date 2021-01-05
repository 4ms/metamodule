#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class LogicCore : public CoreProcessor {
public:
	LogicCore() {}

	virtual void update(void) override
	{
		andOutput = (int)in1 & (int)in2;
		orOutput = (int)in1 | (int)in2;
		xorOutput = (int)in1 ^ (int)in2;
	}

	virtual void set_param(const int param_id, const float val) override
	{
	}
	virtual void set_samplerate(const float sr) override
	{
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				in1 = val > 0.0f;
				break;
			case 1:
				in2 = val > 0.0f;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = andOutput;
				break;
			case 1:
				output = orOutput;
				break;
			case 2:
				output = xorOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LogicCore>();
	}
	static constexpr char typeID[20] = "LOGIC";
	static constexpr char description[] = "Logic - AND, OR, XOR";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float in1;
	float in2;
	float andOutput;
	float orOutput;
	float xorOutput;
};
