#pragma once

#include "audio_processor.hh"
#include "math.hh"
#include "tools/cubicDist.h"
#include "util/math_tables.hh"
#include <cmath>

using namespace MathTools;

class LowPassFilter : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output=0;
		float fSlow0 = (1.0f / float(q));
		float fSlow1 = std::tan((fConst0 * float(cutoff)));
		float fSlow2 = (1.0f / fSlow1);
		float fSlow3 = (1.0f / (((fSlow0 + fSlow2) / fSlow1) + 1.0f));
		float fSlow4 = (((fSlow2 - fSlow0) / fSlow1) + 1.0f);
		float fSlow5 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
		fRec0[0] = (float(input) - (fSlow3 * ((fSlow4 * fRec0[2]) + (fSlow5 * fRec0[1]))));
		output = float((fSlow3 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		return output;
	}

	LowPassFilter()
	{
		set_samplerate(48000);
		set_param(0, 0.1f);
		set_param(1, 0.0f);
		for (int i = 0; i < 3; i++) {
			fRec0[i] = 0.0f;
		}
	}

	virtual void set_param(int param_id, float val)
	{
		const float minCutoff = 20.f;
		const float maxCutoff = 20000.f;

		if (param_id == 0) {
				cutoff = map_value(val * val, 0.f, 1.f, minCutoff, maxCutoff);
		}
		if (param_id == 1) {
				q=map_value(val,0.0f,1.0f,0.1f,20.0f);
		}
	}
	virtual void set_samplerate(float sr)
	{
		samplerate = constrain(sr, 1.0f, 192000.0f);
		fConst0 = (3.14159274f / std::min<float>(192000.0f, std::max<float>(1.0f, float(samplerate))));
	}

	//~LowPassFilter() {}

private:
	CubicNonlinearDist dist;
	float cutoff;
	float q=1;
	float fRec0[3];
	float samplerate=48000;
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4, fSlow5;
	float fConst0=1;

	static float mydsp_faustpower2_f(float value) {
	return (value * value);
}
};
