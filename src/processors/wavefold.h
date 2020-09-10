#pragma once
#include "audio_processor.hh"
#include "tools.h"
#include "wavefold-tables-old.h" //Tables from original python scripts (don't work right)
#include "wavefold_tables.h"	 //Tables from new g++ project (not all converted yet)

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
		//return (output);

		return (chebyFold(input));
	}

	WaveFolder()
	{
		//Generate fold tables
		for (int i = 0; i < 512; i++) {
			fold1[i] = map_value(fmodf(i, 256.f), 0.0f, 255.0f, -1.0f, 1.0f);
			fold2[i] = map_value(fmodf(i, 170.6666666667), 0.0f, (512.f / 3.0f - 1.f), -1.0f, 1.0f);
			fold3[i] = map_value(fmodf(i, 128.f), 0.0f, 127.0f, -1.0f, 1.0f);
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
	virtual void set_samplerate(float sr)
	{
	}

private:
	float mainFold;

	float foldType = 0;
	float fold1[512] = {0};
	float fold2[512] = {0};
	float fold3[512] = {0};

	float sharpFold(float input)
	{
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, 511.0f);
		float interpVal = lookupIndex - (long)lookupIndex;
		int firstLookup = lookupIndex;
		int secondLookup = (firstLookup + 1) % 512;

		float foldSamp[4];
		foldSamp[0] = input;
		foldSamp[1] = interpolate(fold1[firstLookup], fold1[secondLookup], interpVal);
		foldSamp[2] = interpolate(fold2[firstLookup], fold2[secondLookup], interpVal);
		foldSamp[3] = interpolate(fold3[firstLookup], fold3[secondLookup], interpVal);

		float foldLevel = mainFold * 3.0f;
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}

	float cleanFold(float input)
	{
		// s1_31 sample = x * s1_15(amount);
		// u0_32 phase = sample.to_unsigned_scale();
		// f res = DynamicData::fold.interpolateDiff<f>(phase);
		// res *= DynamicData::fold_max.interpolate(amount);

		float scaledMainFold = constrain(mainFold + 0.004f, 0.f, 1.f);
		float gainedInput = input * scaledMainFold;
		float lookupIndex = map_value(gainedInput, -1.0f, 1.0f, 0.0f, 1024.0f);
		float interpVal = lookupIndex - (long)lookupIndex;
		int firstLookup = lookupIndex;
		int secondLookup = (firstLookup + 1) % 1025;

		float foldSamp = interpolate(fold[firstLookup], fold[secondLookup], interpVal);
		float foldMax = interpolate(fold_max[firstLookup / 2], fold_max[secondLookup / 2], interpVal);
		float output = foldSamp * foldMax;

		return (output);
	}

	float chebyFold(float input)
	{
		int cheby_tables = 16;
		int cheby_size = 513;
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, (float)(cheby_size - 1));
		float interpVal = lookupIndex - (long)lookupIndex;
		int firstLookup = lookupIndex;
		int secondLookup = (firstLookup + 1) % cheby_size;

		float foldSamp[cheby_tables + 1];
		foldSamp[0] = input;
		for (int i = 0; i < cheby_tables; i++) {
			foldSamp[i + 1] = interpolate(cheby[i][firstLookup], cheby[i][secondLookup], interpVal);
		}

		float foldLevel = mainFold * float(cheby_tables);
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}

	float triFold(float input)
	{
		float lookupIndex = map_value(input, -1.0f, 1.0f, 0.0f, 8.0f);
		float interpVal = lookupIndex - (long)lookupIndex;
		int firstLookup = lookupIndex;
		int secondLookup = (firstLookup + 1) % 9;

		float foldSamp[9];
		foldSamp[0] = input;
		for (int i = 0; i < 8; i++) {
			foldSamp[i + 1] = interpolate(triangles[i][firstLookup], triangles[i][secondLookup], interpVal);
		}

		float foldLevel = mainFold * 8.0f;
		float foldPartial = foldLevel - (long)foldLevel;

		float output = 0;

		output = interpolate(foldSamp[(int)foldLevel], foldSamp[(int)(foldLevel + 1)], foldPartial);

		return (output);
	}
};
