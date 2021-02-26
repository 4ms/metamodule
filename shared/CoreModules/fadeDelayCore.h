#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"
#include "processors/tools/clockToSamples.h"
#include "processors/tools/multireadDelayLine.h"

using namespace MathTools;

class FadeDelayCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		clockSamples.update(clockInput);

		if (fading == false) {
			float finalDelay = constrain(baseDelay + cvInput * cvAmount, 0.0f, 1.0f);
			if (clockAttached == false) {
				timeinMs = map_value(finalDelay, 0.0f, 1.0f, 0.0f, 1000.0f);
				sampleDelay = timeinMs / 1000.0f * sampleRate;
			} else {
				int divSelect = finalDelay * 4.0f;
				auto delayCalc = clockSamples.getSamples() * divTable[divSelect];
				if (delayCalc < maxSamples)
					sampleDelay = delayCalc;
			}
		}
		lastDelay = currentDelay;
		currentDelay = sampleDelay;
		if (currentDelay != lastDelay) {
			delayTimes[1] = sampleDelay;
			fading = true;
			sinceChange = 0;
		}

		float output = 0;
		float fade = sinceChange / changeTime;

		if (fade > 1) {
			fade = 1;
		}

		if (fade >= 1) {
			delayTimes[0] = delayTimes[1];
			fading = false;
		}

		delayLine.updateSample(input + feedbackSample * feedback);
		if (fading)
			output = interpolate(delayLine.readSample(delayTimes[0]), delayLine.readSample(delayTimes[1]), fade);
		else {
			output = delayLine.readSample(delayTimes[1]);
		}

		delayLine.incrementWriteHead();

		feedbackSample = output;

		delayOutput = (interpolate(input, output, mix));

		sinceChange++;
	}

	FadeDelayCore() {}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				baseDelay = val;
				break;
			case 1:
				feedback = val;
				break;
			case 2: {
				float changeMs = 0;
				changeMs = map_value(val, 0.0f, 1.0f, 10.0f, 1000.0f);
				changeTime = changeMs * sampleRate / 1000.0f;
			} break;
			case 3:
				mix = val;
				break;
			case 4:
				cvAmount = val;
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
			case 1:
				clockInput = val;
				break;
			case 2:
				cvInput = val;
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

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 1)
			clockAttached = false;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 1)
			clockAttached = true;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FadeDelayCore>();
	}
	static constexpr char typeID[20] = "FADEDELAY";
	static constexpr char description[] = "Fade Delay";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	const float divTable[5] = {0.125, 0.25, 0.5, 1, 2};
	float sampleDelay = 0;
	float feedback = 0;
	float mix;

	float delayOutput = 0;

	float input = 0;

	float timeinMs = 0;
	float baseDelay = 0;

	float currentDelay = 0;
	float lastDelay = 0;

	float sampleRate = 48000;

	float cvInput = 0;
	float cvAmount = 0;

	const static inline long maxSamples = 48000;

	MultireadDelayLine<maxSamples> delayLine;

	float sinceChange = 0;
	float changeTime = 48000;

	float delayTimes[2] = {0, 0};

	float feedbackSample = 0;

	bool fading = false;

	float clockInput = 0;

	bool clockAttached = false;

	ClockToSamples clockSamples;
};
