#pragma once

#include "audio_processor.hh"
#include "tools.h"
#include <cmath>

using namespace MathTools;

class LowPassFilter : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output = 0;
		float fSlow0 = (1.0f / q);
		float fSlow1 = tan((fConst0 * cutoff)); //todo: will this compile on stm32?
		float fSlow2 = (1.0f / fSlow1);
		float fSlow3 = (1.0f / (((fSlow0 + fSlow2) / fSlow1) + 1.0f));
		float fSlow4 = (((fSlow2 - fSlow0) / fSlow1) + 1.0f);
		float fSlow5 = (2.0f * (1.0f - (1.0f / (fSlow1 * fSlow1))));
		fRec0[0] = (input - (fSlow3 * ((fSlow4 * fRec0[2]) + (fSlow5 * fRec0[1]))));
		output = (fSlow3 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		return output;
	}

	LowPassFilter()
	{
		cutoff = 200;
		q = 1;
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
	}

	virtual void set_param(int param_id, float val)
	{
		const float minCutoff = 20.F;
		const float maxCutoff = 20000.F;
		if (param_id == 0)
			cutoff = map_value(val, 0.F, 1.F, minCutoff, maxCutoff);
		if (param_id == 1)
			q = map_value(val, 0.F, 1.F, 0.2F, 40.F);
	}
	virtual void set_samplerate(float sr)
	{
		fConst0 = (3.14159274F / std::min<float>(192000.0F, std::max<float>(1.0F, float(sr))));
	}

private:
	float cutoff;
	float q;
	float fRec0[3];
	float fConst0 = 0;
};

