#pragma once

#include "debug.hh"
#include "math.hh"

template<int maxSamples>
class DelayLine {
public:
	float delaySamples = 0;
	float output = 0;

	DelayLine()
	{
		for (int i = 0; i < maxSamples; i++) {
			delayBuffer[i] = 0;
		}
	}

	virtual void set_samplerate(float sr)
	{
		// sampleRate = sr;
	}

	void update(float input)
	{
		delayBuffer[writeIndex] = input;
		readIndex = writeIndex - delaySamples;
		if (readIndex < 0)
			readIndex += maxSamples;
		read1 = readIndex;
		read2 = (read1 + 1) % maxSamples;
		float readFraction = readIndex - read1;
		output = interpolate(delayBuffer[read1], delayBuffer[read2], readFraction);
		// output = delayBuffer[readIndex];
		writeIndex++;
		writeIndex %= maxSamples;
	}

private:
	float delayBuffer[maxSamples];
	// float sampleRate = 44100;

	unsigned int writeIndex = 0;
	// int readIndex;
	float readIndex;
	unsigned int read1;
	unsigned int read2;
};
