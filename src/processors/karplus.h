#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
//#include "debug.hh"
#include "math.hh"
#include "tools/delayLine.h"
#include <cmath>

using namespace MathTools;

class Karplus : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output = 0;
		float apFreqs[taps];
		apFreqs[0] = baseFreq;
		for (int i = 1; i < taps; i++) {
			apFreqs[i] = apFreqs[i - 1] * spread;
		}

		float addTaps = 0;

		for (int i = 0; i < taps; i++) {
			delayLine[i].delaySamples = freqToSamples(apFreqs[i]);
		}

		for (int i = 0; i < taps; i++) {
			float lastSample = delayLine[i].output;
			if (i == 0)
				lastSample = delayLine[taps - 1].output;
			delayLine[i].update(input + lastSample * feedback);
		}

		for (int i = 0; i < taps; i++) {
			addTaps += delayLine[i].output;
		}

		output = input + addTaps;
		return (output);
	}

	Karplus()
	{
		set_samplerate(48000.0f);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			baseFreq = map_value(val, 0.0f, 1.0f, 20.0f, 1000.0f);
		}
		if (param_id == 1) {
			spread = map_value(val, 0.0f, 1.0f, 1.0001f, 1.1f);
		}
	}
	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

private:
	static const int taps = 6;
	float sampleRate = 48000;
	float spread = 1.0f;

	float baseFreq = 20.0f;
	float feedback = 0.995f;

	DelayLine<2400> delayLine[taps];

	float freqToSamples(float inputFrequency)
	{
		float seconds = 1.0f / inputFrequency;
		return (seconds * sampleRate);
	}
};
