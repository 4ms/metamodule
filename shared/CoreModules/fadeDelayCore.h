#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"
#include "processors/tools/multireadDelayLine.h"

using namespace MathTools;

class FadeDelayCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float output = 0;
		float fade = sinceChange / changeTime;

		if (fade > 1) {
			fade = 1;
		}

		if (fade >= 1) {
			delayTimes[0] = delayTimes[1];
			fading = false;
		}

		sinceChange++;
		delayLine.updateSample(input + feedbackSample * feedback);

		output = interpolate(delayLine.readSample(delayTimes[0]), delayLine.readSample(delayTimes[1]), fade);

		delayLine.incrementWriteHead();

		feedbackSample = output;

		delayOutput = (interpolate(input, output, mix));
	}

	FadeDelayCore() {}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				timeinMs = map_value(val, 0.0f, 1.0f, 0.0f, 1000.0f);
				sampleDelay = timeinMs / 1000.0f * sampleRate;
				lastDelay = currentDelay;
				currentDelay = sampleDelay;
				if (currentDelay != lastDelay) {
					delayTimes[1] = sampleDelay;
					fading = true;
					sinceChange = 0;
				}

				break;
			case 1:
				feedback = val;
				break;
			case 2: {
				auto changeMs = 0;
				changeMs = map_value(val, 0.0f, 1.0f, 10.0f, 1000.0f);
				changeTime = changeMs / 1000.0f * sampleRate;
			} break;
			case 3:
				mix = val;
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
				input = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = delayOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FadeDelayCore>();
	}
	static constexpr char typeID[20] = "FADEDELAY";
	static constexpr char description[] = "Fade Delay";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float sampleDelay = 0;
	float feedback = 0;
	float mix;

	float delayOutput = 0;

	float input = 0;

	float timeinMs = 0;

	float currentDelay = 0;
	float lastDelay = 0;

	float sampleRate = 48000;

	const static inline long maxSamples = 48000;

	MultireadDelayLine<maxSamples> delayLine;

	float sinceChange = 0;
	float changeTime = 48000;

	float delayTimes[2] = {0, 0};

	float feedbackSample = 0;

	bool fading = false;
};
