#pragma once

class ExpDecay {
public:
	float decayTime = 10;
		float attackTime=10;

	ExpDecay()
	{
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
			slewedOut += ((input - slewedOut) * (1000.0f / decayTime / sampleRate));
		else {
			slewedOut += ((input - slewedOut) * (1000.0f / attackTime / sampleRate));
		}

		return (slewedOut);
	}

private:
	float sampleRate = 48000;
	float slewedOut = 0;
	int direction;
	float lastSample = 0;
	float currentSample = 0;
};