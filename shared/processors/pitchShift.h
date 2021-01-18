#pragma once

#include "util/math.hh"

using namespace MathTools;

class PitchDelay {
private:
	float samplesMax;
	float *delayBuffer;
	unsigned long writeIndex = 0;
	float sampR;
	int samplesNeeded;

public:
	PitchDelay(float maxTime)
	{
		float sampRate = 96000;
		samplesMax = maxTime / 1000.0f * sampRate;
		samplesNeeded = samplesMax + 1;
		delayBuffer = new float[samplesNeeded];
		sampR = sampRate;
	}
	float timeinMs = 0;
	float timeinMs2 = 0;
	float output1;
	float output2;

	void update(float input)
	{
		float timeToSamples = (timeinMs / 1000.0f) * sampR;
		delayBuffer[writeIndex] = input;

		float sampleToRead = writeIndex - timeToSamples;
		if (sampleToRead < 0)
			sampleToRead += samplesNeeded;
		float fractional = sampleToRead - (long)sampleToRead;

		int firstSample = sampleToRead;
		int secondSample = (firstSample + 1) % samplesNeeded;

		float timeToSamples2 = timeinMs2 / 1000.0f * sampR;
		float offsetSampleToRead = writeIndex - timeToSamples2;
		if (offsetSampleToRead < 0)
			offsetSampleToRead += samplesNeeded;
		float offsetFractional = offsetSampleToRead - (long)offsetSampleToRead;

		int firstOffsetSample = offsetSampleToRead;
		int secondOffsetSample = (firstOffsetSample + 1) % samplesNeeded;

		writeIndex++;
		writeIndex %= samplesNeeded;
		output1 = interpolate(delayBuffer[firstSample], delayBuffer[secondSample], fractional);
		output2 = interpolate(delayBuffer[firstOffsetSample], delayBuffer[secondOffsetSample], offsetFractional);
	}

	void setSampleRate(float sr)
	{
		sampR = sr;
	}
};

class PitchShift {
private:
	std::unique_ptr<PitchDelay> pitchDelay;
	float phaccu = 0;
	const float maxWindow = 1000;
	const int incrementalPitch = 1;
	float sampleRate = 96000;

public:
	PitchShift()
	{
		pitchDelay = std::make_unique<PitchDelay>(maxWindow);
	}
	float shiftAmount = 1;
	float windowSize = 500;
	float mix = 0;
	float update(float input)
	{
		if (incrementalPitch == 0)
			shiftAmount = (long)shiftAmount;
		pitchDelay->timeinMs = phaccu * windowSize;
		float adjustedPhase = phaccu + 0.5f;
		if (adjustedPhase >= 1)
			adjustedPhase -= 1.0f;
		pitchDelay->timeinMs2 = adjustedPhase * windowSize;
		float window1 = 0;
		float window2 = 0;

		window1 = sin(M_PI * phaccu);
		window2 = sin(M_PI * (adjustedPhase));
		float pitchToFreq = 0;
		pitchToFreq = ((expf(shiftAmount * 0.05776f) - 1.0f) * -1.0f) / (windowSize * 0.001f);
		phaccu += pitchToFreq / sampleRate;
		if (phaccu >= 1)
			phaccu -= 1.0f;
		if (phaccu < 0)
			phaccu += 1.0f;
		pitchDelay->update(input);
		float wet = (pitchDelay->output1 * window1 + pitchDelay->output2 * window2);
		return (interpolate(input, wet, mix));
	}

	void setSampleRate(float sr)
	{
		sampleRate = sr;
		pitchDelay->setSampleRate(sr);
	}
};