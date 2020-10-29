#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
//#include "debug.hh"
#include "math.hh"
#include "tools/dcBlock.h"
#include "tools/delayLine.h"
#include "tools/kneeCompress.h"
#include <cmath>

using namespace MathTools;

class Karplus : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output = input * fTaps;

		output += delayLine[0].update(input + delayLine[taps - 1].output * feedback);
		for (int i = 1; i < taps; i++) {
			output += delayLine[i].update(input + delayLine[i].output * feedback);
		}

		output = dcBlock.update(output/(fTaps*2.f));
		return output;
	}

	Karplus()
	{
		set_samplerate(48000.0f);
	}

	virtual void set_param(int param_id, float val)
	{
		//Todo: fix this so either param can be set independantly
		if (param_id == 0) {
			float baseFreq = map_value(val, 0.0f, 1.0f, 20.0f, 1000.0f);
			apPeriods[0] = 1.0f/baseFreq;
			delayLine[0].set_delay_samples(periodToSamples(apPeriods[0]));
		}
		if (param_id == 1) {
			spread = map_value(val, 0.0f, 1.0f, 1.0001f, 1.1f);
			for (int i = 1; i < taps; i++) {
				apPeriods[i] = apPeriods[i - 1] / spread;
				delayLine[i].set_delay_samples(periodToSamples(apPeriods[i]));
			}
		}

	}
	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

private:
	static const int taps = 6;
	static constexpr float fTaps = (float)taps;
	float apPeriods[taps];
	float sampleRate = 48000;
	float spread = 1.0f;

	float feedback = 0.995f;

	DelayLine<2400> delayLine[taps];

	float periodToSamples(float period)
	{
		return (period * sampleRate);
	}

	DCBlock dcBlock;
};
