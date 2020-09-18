#pragma once

#include "audio_processor.hh"
#include "math.hh"
#include "tools/cubicDist.h"
#include "tools/delayLine.h"
#include <cmath>

CubicNonlinearDist limit;

using namespace MathTools;

class Phaser : public AudioProcessor {
public:
	float feedback = 0.98f;

	virtual float update(float input)
	{
		phaccu += 0.2f / sampleRate;
		if (phaccu > 1)
			phaccu -= 1.0f;
		sinLFO = sin(2 * M_PI * phaccu);
		for (int i = 0; i < 6; i++) {
			delay[i]->delayTimeMS = map_value(sinLFO, -1.0f, 1.0f, 0.0f, 1.0f);
		}
		delay[0]->update(limit.update(input + delay[5]->output * feedback));
		for (int i = 1; i < 6; i++) {
			delay[i]->update(delay[i - 1]->output);
		}

		output = delay[5]->output;
		return interpolate(input, output, 0.5f);
	}

	Phaser()
	{
		for (int i = 0; i < 6; i++)
			delay[i] = new DelayLine(100);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {}
		if (param_id == 1) {}
	}
	virtual void set_samplerate(float sr)
	{
		for (int i = 0; i < 6; i++)
			delay[i]->set_samplerate(sr);
		sampleRate = sr;
	}

private:
	float phaccu = 0;
	float sinLFO = 0;
	float output = 0;
	DelayLine *delay[6];
	float sampleRate;
};
