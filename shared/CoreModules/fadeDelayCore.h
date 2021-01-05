#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"
#include "processors/tools/delayLine.h"

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

		for (int i = 0; i < 2; i++) {
			delayLine[i].update(input + feedbackSample * feedback);
			taps[i] = delayLine[i].output;
		}

		smoothDelayTime += (timeinMs - smoothDelayTime) * 0.0001f;

		if ((smoothDelayTime != currentDelayTime) && fade >= 1) {
			delayLine[!activeChannel].set_delay_samples(sampleDelay);
			sinceChange = 0;
		}

		lastReachedNew = reachedNew;
		reachedNew = fade >= 1;
		if (reachedNew > lastReachedNew) {
			activeChannel = !activeChannel;
		}

		sinceChange++;

		output = interpolate(taps[activeChannel], taps[!activeChannel], fade);
		feedbackSample = output;

		delayOutput = (interpolate(input, output, mix));
	}

	FadeDelayCore()
	{
	}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				timeinMs = map_value(val, 0.0f, 1.0f, 0.0f, 1000.0f);
				sampleDelay = timeinMs / 1000.0f * sampleRate;
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

	float sampleRate = 48000;

	DelayLine<96000> delayLine[2];

	float sinceChange = 0;
	float changeTime = 48000;

	float currentDelayTime = 0;

	float smoothDelayTime = 0;

	int activeChannel = 0;
	float taps[2];

	int lastReachedNew = 0;
	int reachedNew = 0;

	float feedbackSample = 0;
};
