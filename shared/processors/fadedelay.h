#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
//#include "debug.hh"
#include "math.hh"
#include "tools/delayLine.h"
#include <cmath>

using namespace MathTools;

class FadeDelay : public AudioProcessor {
public:
	virtual float update(float input)
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

		return (interpolate(input, output, mix));
	}

	FadeDelay()
	{
		set_samplerate(48000.0f);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			timeinMs = map_value(val, 0.0f, 1.0f, 0.0f, 1000.0f);
			sampleDelay = timeinMs / 1000.0f * sampleRate;
		}
		if (param_id == 1) {
			feedback = val;
		}
	}
	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

private:
	float sampleDelay;
	float mix = 0.5f;
	float feedback = 0.0f;

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
