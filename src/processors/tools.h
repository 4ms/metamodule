#pragma once
#include <cmath>

namespace MathTools {

template<typename Tval, typename Tin, typename Tout>
static Tout map_value(Tval x, Tin in_min, Tin in_max, Tout out_min, Tout out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
static T constrain(T val, T min, T max)
{
	return val < min ? min : val > max ? max : val;
}

inline float interpolate(float in1, float in2, float x)
{
	return (in2 * x) + in1 * (1.0f - x);
}

}; // namespace MathTools

using namespace MathTools;

class ExpDecay {
public:
	float decayTime=10;

	ExpDecay()
	{
		for (int i = 0; i < 2; i++) {
			fRec0[i] = 0;
		}
	}

	virtual void set_samplerate(float sr)
	{
		fConst0 = 1.0f / constrain(sr, 1.0f, 192000.0f);
	}

	float update(float input)
	{
		float output = 0;
		float fSlow0 = (0.00100000005f * float(decayTime));
		int iSlow1 = (fabsf(fSlow0) < 0.00000001f); //1.1920929e-07f);
		float fSlow2 = (iSlow1 ? 0.0f : expf((0.0f - (fConst0 / (iSlow1 ? 1.0f : fSlow0)))));
		float fSlow3 = (1.0f - fSlow2);
		float fTemp0 = fabsf(input);
		fRec0[0] = fmax(fTemp0, ((fRec0[1] * fSlow2) + (fTemp0 * fSlow3)));
		output = fRec0[0];
		fRec0[1] = fRec0[0];
		return output;
	}

private:
	float fConst0;
	float fRec0[2];
};

class CubicNonlinearDist {
public:
CubicNonlinearDist()
{

}

float update(float input)
{
	float output =0;
	float fTemp0 = constrain(input,-1.0f,1.0f);
			output = fTemp0 * (1.0f - (0.333333343f * fTemp0*fTemp0));
			return output;
}
private:
};
