#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
#include "math.hh"
#include "tools/cubicDist.h"
#include "tools/delayLine.h"
#include <cmath>

using namespace MathTools;

class Phaser : public AudioProcessor {
public:
	float feedback = 0.89f;

	virtual float update(float input)
	{
		phaccu += lfoSpeed / sampleRate;
		if (phaccu > 1.0f)
			phaccu -= 1.0f;
		sinLFO = sinTable.interp(phaccu);
		const float modDelayTime = map_value(sinLFO, -1.0f, 1.0f, 0.1f, 1.0f * lfoDepth);
		for (int i = 0; i < stages; i++) {
			delay[i].delayTimeMS = modDelayTime;
		}
		delay[0].update(inLimit.update(input + delay[stages - 1].output * feedback));
		for (int i = 1; i < stages; i++) {
			delay[i].update(delay[i - 1].output);
		}

		output = outLimit.update(delay[stages - 1].output);
		return interpolate(input, output, 0.5f);
	}

	Phaser()
	{
		// for (int i = 0; i < stages; i++)
		// 	delay[i] = new DelayLine(4);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			lfoSpeed = map_value(val, 0.0f, 1.0f, 0.05f, 1.0f);
		}
		if (param_id == 1) {
			lfoDepth = val;
		}
	}
	virtual void set_samplerate(float sr)
	{
		for (int i = 0; i < stages; i++)
			delay[i].set_samplerate(sr);
		sampleRate = sr;
	}

private:
	static const int stages = 6;
	static const int delayLineSamples = (int)((4.f / 1000.f) * 48000.f + 1.f);
	float phaccu = 0;
	float lfoDepth = 0;
	float lfoSpeed = 2;
	float sinLFO = 0;
	float output = 0;
	DelayLine<delayLineSamples> delay[stages];
	float sampleRate;
	CubicNonlinearDist inLimit;
	CubicNonlinearDist outLimit;
};