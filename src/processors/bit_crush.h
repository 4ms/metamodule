#pragma once
#include "audio_processor.hh"
#include "math.hh"
#include "tools.h"

class BitCrusher : public AudioProcessor {
public:
	virtual float update(float input)
	{
		phaccu += reducedSampleRate / currentSampleRate;
		if (phaccu > 1.0f) {
			int quantizedVal = input * ipow(2.0f, bitDepth);
			float bitReduced = (float)quantizedVal / (float)(ipow(2.0f, bitDepth));

			sampledOutput = bitReduced;

			phaccu -= 1.0f;
		}
		return (sampledOutput);
	}

	BitCrusher()
	{
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			float expoControl = val * val;
			if ((expoControl) <= 0.9f) {
				reducedSampleRate = map_value(expoControl, 0.0f, 0.9f, 0.1f, currentSampleRate / 16.0f);
			}
			else {
				reducedSampleRate = map_value(expoControl, 0.9f, 1.0f, currentSampleRate / 16.0f, currentSampleRate / 2.0f);
			}
		}
		if (param_id == 1) {
			bitDepth = map_value(val, 0.0f, 1.0f, 1U, 16U);
		}
	}
	virtual void set_samplerate(float sr)
	{
		currentSampleRate = sr;
	}

private:
	float reducedSampleRate = 48000.0f;
	int bitDepth = 16;
	float phaccu = 0;
	float currentSampleRate;
	float sampledOutput = 0;
};
