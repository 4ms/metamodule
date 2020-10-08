#pragma once

#include "math.hh"

template<int maxSamples>
class DelayLine {
public:
	float delayTimeMS = 0;

	float output = 0;

	DelayLine()
	{
		for (int i = 0; i < maxSamples; i++) {
			delayBuffer[i] = 0;
		}
	}

	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

	void update(float input)
	{
		delayBuffer[writeIndex] = input;
		readIndex = writeIndex - ((delayTimeMS / 1000.0f) * sampleRate);
		if (readIndex < 0)
			readIndex += maxSamples;
		read1 = readIndex;
		read2 = (read1 + 1) % maxSamples;
		float readFraction = readIndex - read1;
		output = interpolate(delayBuffer[read1], delayBuffer[read2], readFraction);
		writeIndex++;
		writeIndex %= maxSamples;
	}

private:
	// int maxSamples;
	float delayBuffer[maxSamples];
	float sampleRate = 44100;

	unsigned long writeIndex = 0;
	float readIndex;
	unsigned long read1;
	unsigned long read2;
};
