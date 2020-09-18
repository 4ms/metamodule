#pragma once

class DelayLine {
public:
	DelayLine(float maxTimeMS)
	{
		maxSamples = (maxTimeMS / 1000.0f) * sampleRate;
		delayBuffer = new float[]
	}

	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

	float update(float input)
	{
	}

private:
	int maxSamples;
	float *delayBuffer;
	float sampleRate;
};