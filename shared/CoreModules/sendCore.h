#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class SendCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		for (int i = 0; i < 4; i++) {
			signalOuts[i] = signalInput * levels[i];
		}
	}

	SendCore()
	{
		for (int i = 0; i < 4; i++) {
			levels[i] = 0;
			signalOuts[i] = 0;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		levels[param_id] = val;
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
		output = signalOuts[output_id];
		return output;
	}
	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<SendCore>();
	}
	static constexpr char typeID[20] = "SEND_1TO4";
	static constexpr char description[] = "Splitter - 1 in to 4 out";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float levels[4];
	float signalInput = 0;
	float signalOuts[4];
};
