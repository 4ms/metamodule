#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/delayLine.h"
#include "processors/tools/windowComparator.h"

using namespace MathTools;

class GateconverterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		lastGate = currentGate;
		currentGate = wc.get_output();
		if (currentGate && (lastGate == false)) {
			finalDelay = map_value(constrain(delayCV + delayTime, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f, 1000.0f) / 1000.0f * sampleRate;
			finalLength = map_value(constrain(lengthCV + gateLength, 0.0f, 1.0f), 0.0f, 1.0f, 1.0f, 1000.0f) / 1000.0f *
						  sampleRate;

			del.set_delay_samples(finalDelay);

			sinceGate = 0;
		}

		wc.update(del.update(signalInput));

		if (sinceGate < finalLength) {
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
			case 0: {
				gateLength = val;
				break;
			}
			case 1: {
				delayTime = val;
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
				signalInput = val;
				break;
			case 1:
				lengthCV = val;
				break;
			case 2:
				delayCV = val;
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
	bool lastGate = false;
	bool currentGate = false;
	bool gateOutput = false;

	unsigned long sinceGate = 0;

	float gateLength = 10;

	float delayTime = 0;

	float signalInput = 0;

	float lengthCV = 0;
	float delayCV = 0;

	float finalLength = 10;
	float finalDelay = 0;

	DelayLine<96000> del;
	WindowComparator wc;
};
