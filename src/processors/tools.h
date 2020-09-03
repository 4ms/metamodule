#pragma once
#include "math.hh"
#include <cmath>

using namespace MathTools;

class ExpDecay {
public:
	float decayTime = 10;

	ExpDecay()
	{
		attackTime = 10;
	}

	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

	float update(float input)
	{
		lastSample = currentSample;
		currentSample = input;

		if (currentSample > lastSample) {
			direction = 1;
		}
		else if (currentSample < lastSample) {
			direction = 0;
		}

		if (direction == 0)
			slewedOut += (input - slewedOut) * (1000.0f / decayTime / sampleRate);
		else {
			slewedOut += (input - slewedOut) * (1000.0f / attackTime / sampleRate);
		}

		return (slewedOut);
	}

private:
	float sampleRate;
	float slewedOut = 0;
	int direction;
	float lastSample = 0;
	float currentSample = 0;
	float attackTime;
};

class CubicNonlinearDist {
public:
	CubicNonlinearDist()
	{
	}

	float update(float input)
	{
		float output = 0;
		float fTemp0 = constrain(input, -1.0f, 1.0f);
		output = fTemp0 * (1.0f - (0.333333343f * fTemp0 * fTemp0));
		return output;
	}

private:
};
