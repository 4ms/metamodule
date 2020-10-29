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
		float output = input * taps;

		output += delayLine[0].update(input + delayLine[taps - 1].output * feedback);
		for (int i = 1; i < taps; i++) {
			output += delayLine[i].update(input + delayLine[i].output * feedback);
		}

		output = dcBlock.update(output / (taps * 2.f));
		return output;
	}

	Karplus()
	{
		set_samplerate(48000.0f);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			float baseFreq = map_value(val, 0.0f, 1.0f, 20.0f, 1000.0f);
			apPeriods[0] = 1.0f / baseFreq;
			delayLine[0].set_delay_samples(periodToSamples(apPeriods[0]));
			update_delay_samples();
		}
		if (param_id == 1) {
			spread = map_value(val, 0.0f, 1.0f, 1.0001f, 1.1f);
			update_delay_samples();
		}
	}
	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

private:
	static const int taps = 6;
	float apPeriods[taps];
	float sampleRate = 48000;
	float spread = 1.0f;

	float feedback = 0.995f;

	DelayLine<2400> delayLine[taps];

	float periodToSamples(float period)
	{
		return (period * sampleRate);
	}
	void update_delay_samples()
	{
		for (int i = 1; i < taps; i++) {
			apPeriods[i] = apPeriods[i - 1] / spread;
			delayLine[i].set_delay_samples(periodToSamples(apPeriods[i]));
		}
	}

	DCBlock dcBlock;
};
