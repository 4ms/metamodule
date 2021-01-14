#pragma once
#include "audio_processor.hh"
#include "util/math.hh"

using namespace MathTools;

class BitCrusher : public AudioProcessor {
public:
	virtual float update(float input)
	{
		if ((reducedSampleRate == maxSampleRate) && (bitDepth == maxBitDepth)) {
			return input;
		} else {
			phaccu += reducedSampleRate / currentSampleRate;
			if (phaccu >= 1.0f) {
				int quantizedVal = floorf(input * ipow(2.0f, bitDepth >> 1));
				float bitReduced = (float)quantizedVal / powf(2.0f, bitDepth >> 1);

				sampledOutput = bitReduced;

				phaccu -= 1.0f;
			}
			return (sampledOutput);
		}
	}

	BitCrusher() {}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			float expoControl = val * val;
			if ((expoControl) <= 0.9f) {
				reducedSampleRate = map_value(expoControl, 0.0f, 0.9f, 0.1f, currentSampleRate / 16.0f);
			} else {
				reducedSampleRate = map_value(expoControl, 0.9f, 1.0f, currentSampleRate / 16.0f, maxSampleRate);
			}
		}
		if (param_id == 1) {
			bitDepth = map_value(val, 0.0f, 1.0f, 1U, maxBitDepth);
		}
	}
	virtual void set_samplerate(float sr)
	{
		currentSampleRate = sr;
		maxSampleRate = currentSampleRate / 2.0f;
	}

private:
	float reducedSampleRate = 48000.0f;
	float maxSampleRate;
	unsigned int maxBitDepth = 16U;
	unsigned int bitDepth = 16;
	float phaccu = 0;
	float currentSampleRate;
	float sampledOutput = 0;
};
