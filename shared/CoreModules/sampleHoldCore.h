#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class SampleHoldCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		lastSample1 = currentSample1;
		currentSample1 = sample1;

		lastSample2 = currentSample2;
		currentSample2 = sample2;

		if (currentSample1 > lastSample1) {
			out1 = in1;
		}

		if (currentSample2 > lastSample2) {
			out2 = in2;
		}
	}

	SampleHoldCore()
	{
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
			case 0: {
				if (in1Connected == 1) {
					in1 = val;
				}
				else {
					in1 = randomNumber(-1.0f, 1.0f);
				}
			} break;
			case 1:
				sample1 = val > 0.0f;
				break;
			case 2: {
				if (in2Connected == 1) {
					in2 = val;
				}
				else {
					in2 = randomNumber(-1.0f, 1.0f);
				}
			} break;
			case 3:
				sample2 = val > 0.0f;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = out1;
				break;
			case 1:
				output = out2;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 0;
		else if (input_id == 2)
			in2Connected = 0;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 1;
		else if (input_id == 2)
			in2Connected = 1;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<SampleHoldCore>();
	}
	static constexpr char typeID[20] = "SAMPHOLD";
	static constexpr char description[] = "Sample and Hold";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float in1 = 0;
	float in2 = 0;
	float sample1 = 0;
	float sample2 = 0;
	float out1 = 0;
	float out2 = 0;

	int currentSample1 = 0;
	int lastSample1 = 0;
	int currentSample2 = 0;
	int lastSample2 = 0;

	int in1Connected = 0;
	int in2Connected = 0;
};
