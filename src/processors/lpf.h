#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
#include "math.hh"
#include "tools/cubicDist.h"
#include <cmath>

using namespace MathTools;

class LowPassFilter : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output = 0;
		fRec0[0] = (input - (fSlow3 * ((fSlow4 * fRec0[2]) + (fSlow5 * fRec0[1]))));
		output = dist.update(fSlow3 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		return output;
	}

	LowPassFilter()
	{
		set_samplerate(48000);
		set_param(0, 0.1f);
		set_param(1, 0.5f);
		for (int l0 = 0; l0 < 3; l0++) {
			fRec0[l0] = 0.0f;
		}
	}

	virtual void set_param(int param_id, float val)
	{
		const float minCutoff = 20.f;
		const float maxCutoff = 20000.f;

		if (param_id == 0) {
			if (fabsf(last_param[0] - val) > 0.001f) {
				last_param[0] = val;
				cutoff = map_value(val * val, 0.f, 1.f, minCutoff, maxCutoff);
				// fSlow1 = cutoff / fConst0;
				fSlow1 = tanTable.interp(cutoff / fConst0);
				fSlow2 = (1.0f / fSlow1);
				fSlow3 = (1.0f / (((fSlow0 + fSlow2) / fSlow1) + 1.0f));
				fSlow4 = (((fSlow2 - fSlow0) / fSlow1) + 1.0f);
				fSlow5 = (2.0f * (1.0f - (1.0f / (fSlow1 * fSlow1))));
			}
		}
		if (param_id == 1) {
			if (fabsf(last_param[1] - val) > 0.001f) {
				last_param[1] = val;
				q = map_value(val, 0.f, 1.f, 0.2f, 40.f);
				fSlow0 = (1.0f / q);
			}
		}
	}
	virtual void set_samplerate(float sr)
	{
		// fConst0 = constrain(sr, 1.0f, 192000.0f);
		fConst0 = constrain(sr, 1.0f, 192000.0f);
	}

	//~LowPassFilter() {}

private:
	CubicNonlinearDist dist;
	float last_param[2] = {0.f, 0.f};
	float cutoff;
	float q;
	float fRec0[3];
	float fConst0;
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4, fSlow5;
};
