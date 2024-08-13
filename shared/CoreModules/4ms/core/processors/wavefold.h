#pragma once
#include "../util/interp_array.hh"
#include "audio_processor.hh"
#include "math.hh"
#include "wavefold_tables.h" //Tables from new g++ project
#include <cmath>

using namespace MathTools;

class WaveFolder : public AudioProcessor {

public:
	virtual float update(float input)
	{
		float output = 0;

		float foldInterp = foldType - (long)foldType;
		switch ((int)foldType) {
			case 0:
				output = interpolate(cleanFold(input), sharpFold(input), foldInterp);
				break;
			case 1:
				output = interpolate(sharpFold(input), chebyFold(input), foldInterp);
				break;
			case 2:
				output = interpolate(chebyFold(input), triFold(input), foldInterp);
				break;
			case 3:
				output = triFold(input);
				break;
		}
		return (output);
	}

	WaveFolder()
	{
		// Todo: generate these in tableGen
		for (int i = 0; i < 512; i++) {
			fold1[i] = map_value(i % 256, 0.0f, 255.0f, -1.0f, 1.0f);
			fold2[i] = map_value(fmodf(i, 170.6666666667f), 0.0f, (512.f / 3.0f - 1.f), -1.0f, 1.0f);
			fold3[i] = map_value(i % 128, 0.0f, 127.0f, -1.0f, 1.0f);
		}
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			mainFold = val;
		}
		if (param_id == 1) {
			foldType = val * 3.0f;
		}
	}
	virtual void set_samplerate(float sr) {}

private:
	float mainFold = 0;
	float foldType = 0;
	static inline InterpArray<float, 512> fold1, fold2, fold3;

	float sharpFold(float input)
	{
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, 1.0f);

		float foldSamp[4];
		foldSamp[0] = input;

		foldSamp[1] = fold1.interp(lookupIndex);
		foldSamp[2] = fold2.interp(lookupIndex);
		foldSamp[3] = fold3.interp(lookupIndex);

		float foldLevel = mainFold * 3.0f;
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}

	float cleanFold(float input)
	{
		// float scaledMainFold = constrain(mainFold + 0.004f, 0.f, 1.f);
		// Todo: scale mainFold so it goes to 0, but slowly goes up to 0.004f
		// Or constrain to 0.004...1.0f and add a VCA that goes to 0->1.0 as mainFold goes 0->0.1
		// (or so)
		float scaledMainFold = mainFold;
		float gainedInput = input * scaledMainFold;

		float lookupIndex = map_value(gainedInput, -1.0f, 1.0f, 0.0f, 1.0f);
		float foldSamp = fold.interp(lookupIndex);

		lookupIndex = map_value(mainFold, 0.f, 1.0f, 0.0f, 1.0f);
		float foldMax = fold_max.interp(lookupIndex);

		float output = foldSamp * foldMax;

		return (output);
	}

	float chebyFold(float input)
	{
		int cheby_tables = 16;
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, 1.0f);

		float foldSamp[cheby_tables + 1];
		foldSamp[0] = input;
		for (int i = 0; i < cheby_tables; i++) {
			foldSamp[i + 1] = cheby[i].interp(lookupIndex);
		}

		float foldLevel = mainFold * float(cheby_tables);
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}

	float triFold(float input)
	{
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, 1.0f);

		float foldSamp[9];
		foldSamp[0] = input;
		for (int i = 0; i < 8; i++) {
			foldSamp[i + 1] = triangles[i].interp(lookupIndex);
		}

		float foldLevel = mainFold * 8.0f;
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}
};
