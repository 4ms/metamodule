#pragma once
#include "audio_processor.hh"
#include "tools.h"

class WaveFolder : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float lookupIndex = map_value(input / 5.0f, -1.0f, 1.0f, 0.0f, 511.0f);
		float interpVal = lookupIndex - (long)lookupIndex;
		int firstLookup = lookupIndex;
		int secondLookup = (firstLookup + 1) % 512;

		float foldSamp[4];
		foldSamp[0] = interpolate(fold1[firstLookup], fold1[secondLookup], interpVal);
		foldSamp[1] = interpolate(fold2[firstLookup], fold2[secondLookup], interpVal);
		foldSamp[2] = interpolate(fold3[firstLookup], fold3[secondLookup], interpVal);
		foldSamp[3] = interpolate(fold4[firstLookup], fold4[secondLookup], interpVal);

		float foldLevel = mainFold * 3.0f;
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		switch ((int)foldLevel) {
			case 0:
				output = interpolate(foldSamp[0], foldSamp[1], foldPartial);
				break;
			case 1:
				output = interpolate(foldSamp[1], foldSamp[2], foldPartial);
				break;
			case 2:
				output = interpolate(foldSamp[2], foldSamp[3], foldPartial);
				break;
			case 3:
				output = foldSamp[3];
				break;
		}

		return (output * 5.0f);
	}

	WaveFolder()
	{
		//Generate fold tables
		for (int i = 0; i < 512; i++) {
			fold1[i] = map_value(i, 0.0f, 511.0f, -1.0f, 1.0f);
			fold2[i] = map_value(fmod(i, 256), 0.0f, 255.0f, -1.0f, 1.0f);
			fold3[i] = map_value(fmod(i, 170.6666666667), 0.0f, (512 / 3.0f - 1), -1.0f, 1.0f);
			fold4[i] = map_value(fmod(i, 128), 0.0f, 127.0f, -1.0f, 1.0f);
		}
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			mainFold = val;
		}
		if (param_id == 1) {
		}
	}
	virtual void set_samplerate(float sr)
	{
	}

private:
	float mainFold;
	float fold1[512] = {0};
	float fold2[512] = {0};
	float fold3[512] = {0};
	float fold4[512] = {0};
};
