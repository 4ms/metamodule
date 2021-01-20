#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/delayLine.h"

using namespace MathTools;

class GateconverterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		lastGate = currentGate;
		currentGate = del.update(gateInput)>0.0f;
		if (currentGate && (lastGate == false)) {
			sinceGate = 0;
		}
		if (sinceGate < lengthInSamples) {
			gateOutput = true;
		} else {
			gateOutput = false;
		}
		sinceGate++;
	}

	GateconverterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
			{
				float gateTime = map_value(val, 0.0f, 1.0f, 1.0f, 1000.0f);
				lengthInSamples = gateTime / 1000.0f * sampleRate;
				break;
			}
			case 1:
			{
				float delayTimeMs = map_value(val, 0.0f, 1.0f, 0.0f, 1000.0f);
				delayTimeSamples = delayTimeMs / 1000.0f * sampleRate;
				del.set_delay_samples(delayTimeSamples);
				break;
			}
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
				gateInput = (val > 0.0f);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				if (gateOutput)
					output = 1;
				else
					output = 0;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<GateconverterCore>();
	}
	static constexpr char typeID[20] = "GATECONVERTER";
	static constexpr char description[] = "Gate Converter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float sampleRate = 48000;
	bool gateInput = false;
	bool lastGate = false;
	bool currentGate = false;
	bool gateOutput = false;

	unsigned long sinceGate = 0;

	float lengthInSamples = 10;

	float delayTimeSamples = 0;

	DelayLine<96000> del;
};
