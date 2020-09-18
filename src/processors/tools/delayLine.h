#pragma once

#include "math.hh"

class DelayLine {
public:
	float delayTimeMS = 500;

	DelayLine(float maxTimeMS)
	{
		maxSamples = ((maxTimeMS / 1000.0f) * sampleRate) + 1;
		delayBuffer = new float[maxSamples];
	}

	virtual void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

	float update(float input)
	{
		delayBuffer[writeIndex] = input;
		readIndex = writeIndex - ((delayTimeMS / 1000.0f) * sampleRate);
		if (readIndex < 0)
			readIndex += maxSamples;
		read1 = readIndex;
		read2 = (read1 + 1) % maxSamples;
		float readFraction = readIndex - read1;
		output = interpolate(read1, read2, readFraction);
		writeIndex++;
		writeIndex %= maxSamples;
		return (output);
	}

private:
	int maxSamples;
	float *delayBuffer;
	float sampleRate = 44100;

	float output = 0;

	unsigned long writeIndex;
	float readIndex;
	unsigned long read1;
	unsigned long read2;
};