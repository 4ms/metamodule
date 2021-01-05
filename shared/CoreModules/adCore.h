#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class AdCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		stage = (int)phaccu;
		float envFrequency;
		if (stage == 0) {
			envFrequency = 1000.0f / attackTime;
		}
		else {
			envFrequency = 1000.0f / decayTime;
		}

		phaccu += envFrequency / sampleRate;

		if (stage == 0) {
			envOut = phaccu;
		}
		else {
			if (phaccu >= 2)
				envOut = 0;
			else {
				envOut = 2.0f - phaccu;
			}
		}

		if (currentGate > lastGate) {
			phaccu = 0;
			stage = 0;
		}
	}

	AdCore()
	{
	}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				attackTime = map_value(val, 0.0f, 1.0f, 1.0f, 1200.0f);
				break;
			case 1:
				decayTime = map_value(val, 0.0f, 1.0f, 1.0f, 1200.0f);
				break;
		}
	}

	virtual void set_samplerate(const float sr) override
	{
		sampleRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				lastGate = currentGate;
				currentGate = val > 0;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = envOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<AdCore>();
	}
	static constexpr char typeID[20] = "ADENV";
	static constexpr char description[] = "Attack Decay Envelope";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int currentGate = 0;
	int lastGate = 0;
	float attackTime = 0;
	float decayTime = 0;
	float envOut = 0;

	float phaccu;
	int stage = 0;

	float sampleRate = 48000;
};
