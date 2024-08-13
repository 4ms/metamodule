#pragma once
#include "audio_processor.hh"
#include "processors/tools/quantizeBits.h"
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
				float bitReduced = q.update(input);

				sampledOutput = bitReduced;

				phaccu -= 1.0f;
			}
			return (sampledOutput);
		}
	}

	BitCrusher()
	{
		q.setMax(1);
		q.setMin(-1);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			if (val == 1)
				reducedSampleRate = maxSampleRate;
			else {
				reducedSampleRate = setPitchMultiple(val) * 625.0f;
			}
		}
		if (param_id == 1) {
			bitDepth = map_value(val, 0.0f, 1.0f, 1U, maxBitDepth);
			q.setSteps(powf(2, bitDepth));
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
	float currentSampleRate = 48000;
	float sampledOutput = 0;

	BitQuantizer q;
};
